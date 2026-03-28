#include <gtest/gtest.h>

#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/nng_transport.h"
#include "croupier/sdk/protocol.h"
#include "croupier/sdk/v1/invocation.pb.h"

#include <chrono>
#include <random>
#include <thread>
#include <unordered_map>

namespace croupier {
namespace sdk {
namespace test {

namespace {

std::string GetTestAddress() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(17001, 18000);
    return "tcp://127.0.0.1:" + std::to_string(dis(gen));
}

std::vector<uint8_t> SerializeMessage(const google::protobuf::Message& message) {
    std::string bytes;
    if (!message.SerializeToString(&bytes)) {
        throw std::runtime_error("failed to serialize protobuf message");
    }
    return std::vector<uint8_t>(bytes.begin(), bytes.end());
}

template <typename T>
T ParseMessage(const std::vector<uint8_t>& bytes) {
    T message;
    if (!message.ParseFromArray(bytes.data(), static_cast<int>(bytes.size()))) {
        throw std::runtime_error("failed to parse protobuf message");
    }
    return message;
}

}  // namespace

class InvokerTest : public ::testing::Test {
protected:
    void SetUp() override {
        server_address_ = GetTestAddress();
    }

    std::string server_address_;
};

TEST_F(InvokerTest, InvokeUsesNNGProtocol) {
    NNGServer server(server_address_);
    server.SetHandler([](uint32_t msg_type, uint32_t, const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        EXPECT_EQ(msg_type, protocol::MSG_INVOKE_REQUEST);

        auto request = ParseMessage<croupier::sdk::v1::InvokeRequest>(body);
        EXPECT_EQ(request.function_id(), "player.echo");
        EXPECT_EQ(request.payload(), R"({"name":"alice"})");
        EXPECT_EQ(request.metadata().at("trace_id"), "trace-1");
        EXPECT_EQ(request.metadata().at("X-Game-ID"), "test-game");

        croupier::sdk::v1::InvokeResponse response;
        response.set_payload(std::string("ok:") + request.payload());
        return SerializeMessage(response);
    });
    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    InvokerConfig config;
    config.address = server_address_;
    config.game_id = "test-game";
    config.env = "testing";
    config.disable_logging = true;
    CroupierInvoker invoker(config);

    InvokeOptions options;
    options.trace_id = "trace-1";
    std::string result = invoker.Invoke("player.echo", R"({"name":"alice"})", options);

    EXPECT_EQ(result, R"(ok:{"name":"alice"})");

    invoker.Close();
    server.Stop();
}

TEST_F(InvokerTest, StartJobAndStreamJobPollsRemoteEvents) {
    NNGServer server(server_address_);
    std::unordered_map<std::string, int> stream_counts;

    server.SetHandler([&stream_counts](uint32_t msg_type, uint32_t, const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        if (msg_type == protocol::MSG_START_JOB_REQUEST) {
            auto request = ParseMessage<croupier::sdk::v1::InvokeRequest>(body);
            EXPECT_EQ(request.function_id(), "player.batch");

            croupier::sdk::v1::StartJobResponse response;
            response.set_job_id("job-123");
            return SerializeMessage(response);
        }

        if (msg_type == protocol::MSG_STREAM_JOB_REQUEST) {
            auto request = ParseMessage<croupier::sdk::v1::JobStreamRequest>(body);
            int count = ++stream_counts[request.job_id()];

            croupier::sdk::v1::JobEvent event;
            if (count == 1) {
                event.set_type("progress");
                event.set_message("halfway");
                event.set_progress(50);
            } else {
                event.set_type("done");
                event.set_message("completed");
                event.set_progress(100);
                event.set_payload(R"({"ok":true})");
            }
            return SerializeMessage(event);
        }

        return {};
    });
    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    InvokerConfig config;
    config.address = server_address_;
    config.disable_logging = true;
    CroupierInvoker invoker(config);

    std::string job_id = invoker.StartJob("player.batch", R"({"ids":[1,2,3]})");
    EXPECT_EQ(job_id, "job-123");

    auto future = invoker.StreamJob(job_id);
    auto events = future.get();

    ASSERT_GE(events.size(), 3U);
    EXPECT_EQ(events.front().event_type, "started");
    EXPECT_EQ(events[1].event_type, "progress");
    EXPECT_EQ(events.back().event_type, "done");
    EXPECT_TRUE(events.back().done);
    EXPECT_EQ(events.back().payload, R"({"ok":true})");

    invoker.Close();
    server.Stop();
}

TEST_F(InvokerTest, CancelJobSendsProtocolRequest) {
    NNGServer server(server_address_);
    bool cancel_called = false;

    server.SetHandler([&cancel_called](uint32_t msg_type, uint32_t, const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        if (msg_type == protocol::MSG_START_JOB_REQUEST) {
            croupier::sdk::v1::StartJobResponse response;
            response.set_job_id("job-cancel");
            return SerializeMessage(response);
        }

        if (msg_type == protocol::MSG_CANCEL_JOB_REQUEST) {
            auto request = ParseMessage<croupier::sdk::v1::CancelJobRequest>(body);
            EXPECT_EQ(request.job_id(), "job-cancel");
            cancel_called = true;

            croupier::sdk::v1::InvokeResponse response;
            return SerializeMessage(response);
        }

        return {};
    });
    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    InvokerConfig config;
    config.address = server_address_;
    config.disable_logging = true;
    CroupierInvoker invoker(config);

    std::string job_id = invoker.StartJob("player.batch", "{}");
    EXPECT_TRUE(invoker.CancelJob(job_id));

    auto events = invoker.StreamJob(job_id).get();
    ASSERT_GE(events.size(), 2U);
    EXPECT_EQ(events.back().event_type, "cancelled");
    EXPECT_TRUE(events.back().done);
    EXPECT_TRUE(cancel_called);

    invoker.Close();
    server.Stop();
}

TEST_F(InvokerTest, SetSchemaValidatesPayloadBeforeSending) {
    InvokerConfig config;
    config.address = server_address_;
    config.disable_logging = true;
    CroupierInvoker invoker(config);

    invoker.SetSchema("player.create", {
        {"type", "object"},
        {"required", R"(["name"])"}
    });

    EXPECT_THROW(invoker.Invoke("player.create", R"({"id":1})"), std::runtime_error);
    invoker.Close();
}

}  // namespace test
}  // namespace sdk
}  // namespace croupier
