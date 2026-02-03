// Croupier C++ SDK - Transport Client Implementation
// Copyright (c) 2025 cuihairu
// Licensed under Apache License 2.0

#include "croupier/transport/client.h"
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <stdexcept>
#include <cstring>
#include <atomic>

namespace croupier {
namespace transport {

//=============================================================================
// Client::Impl - Internal implementation using NNG
//=============================================================================

class Client::Impl {
public:
    Impl() : sock_(NNG_SOCKET_INITIALIZER) {
        if (nng_req0_open(&sock_) != 0) {
            throw std::runtime_error("Failed to create REQ socket");
        }
    }

    ~Impl() {
        Close();
    }

    bool Dial(const std::string& addr) {
        std::string url = "tcp://" + addr;
        int ret = nng_dial(sock_, url.c_str(), nullptr, 0);
        return ret == 0;
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

    bool Receive(std::vector<uint8_t>& data, int timeout_ms) {
        nng_msg* msg;
        nng_time expire = timeout_ms > 0
            ? nng_clock() + static_cast<nng_time>(timeout_ms)
            : NNG_TIME_NEVER;

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

    void Close() {
        nng_close(sock_);
        sock_ = NNG_SOCKET_INITIALIZER;
    }

    nng_socket sock_;
};

//=============================================================================
// Client implementation
//=============================================================================

Client::Client()
    : impl_(std::make_unique<Impl>())
    , connected_(false) {}

Client::Client(const ClientConfig& config)
    : impl_(std::make_unique<Impl>())
    , config_(config)
    , connected_(false) {}

Client::~Client() {
    Disconnect();
}

Client::Client(Client&& other) noexcept
    : impl_(std::move(other.impl_))
    , config_(std::move(other.config_))
    , connected_(other.connected_.load()) {
    other.connected_ = false;
}

Client& Client::operator=(Client&& other) noexcept {
    if (this != &other) {
        Disconnect();
        impl_ = std::move(other.impl_);
        config_ = std::move(other.config_);
        connected_ = other.connected_.load();
        other.connected_ = false;
    }
    return *this;
}

bool Client::Connect() {
    if (connected_) {
        return true;
    }

    connected_ = impl_->Dial(config_.address);
    return connected_;
}

void Client::Disconnect() {
    connected_ = false;
    impl_->Close();
}

bool Client::Call(
    uint32_t msg_id,
    const std::vector<uint8_t>& request,
    std::vector<uint8_t>& response,
    int timeout_ms
) {
    if (!connected_) {
        return false;
    }

    // Encode request with protocol header
    std::vector<uint8_t> encoded = protocol::CreateRequestMessage(
        NextRequestID(),
        msg_id,
        request
    );

    // Send request
    if (!impl_->Send(encoded)) {
        return false;
    }

    // Receive response
    int to = timeout_ms > 0 ? timeout_ms : config_.recv_timeout;
    return impl_->Receive(response, to);
}

bool Client::CallAsync(
    uint32_t msg_id,
    const std::vector<uint8_t>& request,
    ResponseCallback callback
) {
    // For simplicity, implement as sync call + callback invocation
    std::vector<uint8_t> response;
    bool success = Call(msg_id, request, response);

    CallResult result;
    result.success = success;
    if (success) {
        result.body = response;
    } else {
        result.error_msg = "Call failed";
    }

    callback(result);
    return success;
}

void Client::SetConfig(const ClientConfig& config) {
    if (connected_) {
        return;  // Cannot change config while connected
    }
    config_ = config;
}

uint32_t Client::NextRequestID() {
    static std::atomic<uint32_t> next_id{1};
    return next_id.fetch_add(1);
}

} // namespace transport
} // namespace croupier
