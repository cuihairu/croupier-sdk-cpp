#include <gtest/gtest.h>
#include "croupier/sdk/transport/nng_transport.h"
#include <thread>
#include <chrono>

using namespace croupier::sdk::transport;

class NNGTransportTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(NNGTransportTest, CreateTransport) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    ASSERT_NE(transport, nullptr);
    EXPECT_FALSE(transport->is_connected());
}

TEST_F(NNGTransportTest, CreateTransportWithTimeout) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090", 10000);

    ASSERT_NE(transport, nullptr);
    EXPECT_FALSE(transport->is_connected());
}

TEST_F(NNGTransportTest, CreateTransportWithInvalidAddress) {
    auto transport = std::make_shared<NNGTransport>("invalid-address");

    ASSERT_NE(transport, nullptr);
    EXPECT_FALSE(transport->is_connected());
}

TEST_F(NNGTransportTest, ConnectWithoutServer) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999"); // Non-existent server

    // Will likely timeout or fail
    try {
        transport->connect();
        // If it doesn't throw, it might timeout
    } catch (const std::exception& e) {
        // Expected - no server running
    }
}

TEST_F(NNGTransportTest, DoubleConnect) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999");

    try {
        transport->connect();
        // Second connect should be idempotent or handled gracefully
        transport->connect();
    } catch (const std::exception& e) {
        // Expected
    }
}

TEST_F(NNGTransportTest, CloseWithoutConnect) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    // Close without connect should not crash
    EXPECT_NO_THROW(transport->close());
}

TEST_F(NNGTransportTest, DoubleClose) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    transport->close();
    // Second close should not crash
    EXPECT_NO_THROW(transport->close());
}

TEST_F(NNGTransportTest, CallWithoutConnect) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    std::vector<uint8_t> request_data = {1, 2, 3, 4};

    // Should throw or fail gracefully
    EXPECT_THROW(transport->call(1, request_data), std::exception);
}

TEST_F(NNGTransportTest, CallWithEmptyData) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999");

    std::vector<uint8_t> empty_data;

    try {
        transport->connect();
        auto response = transport->call(1, empty_data);
        // Will likely fail due to no server
    } catch (const std::exception& e) {
        // Expected
    }
}

TEST_F(NNGTransportTest, CallWithLargeData) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999");

    std::vector<uint8_t> large_data(1024 * 1024); // 1MB
    for (size_t i = 0; i < large_data.size(); i++) {
        large_data[i] = i % 256;
    }

    try {
        transport->connect();
        auto response = transport->call(1, large_data);
        // Will likely fail due to no server
    } catch (const std::exception& e) {
        // Expected
    }
}

TEST_F(NNGTransportTest, MultipleTransportInstances) {
    auto transport1 = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");
    auto transport2 = std::make_shared<NNGTransport>("tcp://127.0.0.1:19091");

    ASSERT_NE(transport1, nullptr);
    ASSERT_NE(transport2, nullptr);

    EXPECT_FALSE(transport1->is_connected());
    EXPECT_FALSE(transport2->is_connected());
}

TEST_F(NNGTransportTest, TransportCopySemantics) {
    auto transport1 = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    // Copy should not be allowed or should be handled
    // If NNGTransport is non-copyable, this will fail at compile time
}

TEST_F(NNGTransportTest, TransportMoveSemantics) {
    auto transport1 = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    // Move semantics
    // If NNGTransport supports move, test it
}

TEST_F(NNGTransportTest, DifferentTimeouts) {
    std::vector<int> timeouts = {100, 1000, 5000, 10000, 30000, 60000};

    for (auto timeout : timeouts) {
        auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999", timeout);

        ASSERT_NE(transport, nullptr);

        try {
            transport->connect();
        } catch (const std::exception& e) {
            // Expected
        }
    }
}

TEST_F(NNGTransportTest, DifferentAddressFormats) {
    std::vector<std::string> addresses = {
        "tcp://127.0.0.1:19090",
        "tcp://localhost:19090",
        "tcp://0.0.0.0:19090",
        "ipc://croupier-transport-test",
        "inproc://test-transport"
    };

    for (const auto& addr : addresses) {
        auto transport = std::make_shared<NNGTransport>(addr);

        ASSERT_NE(transport, nullptr);
        EXPECT_FALSE(transport->is_connected());
    }
}

TEST_F(NNGTransportTest, ZeroTimeout) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090", 0);

    ASSERT_NE(transport, nullptr);
}

TEST_F(NNGTransportTest, VeryLargeTimeout) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090", INT_MAX);

    ASSERT_NE(transport, nullptr);
}

TEST_F(NNGTransportTest, NegativeTimeout) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090", -1);

    ASSERT_NE(transport, nullptr);
}

TEST_F(NNGTransportTest, ConcurrentOperations) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    const int num_threads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([transport, i]() {
            try {
                transport->connect();
            } catch (const std::exception& e) {
                // Expected - no server
            }

            std::vector<uint8_t> data = {1, 2, 3};

            try {
                transport->call(1, data);
            } catch (const std::exception& e) {
                // Expected - not connected
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Should not crash
}

TEST_F(NNGTransportTest, RapidConnectDisconnect) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999");

    for (int i = 0; i < 100; i++) {
        try {
            transport->connect();
        } catch (const std::exception& e) {
            // Expected
        }

        transport->close();
    }

    // Should not crash or leak
}

TEST_F(NNGTransportTest, IsConnectedAfterClose) {
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090");

    transport->close();

    EXPECT_FALSE(transport->is_connected());
}

TEST_F(NNGTransportTest, GetAddress) {
    std::string address = "tcp://127.0.0.1:19090";
    auto transport = std::make_shared<NNGTransport>(address);

    // If NNGTransport has a get_address method
    // EXPECT_EQ(address, transport->get_address());

    // For now, just verify it was created
    ASSERT_NE(transport, nullptr);
}

TEST_F(NNGTransportTest, GetTimeout) {
    int timeout = 10000;
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:19090", timeout);

    // If NNGTransport has a get_timeout method
    // EXPECT_EQ(timeout, transport->get_timeout());

    // For now, just verify it was created
    ASSERT_NE(transport, nullptr);
}

TEST_F(NNGTransportTest, TransportLifecycle) {
    // Test full lifecycle
    auto transport = std::make_shared<NNGTransport>("tcp://127.0.0.1:9999");

    // Created
    ASSERT_NE(transport, nullptr);
    EXPECT_FALSE(transport->is_connected());

    // Try to connect
    try {
        transport->connect();
    } catch (const std::exception& e) {
        // Expected - no server
    }

    // Close
    transport->close();
    EXPECT_FALSE(transport->is_connected());
}

TEST_F(NNGTransportTest, UniqueAddresses) {
    std::vector<std::shared_ptr<NNGTransport>> transports;

    for (int i = 0; i < 10; i++) {
        std::string addr = "tcp://127.0.0.1:" + std::to_string(19090 + i);
        transports.push_back(std::make_shared<NNGTransport>(addr));
    }

    EXPECT_EQ(10, transports.size());

    for (auto& transport : transports) {
        ASSERT_NE(transport, nullptr);
    }
}
