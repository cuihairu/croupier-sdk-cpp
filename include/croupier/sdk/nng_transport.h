/**
 * @file nng_transport.h
 * @brief NNG Transport Layer for Croupier C++ SDK.
 *
 * Implements the NNG (nanomsg-next-gen) based transport for communication
 * with Croupier Agent using REQ/REP pattern.
 */

#ifndef CROUPIER_SDK_NNG_TRANSPORT_H
#define CROUPIER_SDK_NNG_TRANSPORT_H

#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

#include "protocol.h"

namespace croupier {
namespace sdk {

/**
 * NNG-based transport client using REQ/REP pattern.
 *
 * Used for:
 * - Invoker: calling remote functions through Agent
 * - Client: registering functions with local Agent
 */
class NNGTransport {
public:
    /**
     * Initialize NNG transport.
     *
     * @param address NNG address (e.g., "tcp://127.0.0.1:19090")
     * @param timeout_ms Request timeout in milliseconds
     */
    explicit NNGTransport(const std::string& address = "tcp://127.0.0.1:19090",
                          int timeout_ms = 30000);

    ~NNGTransport();

    // Non-copyable
    NNGTransport(const NNGTransport&) = delete;
    NNGTransport& operator=(const NNGTransport&) = delete;

    /**
     * Connect to the NNG server (Agent).
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
    std::string address_;
    int timeout_ms_;
    nng_socket socket_;
    bool connected_;
    std::mutex mutex_;
    uint32_t request_id_;
};

/**
 * NNG-based server using REP/REQ pattern.
 *
 * Used for:
 * - Receiving function registration requests from SDK
 * - Receiving function invocation requests from Invoker
 */
class NNGServer {
public:
    using Handler = std::function<std::vector<uint8_t>(uint32_t, uint32_t, const std::vector<uint8_t>&)>;

    /**
     * Initialize NNG server.
     *
     * @param address NNG address to listen on
     * @param timeout_ms Receive timeout in milliseconds
     */
    explicit NNGServer(const std::string& address = "tcp://127.0.0.1:19090",
                       int timeout_ms = 30000);

    ~NNGServer();

    // Non-copyable
    NNGServer(const NNGServer&) = delete;
    NNGServer& operator=(const NNGServer&) = delete;

    /**
     * Set the message handler.
     *
     * @param handler Function that takes (msg_type, req_id, data) and returns response data
     */
    void SetHandler(Handler handler);

    /**
     * Start the server.
     */
    void Start();

    /**
     * Stop the server.
     */
    void Stop();

    /**
     * Check if server is running.
     */
    bool IsRunning() const;

private:
    void ServeLoop();

    std::string address_;
    int timeout_ms_;
    nng_socket socket_;
    bool running_;
    Handler handler_;
    std::thread server_thread_;
};

}  // namespace sdk
}  // namespace croupier

#endif  // CROUPIER_SDK_NNG_TRANSPORT_H
