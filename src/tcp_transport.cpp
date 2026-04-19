/**
 * @file tcp_transport.cpp
 * @brief TCP Transport implementation for Croupier C++ SDK.
 */

#include "croupier/sdk/tcp_transport.h"
#include <stdexcept>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace croupier {
namespace sdk {

#ifdef _WIN32
bool TCPTransport::ws_initialized_ = false;
std::mutex TCPTransport::ws_init_mutex_;
#endif

TCPTransport::TCPTransport(const std::string& host, int port, int timeout_ms)
    : host_(host),
      port_(port),
      timeout_ms_(timeout_ms),
      socket_(INVALID_SOCKET_VALUE),
      connected_(false),
      closing_(false),
      next_req_id_(1) {

#ifdef _WIN32
    // Initialize Winsock once
    std::lock_guard<std::mutex> lock(ws_init_mutex_);
    if (!ws_initialized_) {
        WSADATA wsa_data;
        if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0) {
            ws_initialized_ = true;
        }
    }
#endif
}

TCPTransport::~TCPTransport() {
    Close();
}

TCPTransport::TCPTransport(TCPTransport&& other) noexcept
    : host_(std::move(other.host_)),
      port_(other.port_),
      timeout_ms_(other.timeout_ms_),
      socket_(other.socket_),
      connected_(other.connected_.load()),
      closing_(other.closing_.load()),
      next_req_id_(other.next_req_id_.load()),
      pending_responses_(std::move(other.pending_responses_)),
      read_thread_(std::move(other.read_thread_)) {
    other.socket_ = INVALID_SOCKET_VALUE;
    other.connected_ = false;
}

TCPTransport& TCPTransport::operator=(TCPTransport&& other) noexcept {
    if (this != &other) {
        Close();

        host_ = std::move(other.host_);
        port_ = other.port_;
        timeout_ms_ = other.timeout_ms_;
        socket_ = other.socket_;
        connected_ = other.connected_.load();
        closing_ = other.closing_.load();
        next_req_id_ = other.next_req_id_.load();
        pending_responses_ = std::move(other.pending_responses_);
        read_thread_ = std::move(other.read_thread_);

        other.socket_ = INVALID_SOCKET_VALUE;
        other.connected_ = false;
    }
    return *this;
}

void TCPTransport::Connect() {
    if (connected_) {
        return;
    }

    // Create socket
    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_ == INVALID_SOCKET_VALUE) {
        throw std::runtime_error("Failed to create socket");
    }

    // Set receive timeout
#ifdef _WIN32
    DWORD timeout = timeout_ms_;
    setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO,
               reinterpret_cast<const char*>(&timeout), sizeof(timeout));
#else
    struct timeval tv;
    tv.tv_sec = timeout_ms_ / 1000;
    tv.tv_usec = (timeout_ms_ % 1000) * 1000;
    setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif

    // Connect
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);

    if (inet_pton(AF_INET, host_.c_str(), &addr.sin_addr) <= 0) {
        // Resolve hostname
        addrinfo* result = nullptr;
        addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        int ret = getaddrinfo(host_.c_str(), nullptr, &hints, &result);
        if (ret != 0) {
            closesocket(socket_);
            socket_ = INVALID_SOCKET_VALUE;
            throw std::runtime_error("Failed to resolve host: " + host_);
        }

        std::memcpy(&addr.sin_addr, &reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr,
                   sizeof(addr.sin_addr));
        freeaddrinfo(result);
    }

    if (connect(socket_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR_VALUE) {
        closesocket(socket_);
        socket_ = INVALID_SOCKET_VALUE;
        throw std::runtime_error("Failed to connect to " + host_ + ":" + std::to_string(port_));
    }

    connected_ = true;
    closing_ = false;

    // Start read loop
    read_thread_ = std::thread(&TCPTransport::ReadLoop, this);
}

void TCPTransport::Close() {
    closing_ = true;
    connected_ = false;

    if (socket_ != INVALID_SOCKET_VALUE) {
        closesocket(socket_);
        socket_ = INVALID_SOCKET_VALUE;
    }

    if (read_thread_.joinable()) {
        read_thread_.join();
    }

    std::lock_guard<std::mutex> lock(pending_mutex_);
    pending_responses_.clear();
}

bool TCPTransport::IsConnected() const {
    return connected_ && !closing_;
}

std::pair<uint32_t, std::vector<uint8_t>> TCPTransport::Call(
    uint32_t msg_type, const std::vector<uint8_t>& data) {

    if (!connected_) {
        throw std::runtime_error("Not connected");
    }

    uint32_t req_id = next_req_id_++;
    auto latch = std::make_unique<ResponseLatch>();

    {
        std::lock_guard<std::mutex> lock(pending_mutex_);
        pending_responses_[req_id] = std::move(latch);
    }

    // Create frame: [4-byte length][8-byte protocol header][body]
    size_t frame_size = FRAME_HEADER_BYTES + PROTOCOL_HEADER_SIZE + data.size();
    std::vector<uint8_t> frame(frame_size);

    // Frame length (big-endian)
    uint32_t payload_size = static_cast<uint32_t>(PROTOCOL_HEADER_SIZE + data.size());
    frame[0] = (payload_size >> 24) & 0xFF;
    frame[1] = (payload_size >> 16) & 0xFF;
    frame[2] = (payload_size >> 8) & 0xFF;
    frame[3] = payload_size & 0xFF;

    // Protocol header
    frame[4] = VERSION_1;
    PutMsgId(frame.data() + 5, msg_type);
    frame[8] = (req_id >> 24) & 0xFF;
    frame[9] = (req_id >> 16) & 0xFF;
    frame[10] = (req_id >> 8) & 0xFF;
    frame[11] = req_id & 0xFF;

    // Request body
    std::memcpy(frame.data() + 12, data.data(), data.size());

    // Send frame
    ssize_t sent = send(socket_, reinterpret_cast<const char*>(frame.data()),
                       frame.size(), 0);
    if (sent != static_cast<ssize_t>(frame.size())) {
        throw std::runtime_error("Failed to send complete frame");
    }

    // Get response latch
    std::unique_ptr<ResponseLatch> response_latch;
    {
        std::lock_guard<std::mutex> lock(pending_mutex_);
        auto it = pending_responses_.find(req_id);
        if (it != pending_responses_.end()) {
            response_latch = std::move(it->second);
            pending_responses_.erase(it);
        }
    }

    if (!response_latch) {
        throw std::runtime_error("Response latch not found");
    }

    // Wait for response
    if (!response_latch->Wait(timeout_ms_)) {
        throw std::runtime_error("Timeout waiting for response");
    }

    return {response_latch->msg_id, std::move(response_latch->body)};
}

void TCPTransport::ReadLoop() {
    uint8_t header_buf[FRAME_HEADER_BYTES];

    while (!closing_ && socket_ != INVALID_SOCKET_VALUE) {
        // Read frame header
        int n = ReadFully(header_buf, FRAME_HEADER_BYTES);
        if (n < static_cast<int>(FRAME_HEADER_BYTES)) {
            break;
        }

        // Parse frame size
        uint32_t frame_size = (static_cast<uint32_t>(header_buf[0]) << 24) |
                             (static_cast<uint32_t>(header_buf[1]) << 16) |
                             (static_cast<uint32_t>(header_buf[2]) << 8) |
                             static_cast<uint32_t>(header_buf[3]);

        if (frame_size == 0 || frame_size > MAX_FRAME_BYTES) {
            break;
        }

        // Read frame payload
        std::vector<uint8_t> payload(frame_size);
        n = ReadFully(payload.data(), frame_size);
        if (n < static_cast<int>(frame_size)) {
            break;
        }

        // Parse protocol header
        if (payload.size() < PROTOCOL_HEADER_SIZE) {
            continue;
        }

        uint8_t version = payload[0];
        if (version != VERSION_1) {
            continue;
        }

        uint32_t msg_id = GetMsgId(payload.data() + 1);
        uint32_t req_id = (static_cast<uint32_t>(payload[4]) << 24) |
                         (static_cast<uint32_t>(payload[5]) << 16) |
                         (static_cast<uint32_t>(payload[6]) << 8) |
                         static_cast<uint32_t>(payload[7]);

        size_t body_size = payload.size() - PROTOCOL_HEADER_SIZE;
        std::vector<uint8_t> body(body_size);
        std::memcpy(body.data(), payload.data() + PROTOCOL_HEADER_SIZE, body_size);

        // Route to pending request
        std::lock_guard<std::mutex> lock(pending_mutex_);
        auto it = pending_responses_.find(req_id);
        if (it != pending_responses_.end()) {
            it->second->Signal(std::move(body), msg_id);
        }
    }

    if (!closing_) {
        Close();
    }
}

int TCPTransport::ReadFully(void* buf, size_t count) {
    size_t offset = 0;
    char* buffer = static_cast<char*>(buf);

    while (offset < count) {
        ssize_t n = recv(socket_, buffer + offset, count - offset, 0);
        if (n <= 0) {
            return static_cast<int>(offset);
        }
        offset += n;
    }
    return static_cast<int>(offset);
}

void TCPTransport::PutMsgId(uint8_t* buf, uint32_t msg_id) {
    buf[0] = (msg_id >> 16) & 0xFF;
    buf[1] = (msg_id >> 8) & 0xFF;
    buf[2] = msg_id & 0xFF;
}

uint32_t TCPTransport::GetMsgId(const uint8_t* buf) {
    return (static_cast<uint32_t>(buf[0]) << 16) |
           (static_cast<uint32_t>(buf[1]) << 8) |
           static_cast<uint32_t>(buf[2]);
}

} // namespace sdk
} // namespace croupier
