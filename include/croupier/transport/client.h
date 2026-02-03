// Croupier C++ SDK - Transport Layer (NNG Client)
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#ifndef CROUPIER_TRANSPORT_CLIENT_H
#define CROUPIER_TRANSPORT_CLIENT_H

#include "croupier/protocol/message.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>

// Forward declarations for NNG types
struct nng_socket;

namespace croupier {
namespace transport {

/**
 * @brief Configuration for NNG client
 */
struct ClientConfig {
    std::string address = "127.0.0.1:19091";  // Agent address
    int dial_timeout = 5000;                   // Dial timeout in ms
    int send_timeout = 5000;                   // Send timeout in ms
    int recv_timeout = 30000;                  // Receive timeout in ms
    bool enable_tls = false;                   // Enable TLS

    // TLS configuration
    std::string ca_file;
    std::string cert_file;
    std::string key_file;
    std::string server_name;
    bool skip_verify = false;
};

/**
 * @brief Asynchronous call result
 */
struct CallResult {
    bool success = false;
    std::vector<uint8_t> body;
    std::string error_msg;
};

/**
 * @brief NNG-based REQ client for Agent communication
 *
 * Uses nanomsg REQ/REP pattern for synchronous request/response.
 */
class Client {
public:
    using ResponseCallback = std::function<void(const CallResult&)>;

    Client();
    explicit Client(const ClientConfig& config);
    ~Client();

    // Disable copy, enable move
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;

    /**
     * @brief Connect to the server
     * @return true on success
     */
    bool Connect();

    /**
     * @brief Disconnect from the server
     */
    void Disconnect();

    /**
     * @brief Check if connected
     */
    bool IsConnected() const { return connected_; }

    /**
     * @brief Synchronous call - send request and wait for response
     * @param msg_id Message type ID
     * @param request Request body
     * @param response Output response body
     * @param timeout_ms Timeout in milliseconds (0 = use default, -1 = infinite)
     * @return true on success
     */
    bool Call(
        uint32_t msg_id,
        const std::vector<uint8_t>& request,
        std::vector<uint8_t>& response,
        int timeout_ms = 0
    );

    /**
     * @brief Asynchronous call - send request and invoke callback on response
     * @param msg_id Message type ID
     * @param request Request body
     * @param callback Callback to invoke when response arrives
     * @return true if request was sent successfully
     */
    bool CallAsync(
        uint32_t msg_id,
        const std::vector<uint8_t>& request,
        ResponseCallback callback
    );

    /**
     * @brief Get configuration
     */
    const ClientConfig& GetConfig() const { return config_; }

    /**
     * @brief Set configuration (must be called before Connect)
     */
    void SetConfig(const ClientConfig& config);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
    ClientConfig config_;
    std::atomic<bool> connected_;

    // Request ID generation
    static uint32_t NextRequestID();
};

/**
 * @brief RAII helper for client connection
 */
class ClientGuard {
public:
    explicit ClientGuard(Client& client) : client_(client) {}
    ~ClientGuard() { client_.Disconnect(); }
private:
    Client& client_;
};

} // namespace transport
} // namespace croupier

#endif // CROUPIER_TRANSPORT_CLIENT_H
