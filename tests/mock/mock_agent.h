#pragma once

#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>
#include <thread>

#include "croupier/agent/local/v1/local.grpc.pb.h"

namespace croupier {
namespace test {

// Mock Agent server for testing
class MockAgent {
public:
    explicit MockAgent(const std::string& server_address = "127.0.0.1:19090");
    ~MockAgent();

    // Start the mock agent server (blocking, runs in background thread)
    bool Start();

    // Stop the mock agent server
    void Stop();

    // Check if the agent is running
    bool IsRunning() const { return running_; }

    // Get the actual server address (with assigned port if using :0)
    std::string GetAddress() const { return server_address_; }

    // Get the number of RegisterLocal calls received
    int GetRegisterCallCount() const { return register_call_count_; }

private:
    // gRPC service implementation
    class LocalControlServiceImpl : public croupier::agent::local::v1::LocalControlService::Service {
    public:
        explicit LocalControlServiceImpl(MockAgent* agent) : agent_(agent) {}

        grpc::Status RegisterLocal(
            grpc::ServerContext* context,
            const croupier::agent::local::v1::RegisterLocalRequest* request,
            croupier::agent::local::v1::RegisterLocalResponse* response) override {
            if (agent_) {
                agent_->register_call_count_++;
            }
            // Generate a session ID
            response->set_session_id("test-session-" + std::to_string(std::time(nullptr)));
            return grpc::Status::OK;
        }

        grpc::Status Heartbeat(
            grpc::ServerContext* context,
            const croupier::agent::local::v1::HeartbeatRequest* request,
            croupier::agent::local::v1::HeartbeatResponse* response) override {
            return grpc::Status::OK;
        }

        grpc::Status ListLocal(
            grpc::ServerContext* context,
            const croupier::agent::local::v1::ListLocalRequest* request,
            croupier::agent::local::v1::ListLocalResponse* response) override {
            return grpc::Status::OK;
        }

        grpc::Status GetJobResult(
            grpc::ServerContext* context,
            const croupier::agent::local::v1::GetJobResultRequest* request,
            croupier::agent::local::v1::GetJobResultResponse* response) override {
            return grpc::Status::OK;
        }

    private:
        MockAgent* agent_;
    };

    std::string server_address_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<LocalControlServiceImpl> service_;
    std::thread server_thread_;
    bool running_;
    int register_call_count_;
};

}  // namespace test
}  // namespace croupier
