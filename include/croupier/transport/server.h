// Croupier C++ SDK - Transport Layer (NNG Server)
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#ifndef CROUPIER_TRANSPORT_SERVER_H
#define CROUPIER_TRANSPORT_SERVER_H

#include "croupier/protocol/message.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <thread>

namespace croupier {
namespace transport {

/**
 * @brief Request handler callback
 *
 * @param msg_id Message type ID from the request
 * @param req_id Request ID for matching responses
 * @param request Request body data
 * @return Response body data
 */
using RequestHandler = std::function<std::vector<uint8_t>(
    uint32_t msg_id,
    uint32_t req_id,
    const std::vector<uint8_t>& request
)>;

/**
 * @brief Configuration for NNG server
 */
struct ServerConfig {
    std::string bind_address = "0.0.0.0:19091";  // Bind address
    int recv_timeout = 30000;                     // Receive timeout in ms
    int send_timeout = 5000;                      // Send timeout in ms
    bool enable_tls = false;                      // Enable TLS

    // TLS configuration
    std::string ca_file;
    std::string cert_file;
    std::string key_file;

    // Concurrency
    int worker_threads = 1;  // Number of worker threads (0 = auto)
};

/**
 * @brief NNG-based REP server for receiving requests
 *
 * Uses nanomsg REQ/REP pattern to handle incoming requests.
 */
class Server {
public:
    Server();
    explicit Server(const ServerConfig& config);
    ~Server();

    // Disable copy, enable move
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) noexcept;
    Server& operator=(Server&& other) noexcept;

    /**
     * @brief Start the server
     * @param handler Request handler callback
     * @return true on success
     */
    bool Start(RequestHandler handler);

    /**
     * @brief Start server in a background thread
     * @param handler Request handler callback
     * @return true on success
     */
    bool StartAsync(RequestHandler handler);

    /**
     * @brief Stop the server
     */
    void Stop();

    /**
     * @brief Check if server is running
     */
    bool IsRunning() const { return running_; }

    /**
     * @brief Get actual bound address (after Start)
     */
    std::string GetBoundAddress() const { return bound_address_; }

    /**
     * @brief Get configuration
     */
    const ServerConfig& GetConfig() const { return config_; }

    /**
     * @brief Set configuration (must be called before Start)
     */
    void SetConfig(const ServerConfig& config);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
    ServerConfig config_;
    std::atomic<bool> running_;
    std::string bound_address_;
    std::thread serve_thread_;
};

/**
 * @brief RAII helper for server lifetime
 */
class ServerGuard {
public:
    explicit ServerGuard(Server& server) : server_(server) {}
    ~ServerGuard() { server_.Stop(); }
private:
    Server& server_;
};

} // namespace transport
} // namespace croupier

#endif // CROUPIER_TRANSPORT_SERVER_H
