/**
 * @file tcp_transport.h
 * @brief TCP Transport Layer for Croupier C++ SDK.
 *
 * Implements TCP-based transport for communication with Croupier Agent
 * using the Croupier wire protocol with multiplexed request/response.
 */

#ifndef CROUPIER_SDK_TCP_TRANSPORT_H
#define CROUPIER_SDK_TCP_TRANSPORT_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET socket_t;
#define INVALID_SOCKET_VALUE INVALID_SOCKET
#define SOCKET_ERROR_VALUE SOCKET_ERROR
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int socket_t;
#define INVALID_SOCKET_VALUE -1
#define SOCKET_ERROR_VALUE -1
#define closesocket close
#endif

#include "protocol.h"

namespace croupier {
namespace sdk {

/**
 * TCP-based transport client using Croupier wire protocol.
 * Supports multiplexed request/response over a single connection.
 */
class TCPTransport {
public:
    /**
     * Initialize TCP transport.
     *
     * @param host Agent host
     * @param port Agent port
     * @param timeout_ms Request timeout in milliseconds
     */
    TCPTransport(const std::string& host = "127.0.0.1",
                 int port = 19090,
                 int timeout_ms = 30000);

    ~TCPTransport();

    // Non-copyable
    TCPTransport(const TCPTransport&) = delete;
    TCPTransport& operator=(const TCPTransport&) = delete;

    // Movable
    TCPTransport(TCPTransport&& other) noexcept;
    TCPTransport& operator=(TCPTransport&& other) noexcept;

    /**
     * Connect to the TCP server (Agent).
     */
    void Connect();

    /**
     * Close the connection.
     */
    void Close();

    /**
     * Check if connected.
     */
    bool IsConnected() const;

    /**
     * Send a request and wait for response.
     *
     * @param msg_type Protocol message type (e.g., MSG_INVOKE_REQUEST)
     * @param data Protobuf serialized request body
     * @return Pair of (response_msg_type, response_data)
     * @throws std::runtime_error if not connected or request fails
     */
    std::pair<uint32_t, std::vector<uint8_t>> Call(uint32_t msg_type,
                                                    const std::vector<uint8_t>& data);

private:
    struct ResponseLatch {
        std::mutex mutex;
        std::condition_variable cv;
        std::vector<uint8_t> body;
        uint32_t msg_id = 0;
        bool ready = false;

        bool Wait(int timeout_ms) {
            std::unique_lock<std::mutex> lock(mutex);
            return cv.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                              [this] { return ready; });
        }

        void Signal(std::vector<uint8_t> b, uint32_t mid) {
            std::lock_guard<std::mutex> lock(mutex);
            body = std::move(b);
            msg_id = mid;
            ready = true;
            cv.notify_one();
        }
    };

    void ReadLoop();
    int ReadFully(void* buf, size_t count);
    static void PutMsgId(uint8_t* buf, uint32_t msg_id);
    static uint32_t GetMsgId(const uint8_t* buf);

    std::string host_;
    int port_;
    int timeout_ms_;
    socket_t socket_;
    std::atomic<bool> connected_;
    std::atomic<bool> closing_;
    std::atomic<uint32_t> next_req_id_;
    std::unordered_map<uint32_t, std::unique_ptr<ResponseLatch>> pending_responses_;
    std::mutex pending_mutex_;
    std::thread read_thread_;

    static constexpr size_t FRAME_HEADER_BYTES = 4;
    static constexpr size_t PROTOCOL_HEADER_SIZE = 8;
    static constexpr size_t MAX_FRAME_BYTES = 32 * 1024 * 1024; // 32 MB
    static constexpr uint8_t VERSION_1 = 0x01;

#ifdef _WIN32
    static bool ws_initialized_;
    static std::mutex ws_init_mutex_;
#endif
};

} // namespace sdk
} // namespace croupier

#endif // CROUPIER_SDK_TCP_TRANSPORT_H
