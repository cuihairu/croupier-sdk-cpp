// Croupier C++ SDK - Transport Server Implementation
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#include "croupier/transport/server.h"
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <stdexcept>
#include <cstring>
#include <thread>

namespace croupier {
namespace transport {

//=============================================================================
// Server::Impl - Internal implementation using NNG
//=============================================================================

class Server::Impl {
public:
    Impl() : sock_(NNG_SOCKET_INITIALIZER), running_(false) {
        if (nng_rep0_open(&sock_) != 0) {
            throw std::runtime_error("Failed to create REP socket");
        }
    }

    ~Impl() {
        Stop();
    }

    bool Listen(const std::string& addr) {
        std::string url = "tcp://" + addr;
        int ret = nng_listen(sock_, url.c_str(), nullptr, 0);
        return ret == 0;
    }

    bool Receive(std::vector<uint8_t>& data) {
        nng_msg* msg;
        int ret = nng_recvmsg(sock_, &msg, 0);
        if (ret != 0) {
            return false;
        }

        size_t len = nng_msg_len(msg);
        data.assign(static_cast<uint8_t*>(nng_msg_body(msg)),
                    static_cast<uint8_t*>(nng_msg_body(msg)) + len);

        nng_msg_free(msg);
        return true;
    }

    bool Send(const std::vector<uint8_t>& data) {
        nng_msg* msg;
        if (nng_msg_alloc(&msg, data.size()) != 0) {
            return false;
        }

        std::memcpy(nng_msg_body(msg), data.data(), data.size());

        int ret = nng_sendmsg(sock_, msg, 0);
        if (ret != 0) {
            nng_msg_free(msg);
            return false;
        }
        return true;
    }

    void Stop() {
        running_ = false;
        nng_close(sock_);
        sock_ = NNG_SOCKET_INITIALIZER;
    }

    nng_socket sock_;
    std::atomic<bool> running_;
};

//=============================================================================
// Server implementation
//=============================================================================

Server::Server()
    : impl_(std::make_unique<Impl>())
    , running_(false) {}

Server::Server(const ServerConfig& config)
    : impl_(std::make_unique<Impl>())
    , config_(config)
    , running_(false) {}

Server::~Server() {
    Stop();
}

Server::Server(Server&& other) noexcept
    : impl_(std::move(other.impl_))
    , config_(std::move(other.config_))
    , running_(other.running_.load())
    , bound_address_(std::move(other.bound_address_)) {
    other.running_ = false;
}

Server& Server::operator=(Server&& other) noexcept {
    if (this != &other) {
        Stop();
        impl_ = std::move(other.impl_);
        config_ = std::move(other.config_);
        running_ = other.running_.load();
        bound_address_ = std::move(other.bound_address_);
        other.running_ = false;
    }
    return *this;
}

bool Server::Start(RequestHandler handler) {
    if (running_) {
        return false;
    }

    if (!impl_->Listen(config_.bind_address)) {
        return false;
    }

    running_ = true;
    bound_address_ = config_.bind_address;

    // Serve loop
    while (running_) {
        std::vector<uint8_t> data;
        if (!impl_->Receive(data)) {
            if (running_) {
                // Receive failed but still running, continue
                continue;
            }
            break;
        }

        // Parse protocol header
        uint8_t version;
        uint32_t msg_id, req_id;
        std::vector<uint8_t> body;

        if (!protocol::ParseMessage(data, version, msg_id, req_id, body)) {
            // Invalid message, send error response
            continue;
        }

        // Handle request
        std::vector<uint8_t> response_body;
        try {
            response_body = handler(msg_id, req_id, body);
        } catch (const std::exception& e) {
            // Handler threw exception, send empty response
            response_body.clear();
        }

        // Send response with protocol header
        uint32_t response_msg_id = protocol::GetResponseMessageID(msg_id);
        std::vector<uint8_t> response = protocol::CreateResponseMessage(
            response_msg_id,
            req_id,
            response_body
        );

        impl_->Send(response);
    }

    return true;
}

bool Server::StartAsync(RequestHandler handler) {
    if (running_) {
        return false;
    }

    running_ = true;

    serve_thread_ = std::thread([this, handler]() {
        this->Start(handler);
    });

    return true;
}

void Server::Stop() {
    if (!running_) {
        return;
    }

    running_ = false;
    impl_->Stop();

    if (serve_thread_.joinable()) {
        serve_thread_.join();
    }
}

void Server::SetConfig(const ServerConfig& config) {
    if (running_) {
        return;  // Cannot change config while running
    }
    config_ = config;
}

} // namespace transport
} // namespace croupier
