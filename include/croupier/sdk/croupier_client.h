#pragma once

#include <string>

namespace croupier {
namespace sdk {

// C++ SDK skeleton client (no real networking yet)
class CroupierClient {
public:
    explicit CroupierClient(std::string agent_addr) : agent_addr_(std::move(agent_addr)) {}
    void connect() { /* TODO: connect to Agent via gRPC */ }
    const std::string& agent_addr() const { return agent_addr_; }
private:
    std::string agent_addr_;
};

} // namespace sdk
} // namespace croupier

