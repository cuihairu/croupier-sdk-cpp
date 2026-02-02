#include "mock_agent.h"
#include <ctime>
#include <iostream>

namespace croupier {
namespace test {

MockAgent::MockAgent(const std::string& server_address)
    : server_address_(server_address),
      running_(false),
      register_call_count_(0) {}

MockAgent::~MockAgent() {
    Stop();
}

bool MockAgent::Start() {
    if (running_) {
        std::cerr << "MockAgent already running" << std::endl;
        return true;
    }

    // Create service implementation
    service_ = std::make_unique<LocalControlServiceImpl>(this);

    // Build gRPC server
    grpc::ServerBuilder builder;
    int selected_port = 0;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials(), &selected_port);
    builder.RegisterService(service_.get());

    // Add reuse port option to help with port conflicts between test runs
    builder.AddChannelArgument(GRPC_ARG_ALLOW_REUSEPORT, 1);

    // Create and start server
    server_ = builder.BuildAndStart();
    if (!server_) {
        std::cerr << "Failed to start MockAgent on " << server_address_ << std::endl;
        return false;
    }

    // Update actual address with the real port
    actual_address_ = "127.0.0.1:" + std::to_string(selected_port);

    running_ = true;
    std::cout << "MockAgent started on " << actual_address_ << std::endl;
    return true;
}

void MockAgent::Stop() {
    if (!running_) {
        return;
    }

    std::cout << "Stopping MockAgent..." << std::endl;

    if (server_) {
        // For tests, use immediate shutdown (no graceful wait)
        server_->Shutdown(gpr_time_0(GPR_CLOCK_REALTIME));
        // Don't use Wait() as it can block indefinitely in test scenarios
        server_.reset();
    }

    service_.reset();
    running_ = false;

    std::cout << "MockAgent stopped" << std::endl;
}

}  // namespace test
}  // namespace croupier
