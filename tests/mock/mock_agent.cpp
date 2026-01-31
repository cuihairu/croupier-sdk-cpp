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
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    builder.RegisterService(service_.get());

    // Create and start server
    server_ = builder.BuildAndStart();
    if (!server_) {
        std::cerr << "Failed to start MockAgent on " << server_address_ << std::endl;
        return false;
    }

    running_ = true;
    std::cout << "MockAgent started on " << server_address_ << std::endl;
    return true;
}

void MockAgent::Stop() {
    if (!running_) {
        return;
    }

    std::cout << "Stopping MockAgent..." << std::endl;

    if (server_) {
        server_->Shutdown();
        server_->Wait();
        server_.reset();
    }

    service_.reset();
    running_ = false;

    std::cout << "MockAgent stopped" << std::endl;
}

}  // namespace test
}  // namespace croupier
