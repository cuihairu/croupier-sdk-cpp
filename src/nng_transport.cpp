/**
 * @file nng_transport.cpp
 * @brief NNG Transport Layer implementation for Croupier C++ SDK.
 */

#include "croupier/sdk/nng_transport.h"
#include "croupier/sdk/logger.h"

#include <chrono>
#include <cstring>

namespace croupier {
namespace sdk {

// ========== NNGTransport Implementation ==========

NNGTransport::NNGTransport(const std::string& address, int timeout_ms)
    : address_(address),
      timeout_ms_(timeout_ms),
      socket_(NNG_SOCKET_INITIALIZER),
      connected_(false),
      request_id_(0) {
    SDK_LOG_INFO("NNGTransport created for address: " << address_);
}

NNGTransport::~NNGTransport() {
    Close();
}

void NNGTransport::Connect() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (connected_) {
        return;
    }

    SDK_LOG_INFO("Connecting to NNG server at: " << address_);

    // Create REQ socket
    int rv = nng_req0_open(&socket_);
    if (rv != 0) {
        throw std::runtime_error("Failed to create socket: " + std::string(nng_strerror(rv)));
    }

    // Set timeouts
    nng_duration timeout = timeout_ms_;
    nng_socket_set_ms(socket_, NNG_OPT_SENDTIMEO, timeout);
    nng_socket_set_ms(socket_, NNG_OPT_RECVTIMEO, timeout);

    // Dial to server
    rv = nng_dial(socket_, address_.c_str(), nullptr, 0);
    if (rv != 0) {
        nng_close(socket_);
        throw std::runtime_error("Failed to dial: " + std::string(nng_strerror(rv)));
    }

    connected_ = true;
    SDK_LOG_INFO("Connected to: " << address_);
}

void NNGTransport::Close() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!connected_) {
        return;
    }

    nng_close(socket_);
    socket_ = NNG_SOCKET_INITIALIZER;
    connected_ = false;

    SDK_LOG_INFO("NNG transport closed");
}

bool NNGTransport::IsConnected() const {
    return connected_;
}

std::pair<uint32_t, std::vector<uint8_t>> NNGTransport::Call(
    uint32_t msg_type, const std::vector<uint8_t>& data) {

    if (!connected_) {
        throw std::runtime_error("Not connected");
    }

    std::lock_guard<std::mutex> lock(mutex_);

    // Generate request ID
    request_id_ = (request_id_ + 1) & 0xFFFFFFFF;

    // Build message with protocol header
    auto message = protocol::NewMessage(msg_type, request_id_, data);

    SDK_LOG_DEBUG("Sending message type=0x" << std::hex << msg_type
                  << ", req_id=" << std::dec << request_id_);

    // Send request
    int rv = nng_send(socket_, message.data(), message.size(), 0);
    if (rv != 0) {
        throw std::runtime_error("Send failed: " + std::string(nng_strerror(rv)));
    }

    // Receive response
    char* buf = nullptr;
    size_t buf_size = 0;
    rv = nng_recv(socket_, &buf, &buf_size, NNG_FLAG_ALLOC);
    if (rv != 0) {
        throw std::runtime_error("Receive failed: " + std::string(nng_strerror(rv)));
    }

    // Parse response
    std::vector<uint8_t> response_data(buf, buf + buf_size);
    nng_free(buf, buf_size);

    auto parsed = protocol::ParseMessage(response_data);

    SDK_LOG_DEBUG("Received response type=0x" << std::hex << parsed.msg_id
                  << ", req_id=" << std::dec << parsed.req_id);

    // Verify request ID matches
    if (parsed.req_id != request_id_) {
        SDK_LOG_WARN("Request ID mismatch: expected " << request_id_
                     << ", got " << parsed.req_id);
    }

    // Verify response type
    uint32_t expected_resp_type = protocol::GetResponseMsgID(msg_type);
    if (parsed.msg_id != expected_resp_type) {
        throw std::runtime_error("Unexpected response type: expected 0x" +
                                 std::to_string(expected_resp_type) + ", got 0x" +
                                 std::to_string(parsed.msg_id));
    }

    return {parsed.msg_id, parsed.body};
}

// ========== NNGServer Implementation ==========

NNGServer::NNGServer(const std::string& address, int timeout_ms)
    : address_(address),
      timeout_ms_(timeout_ms),
      socket_(NNG_SOCKET_INITIALIZER),
      running_(false) {
    SDK_LOG_INFO("NNGServer created for address: " << address_);
}

NNGServer::~NNGServer() {
    Stop();
}

void NNGServer::SetHandler(Handler handler) {
    handler_ = std::move(handler);
}

void NNGServer::Start() {
    if (running_) {
        return;
    }

    SDK_LOG_INFO("Starting NNG server on: " << address_);

    // Create REP socket
    int rv = nng_rep0_open(&socket_);
    if (rv != 0) {
        throw std::runtime_error("Failed to create socket: " + std::string(nng_strerror(rv)));
    }

    // Set receive timeout for responsive shutdown
    nng_socket_set_ms(socket_, NNG_OPT_RECVTIMEO, 1000);

    // Listen on address
    rv = nng_listen(socket_, address_.c_str(), nullptr, 0);
    if (rv != 0) {
        nng_close(socket_);
        throw std::runtime_error("Failed to listen: " + std::string(nng_strerror(rv)));
    }

    running_ = true;
    server_thread_ = std::thread(&NNGServer::ServeLoop, this);

    SDK_LOG_INFO("NNG server started on: " << address_);
}

void NNGServer::Stop() {
    if (!running_) {
        return;
    }

    SDK_LOG_INFO("Stopping NNG server...");
    running_ = false;

    if (server_thread_.joinable()) {
        server_thread_.join();
    }

    nng_close(socket_);
    socket_ = NNG_SOCKET_INITIALIZER;

    SDK_LOG_INFO("NNG server stopped");
}

bool NNGServer::IsRunning() const {
    return running_;
}

void NNGServer::ServeLoop() {
    while (running_) {
        char* buf = nullptr;
        size_t buf_size = 0;

        int rv = nng_recv(socket_, &buf, &buf_size, NNG_FLAG_ALLOC);
        if (rv != 0) {
            // Timeout is expected for responsive shutdown
            if (rv == NNG_ETIMEDOUT) {
                continue;
            }
            if (running_) {
                SDK_LOG_DEBUG("Server receive error: " << nng_strerror(rv));
            }
            continue;
        }

        // Parse message
        std::vector<uint8_t> request_data(buf, buf + buf_size);
        nng_free(buf, buf_size);

        protocol::ParsedMessage parsed;
        try {
            parsed = protocol::ParseMessage(request_data);
        } catch (const std::exception& e) {
            SDK_LOG_ERROR("Failed to parse message: " << e.what());
            continue;
        }

        SDK_LOG_DEBUG("Received request type=0x" << std::hex << parsed.msg_id
                      << ", req_id=" << std::dec << parsed.req_id);

        // Handle request
        std::vector<uint8_t> response_body;
        if (handler_) {
            try {
                response_body = handler_(parsed.msg_id, parsed.req_id, parsed.body);
            } catch (const std::exception& e) {
                SDK_LOG_ERROR("Handler error: " << e.what());
                response_body.clear();
            }
        }

        // Build response
        uint32_t resp_msg_type = protocol::GetResponseMsgID(parsed.msg_id);
        auto response = protocol::NewMessage(resp_msg_type, parsed.req_id, response_body);

        // Send response
        rv = nng_send(socket_, response.data(), response.size(), 0);
        if (rv != 0) {
            SDK_LOG_ERROR("Failed to send response: " << nng_strerror(rv));
        }

        SDK_LOG_DEBUG("Sent response type=0x" << std::hex << resp_msg_type
                      << ", req_id=" << std::dec << parsed.req_id);
    }
}

}  // namespace sdk
}  // namespace croupier
