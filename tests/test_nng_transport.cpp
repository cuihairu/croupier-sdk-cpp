/**
 * @file test_nng_transport.cpp
 * @brief Unit tests for NNG Transport Layer.
 */

#include <gtest/gtest.h>

#include "croupier/sdk/nng_transport.h"
#include "croupier/sdk/protocol.h"

#include <chrono>
#include <random>
#include <thread>

namespace croupier {
namespace sdk {
namespace test {

// Generate a random port for testing
std::string GetTestAddress() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(16000, 17000);
    return "tcp://127.0.0.1:" + std::to_string(dis(gen));
}

class ProtocolTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ProtocolTest, NewMessage) {
    uint32_t msg_type = protocol::MSG_INVOKE_REQUEST;
    uint32_t req_id = 12345;
    std::vector<uint8_t> body = {1, 2, 3, 4, 5};

    auto message = protocol::NewMessage(msg_type, req_id, body);

    EXPECT_EQ(message.size(), protocol::HEADER_SIZE + body.size());
    EXPECT_EQ(message[0], protocol::VERSION_1);
}

TEST_F(ProtocolTest, ParseMessage) {
    uint32_t msg_type = protocol::MSG_REGISTER_LOCAL_REQUEST;
    uint32_t req_id = 999;
    std::vector<uint8_t> body = {'h', 'e', 'l', 'l', 'o'};

    auto message = protocol::NewMessage(msg_type, req_id, body);
    auto parsed = protocol::ParseMessage(message);

    EXPECT_EQ(parsed.version, protocol::VERSION_1);
    EXPECT_EQ(parsed.msg_id, msg_type);
    EXPECT_EQ(parsed.req_id, req_id);
    EXPECT_EQ(parsed.body, body);
}

TEST_F(ProtocolTest, GetResponseMsgID) {
    EXPECT_EQ(protocol::GetResponseMsgID(protocol::MSG_INVOKE_REQUEST),
              protocol::MSG_INVOKE_RESPONSE);
    EXPECT_EQ(protocol::GetResponseMsgID(protocol::MSG_REGISTER_LOCAL_REQUEST),
              protocol::MSG_REGISTER_LOCAL_RESPONSE);
}

TEST_F(ProtocolTest, IsRequest) {
    EXPECT_TRUE(protocol::IsRequest(protocol::MSG_INVOKE_REQUEST));
    EXPECT_TRUE(protocol::IsRequest(protocol::MSG_REGISTER_LOCAL_REQUEST));
    EXPECT_FALSE(protocol::IsRequest(protocol::MSG_INVOKE_RESPONSE));
    EXPECT_FALSE(protocol::IsRequest(protocol::MSG_REGISTER_LOCAL_RESPONSE));
}

TEST_F(ProtocolTest, IsResponse) {
    EXPECT_TRUE(protocol::IsResponse(protocol::MSG_INVOKE_RESPONSE));
    EXPECT_TRUE(protocol::IsResponse(protocol::MSG_REGISTER_LOCAL_RESPONSE));
    EXPECT_FALSE(protocol::IsResponse(protocol::MSG_INVOKE_REQUEST));
    EXPECT_FALSE(protocol::IsResponse(protocol::MSG_REGISTER_LOCAL_REQUEST));
}

TEST_F(ProtocolTest, MsgIDString) {
    EXPECT_EQ(protocol::MsgIDString(protocol::MSG_INVOKE_REQUEST), "InvokeRequest");
    EXPECT_EQ(protocol::MsgIDString(protocol::MSG_INVOKE_RESPONSE), "InvokeResponse");
    EXPECT_EQ(protocol::MsgIDString(protocol::MSG_REGISTER_LOCAL_REQUEST), "RegisterLocalRequest");
    EXPECT_EQ(protocol::MsgIDString(0xFFFFFF), "Unknown(0xFFFFFF)");
}

class NNGTransportTest : public ::testing::Test {
protected:
    std::string server_address_;

    void SetUp() override {
        server_address_ = GetTestAddress();
    }

    void TearDown() override {}
};

TEST_F(NNGTransportTest, ConnectAndClose) {
    NNGServer server(server_address_);
    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    NNGTransport transport(server_address_);
    EXPECT_FALSE(transport.IsConnected());

    transport.Connect();
    EXPECT_TRUE(transport.IsConnected());

    transport.Close();
    EXPECT_FALSE(transport.IsConnected());

    server.Stop();
}

TEST_F(NNGTransportTest, CallAndResponse) {
    NNGServer server(server_address_);

    // Set up server handler
    server.SetHandler([](uint32_t msg_type, uint32_t req_id,
                          const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        // Echo back the body
        return body;
    });

    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    NNGTransport transport(server_address_);
    transport.Connect();

    std::vector<uint8_t> request_data = {1, 2, 3, 4, 5};
    auto [resp_type, resp_data] = transport.Call(protocol::MSG_INVOKE_REQUEST, request_data);

    EXPECT_EQ(resp_type, protocol::MSG_INVOKE_RESPONSE);
    EXPECT_EQ(resp_data, request_data);

    transport.Close();
    server.Stop();
}

TEST_F(NNGTransportTest, MultipleCalls) {
    NNGServer server(server_address_);
    int call_count = 0;

    server.SetHandler([&call_count](uint32_t msg_type, uint32_t req_id,
                                     const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        call_count++;
        return std::vector<uint8_t>(body.begin(), body.end());
    });

    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    NNGTransport transport(server_address_);
    transport.Connect();

    for (int i = 0; i < 5; i++) {
        std::vector<uint8_t> request_data = {static_cast<uint8_t>(i)};
        auto [resp_type, resp_data] = transport.Call(protocol::MSG_INVOKE_REQUEST, request_data);
        EXPECT_EQ(resp_data, request_data);
    }

    EXPECT_EQ(call_count, 5);

    transport.Close();
    server.Stop();
}

TEST_F(NNGTransportTest, NotConnectedError) {
    NNGTransport transport(server_address_);
    // Don't connect

    std::vector<uint8_t> data = {1, 2, 3};
    EXPECT_THROW(transport.Call(protocol::MSG_INVOKE_REQUEST, data), std::runtime_error);
}

class NNGServerTest : public ::testing::Test {
protected:
    std::string server_address_;

    void SetUp() override {
        server_address_ = GetTestAddress();
    }

    void TearDown() override {}
};

TEST_F(NNGServerTest, StartAndStop) {
    NNGServer server(server_address_);

    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(server.IsRunning());

    server.Stop();
    EXPECT_FALSE(server.IsRunning());
}

TEST_F(NNGServerTest, HandlerIsCalled) {
    NNGServer server(server_address_);
    bool handler_called = false;

    server.SetHandler([&handler_called](uint32_t msg_type, uint32_t req_id,
                                          const std::vector<uint8_t>& body) -> std::vector<uint8_t> {
        handler_called = true;
        return body;
    });

    server.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    NNGTransport transport(server_address_);
    transport.Connect();
    transport.Call(protocol::MSG_INVOKE_REQUEST, {1, 2, 3});

    EXPECT_TRUE(handler_called);

    transport.Close();
    server.Stop();
}

}  // namespace test
}  // namespace sdk
}  // namespace croupier

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
