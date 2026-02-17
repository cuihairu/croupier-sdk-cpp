#include <gtest/gtest.h>
#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/config_manager.h"
#include <thread>
#include <chrono>

using namespace croupier::sdk;

// Edge case tests for coverage improvement

class EdgeCasesTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(EdgeCasesTest, ClientConfig_DefaultValues) {
    auto config = std::make_shared<ClientConfig>();

    // Verify all default values are set appropriately
    ASSERT_FALSE(config->get_agent_addr().empty());
    ASSERT_FALSE(config->get_env().empty());
    ASSERT_GE(config->get_timeout_seconds(), 0);
}

TEST_F(EdgeCasesTest, ClientConfig_CopySemantics) {
    ClientConfig config1;
    config1.set_agent_addr("localhost:19090");
    config1.set_game_id("test-game");
    config1.set_service_id("test-service");
    config1.set_timeout_seconds(30);

    // Copy constructor
    ClientConfig config2 = config1;

    EXPECT_EQ(config1.get_agent_addr(), config2.get_agent_addr());
    EXPECT_EQ(config1.get_game_id(), config2.get_game_id());
    EXPECT_EQ(config1.get_service_id(), config2.get_service_id());
    EXPECT_EQ(config1.get_timeout_seconds(), config2.get_timeout_seconds());
}

TEST_F(EdgeCasesTest, ClientConfig_MoveSemantics) {
    ClientConfig config1;
    config1.set_agent_addr("localhost:19090");
    config1.set_game_id("test-game");

    // Move constructor
    ClientConfig config2 = std::move(config1);

    EXPECT_EQ("localhost:19090", config2.get_agent_addr());
    EXPECT_EQ("test-game", config2.get_game_id());
}

TEST_F(EdgeCasesTest, ClientConfig_EdgeValues) {
    ClientConfig config;

    // Test with empty strings
    config.set_agent_addr("");
    EXPECT_TRUE(config.get_agent_addr().empty());

    // Test with very long strings
    std::string long_addr(10000, 'a');
    config.set_agent_addr(long_addr);
    EXPECT_EQ(long_addr, config.get_agent_addr());

    // Test with zero timeout
    config.set_timeout_seconds(0);
    EXPECT_EQ(0, config.get_timeout_seconds());

    // Test with very large timeout
    config.set_timeout_seconds(INT_MAX);
    EXPECT_EQ(INT_MAX, config.get_timeout_seconds());
}

TEST_F(EdgeCasesTest, ClientConfig_BooleanFlags) {
    ClientConfig config;

    // Test insecure flag
    config.set_insecure(true);
    EXPECT_TRUE(config.is_insecure());

    config.set_insecure(false);
    EXPECT_FALSE(config.is_insecure());

    // Test logging flags
    config.set_disable_logging(true);
    EXPECT_TRUE(config.is_disable_logging());

    config.set_debug_logging(true);
    EXPECT_TRUE(config.is_debug_logging());
}

TEST_F(EdgeCasesTest, ClientConfig_TLSFields) {
    ClientConfig config;

    config.set_insecure(false);
    config.set_ca_file("/path/to/ca.pem");
    config.set_cert_file("/path/to/cert.pem");
    config.set_key_file("/path/to/key.pem");
    config.set_server_name("example.com");

    EXPECT_EQ("/path/to/ca.pem", config.get_ca_file());
    EXPECT_EQ("/path/to/cert.pem", config.get_cert_file());
    EXPECT_EQ("/path/to/key.pem", config.get_key_file());
    EXPECT_EQ("example.com", config.get_server_name());
}

TEST_F(EdgeCasesTest, ClientConfig_ProviderFields) {
    ClientConfig config;

    config.set_provider_lang("cpp");
    config.set_provider_sdk("croupier-cpp-sdk");

    EXPECT_EQ("cpp", config.get_provider_lang());
    EXPECT_EQ("croupier-cpp-sdk", config.get_provider_sdk());
}

TEST_F(EdgeCasesTest, ClientConfig_MultipleSets) {
    ClientConfig config;

    // Test setting the same field multiple times
    config.set_agent_addr("addr1");
    config.set_agent_addr("addr2");
    config.set_agent_addr("addr3");

    EXPECT_EQ("addr3", config.get_agent_addr());

    config.set_game_id("game1");
    config.set_game_id("game2");
    EXPECT_EQ("game2", config.get_game_id());
}

TEST_F(EdgeCasesTest, ClientConfig_SpecialCharacters) {
    ClientConfig config;

    // Test with special characters in strings
    config.set_agent_addr("tcp://127.0.0.1:19090?param=value&other=123");
    EXPECT_EQ("tcp://127.0.0.1:19090?param=value&other=123", config.get_agent_addr());

    config.set_game_id("game_with-special.chars@123#");
    EXPECT_EQ("game_with-special.chars@123#", config.get_game_id());
}

TEST_F(EdgeCasesTest, ClientConfig_Unicode) {
    ClientConfig config;

    // Test with Unicode characters
    config.set_game_id("游戏-123");
    config.set_service_id("服务-456");

    EXPECT_EQ("游戏-123", config.get_game_id());
    EXPECT_EQ("服务-456", config.get_service_id());
}

TEST_F(EdgeCasesTest, ClientConfig_CopyAssignment) {
    ClientConfig config1;
    config1.set_agent_addr("localhost:19090");
    config1.set_game_id("game1");

    ClientConfig config2;
    config2 = config1;  // Copy assignment

    EXPECT_EQ(config1.get_agent_addr(), config2.get_agent_addr());
    EXPECT_EQ(config1.get_game_id(), config2.get_game_id());
}

TEST_F(EdgeCasesTest, ClientConfig_SelfAssignment) {
    ClientConfig config;
    config.set_agent_addr("localhost:19090");

    // Self assignment
    config = config;

    EXPECT_EQ("localhost:19090", config.get_agent_addr());
}

TEST_F(EdgeCasesTest, ClientConfig_ChainedSetters) {
    ClientConfig config;

    config
        .set_agent_addr("localhost:19090")
        .set_game_id("test-game")
        .set_service_id("test-service")
        .set_timeout_seconds(60)
        .set_insecure(true);

    EXPECT_EQ("localhost:19090", config.get_agent_addr());
    EXPECT_EQ("test-game", config.get_game_id());
    EXPECT_EQ("test-service", config.get_service_id());
    EXPECT_EQ(60, config.get_timeout_seconds());
    EXPECT_TRUE(config.is_insecure());
}

// Test for concurrent config access
TEST_F(EdgeCasesTest, ClientConfig_ConcurrentAccess) {
    auto config = std::make_shared<ClientConfig>();

    const int num_threads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([config, i]() {
            for (int j = 0; j < 100; j++) {
                config->set_agent_addr("addr" + std::to_string(i) + "-" + std::to_string(j));
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Just verify no crash occurred
    ASSERT_TRUE(true);
}

// Test for empty/zero defaults
TEST_F(EdgeCasesTest, ClientConfig_ZeroDefaults) {
    ClientConfig config;

    // All string fields should be empty by default
    EXPECT_TRUE(config.get_game_id().empty());
    EXPECT_TRUE(config.get_service_id().empty());
    EXPECT_TRUE(config.get_agent_id().empty());
    EXPECT_TRUE(config.get_local_listen().empty());
    EXPECT_TRUE(config.get_control_addr().empty());
    EXPECT_TRUE(config.get_ca_file().empty());
    EXPECT_TRUE(config.get_cert_file().empty());
    EXPECT_TRUE(config.get_key_file().empty());
    EXPECT_TRUE(config.get_server_name().empty());
}

// Test for environment variations
TEST_F(EdgeCasesTest, ClientConfig_AllEnvironments) {
    std::vector<std::string> envs = {
        "development",
        "staging",
        "production",
        "testing",
        "local",
        "ci",
        "dev"
    };

    for (const auto& env : envs) {
        ClientConfig config;
        config.set_env(env);
        EXPECT_EQ(env, config.get_env());
    }
}

// Test for timeout variations
TEST_F(EdgeCasesTest, ClientConfig_TimeoutVariations) {
    std::vector<int> timeouts = {0, 1, 10, 30, 60, 120, 300, 3600, INT_MAX};

    for (auto timeout : timeouts) {
        ClientConfig config;
        config.set_timeout_seconds(timeout);
        EXPECT_EQ(timeout, config.get_timeout_seconds());
    }
}

// Test for address format variations
TEST_F(EdgeCasesTest, ClientConfig_AddressFormats) {
    std::vector<std::string> addresses = {
        "localhost:19090",
        "127.0.0.1:19090",
        "0.0.0.0:19090",
        "example.com:19090",
        "192.168.1.1:19090",
        "tcp://localhost:19090",
        "ipc://croupier-agent",
        "inproc://test"
    };

    for (const auto& addr : addresses) {
        ClientConfig config;
        config.set_agent_addr(addr);
        EXPECT_EQ(addr, config.get_agent_addr());
    }
}

// Test for version strings
TEST_F(EdgeCasesTest, ClientConfig_VersionFormats) {
    std::vector<std::string> versions = {
        "1.0.0",
        "2.1.3",
        "0.0.1",
        "10.20.30",
        "1.0.0-beta",
        "2.0.0-rc1",
        "3.0.0-SNAPSHOT"
    };

    for (const auto& version : versions) {
        ClientConfig config;
        config.set_service_version(version);
        EXPECT_EQ(version, config.get_service_version());
    }
}

// Test for client lifecycle without actual connection
TEST_F(EdgeCasesTest, Client_Lifecycle) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");
    config->set_game_id("test-game");
    config->set_service_id("test-service");

    auto client = std::make_shared<CroupierClient>(config);

    // Get local address without connecting
    std::string local_addr = client->get_local_address();
    // Should be empty or some default value

    // Multiple calls to get local address
    std::string local_addr2 = client->get_local_address();
    EXPECT_EQ(local_addr, local_addr2);
}

// Stress test for rapid config changes
TEST_F(EdgeCasesTest, ClientConfig_RapidChanges) {
    ClientConfig config;

    for (int i = 0; i < 10000; i++) {
        config.set_agent_addr("addr" + std::to_string(i));
        config.set_timeout_seconds(i % 100);
        config.set_insecure(i % 2 == 0);
    }

    // Last values should be retained
    EXPECT_EQ("addr9999", config.get_agent_addr());
    EXPECT_EQ(99, config.get_timeout_seconds());
    EXPECT_TRUE(config.is_insecure());
}
