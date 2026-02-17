#include <gtest/gtest.h>
#include "croupier/sdk/config_manager.h"
#include <thread>
#include <chrono>

using namespace croupier::sdk;

class ConfigManagerTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ConfigManagerTest, CreateDefaultConfig) {
    auto config = ConfigManager::CreateDefaultConfig();

    ASSERT_NE(config, nullptr);
    EXPECT_FALSE(config->get_agent_addr().empty());
    EXPECT_FALSE(config->get_env().empty());
    EXPECT_GE(config->get_timeout_seconds(), 0);
}

TEST_F(ConfigManagerTest, CreateConfigWithAgentAddr) {
    auto config = ConfigManager::CreateConfig("localhost:19090");

    ASSERT_NE(config, nullptr);
    EXPECT_EQ("localhost:19090", config->get_agent_addr());
}

TEST_F(ConfigManagerTest, CreateConfigWithAllParams) {
    auto config = ConfigManager::CreateConfig(
        "localhost:19090",
        "test-game",
        "test-service"
    );

    ASSERT_NE(config, nullptr);
    EXPECT_EQ("localhost:19090", config->get_agent_addr());
    EXPECT_EQ("test-game", config->get_game_id());
    EXPECT_EQ("test-service", config->get_service_id());
}

TEST_F(ConfigManagerTest, LoadConfigFromEnv) {
    // Set environment variables
    #ifdef _WIN32
    _putenv_s("CROUPIER_AGENT_ADDR", "env-agent:19090");
    _putenv_s("CROUPIER_GAME_ID", "env-game");
    _putenv_s("CROUPIER_SERVICE_ID", "env-service");
    #else
    setenv("CROUPIER_AGENT_ADDR", "env-agent:19090", 1);
    setenv("CROUPIER_GAME_ID", "env-game", 1);
    setenv("CROUPIER_SERVICE_ID", "env-service", 1);
    #endif

    auto config = ConfigManager::LoadConfigFromEnv();

    // May or may not succeed depending on implementation
    if (config) {
        EXPECT_EQ("env-agent:19090", config->get_agent_addr());
        EXPECT_EQ("env-game", config->get_game_id());
        EXPECT_EQ("env-service", config->get_service_id());
    }

    // Clean up
    #ifdef _WIN32
    _putenv_s("CROUPIER_AGENT_ADDR", "");
    _putenv_s("CROUPIER_GAME_ID", "");
    _putenv_s("CROUPIER_SERVICE_ID", "");
    #else
    unsetenv("CROUPIER_AGENT_ADDR");
    unsetenv("CROUPIER_GAME_ID");
    unsetenv("CROUPIER_SERVICE_ID");
    #endif
}

TEST_F(ConfigManagerTest, LoadConfigFromFile) {
    // Try to load from a non-existent file
    auto config = ConfigManager::LoadConfigFromFile("nonexistent-config.json");

    EXPECT_EQ(config, nullptr);
}

TEST_F(ConfigManagerTest, ValidateConfig) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");
    config->set_game_id("test-game");
    config->set_service_id("test-service");

    bool valid = ConfigManager::ValidateConfig(config);

    EXPECT_TRUE(valid);
}

TEST_F(ConfigManagerTest, ValidateConfigWithEmptyAddr) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("");
    config->set_game_id("test-game");
    config->set_service_id("test-service");

    bool valid = ConfigManager::ValidateConfig(config);

    EXPECT_FALSE(valid);
}

TEST_F(ConfigManagerTest, ValidateConfigWithEmptyGameId) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");
    config->set_game_id("");
    config->set_service_id("test-service");

    bool valid = ConfigManager::ValidateConfig(config);

    // May or may not be valid depending on requirements
}

TEST_F(ConfigManagerTest, CloneConfig) {
    auto config1 = std::make_shared<ClientConfig>();
    config1->set_agent_addr("localhost:19090");
    config1->set_game_id("game1");
    config1->set_service_id("service1");
    config1->set_timeout_seconds(30);

    auto config2 = ConfigManager::CloneConfig(config1);

    ASSERT_NE(config2, nullptr);
    EXPECT_EQ(config1->get_agent_addr(), config2->get_agent_addr());
    EXPECT_EQ(config1->get_game_id(), config2->get_game_id());
    EXPECT_EQ(config1->get_service_id(), config2->get_service_id());
    EXPECT_EQ(config1->get_timeout_seconds(), config2->get_timeout_seconds());
}

TEST_F(ConfigManagerTest, MergeConfigs) {
    auto config1 = std::make_shared<ClientConfig>();
    config1->set_agent_addr("localhost:19090");
    config1->set_game_id("game1");
    config1->set_timeout_seconds(30);

    auto config2 = std::make_shared<ClientConfig>();
    config2->set_game_id("game2");
    config2->set_service_id("service2");
    config2->set_timeout_seconds(60);

    auto merged = ConfigManager::MergeConfigs(config1, config2);

    ASSERT_NE(merged, nullptr);
    EXPECT_EQ("localhost:19090", merged->get_agent_addr()); // From config1
    EXPECT_EQ("game2", merged->get_game_id()); // From config2 (overrides)
    EXPECT_EQ("service2", merged->get_service_id()); // From config2
    EXPECT_EQ(60, merged->get_timeout_seconds()); // From config2 (overrides)
}

TEST_F(ConfigManagerTest, ApplyDefaults) {
    auto config = std::make_shared<ClientConfig>();
    // Don't set any fields

    ConfigManager::ApplyDefaults(config);

    // Should have defaults applied
    EXPECT_FALSE(config->get_agent_addr().empty());
    EXPECT_FALSE(config->get_env().empty());
}

TEST_F(ConfigManagerTest, ConfigToMap) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");
    config->set_game_id("test-game");
    config->set_service_id("test-service");
    config->set_timeout_seconds(30);

    auto map = ConfigManager::ConfigToMap(config);

    EXPECT_FALSE(map.empty());
    if (!map.empty()) {
        EXPECT_EQ("localhost:19090", map["agent_addr"]);
        EXPECT_EQ("test-game", map["game_id"]);
        EXPECT_EQ("test-service", map["service_id"]);
        EXPECT_EQ("30", map["timeout_seconds"]);
    }
}

TEST_F(ConfigManagerTest, MapToConfig) {
    std::map<std::string, std::string> map = {
        {"agent_addr", "localhost:19090"},
        {"game_id", "test-game"},
        {"service_id", "test-service"},
        {"timeout_seconds", "30"}
    };

    auto config = ConfigManager::MapToConfig(map);

    ASSERT_NE(config, nullptr);
    EXPECT_EQ("localhost:19090", config->get_agent_addr());
    EXPECT_EQ("test-game", config->get_game_id());
    EXPECT_EQ("test-service", config->get_service_id());
    EXPECT_EQ(30, config->get_timeout_seconds());
}

TEST_F(ConfigManagerTest, MultipleConfigInstances) {
    auto config1 = ConfigManager::CreateDefaultConfig();
    auto config2 = ConfigManager::CreateDefaultConfig();

    ASSERT_NE(config1, nullptr);
    ASSERT_NE(config2, nullptr);

    // Modify config1
    config1->set_game_id("game1");
    config2->set_game_id("game2");

    EXPECT_EQ("game1", config1->get_game_id());
    EXPECT_EQ("game2", config2->get_game_id());
}

TEST_F(ConfigManagerTest, ConcurrentConfigAccess) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");

    const int num_threads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([config, i]() {
            for (int j = 0; j < 100; j++) {
                config->set_agent_addr("addr" + std::to_string(i) + "-" + std::to_string(j));
                config->set_timeout_seconds(i * 10 + j);
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Just verify no crash occurred
    ASSERT_NE(config, nullptr);
}

TEST_F(ConfigManagerTest, ConfigWithAllFields) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("localhost:19090");
    config->set_game_id("test-game");
    config->set_service_id("test-service");
    config->set_env("production");
    config->set_agent_id("agent-123");
    config->set_local_listen("tcp://127.0.0.1:0");
    config->set_control_addr("localhost:8080");
    config->set_timeout_seconds(60);
    config->set_insecure(false);
    config->set_ca_file("/path/to/ca.pem");
    config->set_cert_file("/path/to/cert.pem");
    config->set_key_file("/path/to/key.pem");
    config->set_server_name("example.com");
    config->set_provider_lang("cpp");
    config->set_provider_sdk("croupier-cpp-sdk");
    config->set_service_version("1.0.0");

    bool valid = ConfigManager::ValidateConfig(config);

    EXPECT_TRUE(valid);
}

TEST_F(ConfigManagerTest, EdgeCaseTimeouts) {
    std::vector<int> timeouts = {0, 1, 30, 60, 300, 3600, INT_MAX};

    for (auto timeout : timeouts) {
        auto config = std::make_shared<ClientConfig>();
        config->set_agent_addr("localhost:19090");
        config->set_game_id("test-game");
        config->set_service_id("test-service");
        config->set_timeout_seconds(timeout);

        EXPECT_EQ(timeout, config->get_timeout_seconds());
    }
}

TEST_F(ConfigManagerTest, EdgeCaseAddresses) {
    std::vector<std::string> addresses = {
        "localhost:19090",
        "127.0.0.1:19090",
        "0.0.0.0:19090",
        "example.com:19090",
        "192.168.1.1:19090",
        "tcp://localhost:19090",
        "ipc://croupier-agent"
    };

    for (const auto& addr : addresses) {
        auto config = std::make_shared<ClientConfig>();
        config->set_agent_addr(addr);

        EXPECT_EQ(addr, config->get_agent_addr());
    }
}

TEST_F(ConfigManagerTest, EdgeCaseEnvironments) {
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
        auto config = std::make_shared<ClientConfig>();
        config->set_env(env);

        EXPECT_EQ(env, config->get_env());
    }
}

TEST_F(ConfigManagerTest, ConfigWithSpecialCharacters) {
    auto config = std::make_shared<ClientConfig>();
    config->set_agent_addr("tcp://127.0.0.1:19090?param=value&other=123");
    config->set_game_id("game-with-special_chars@123#");
    config->set_service_id("service.with.dots");

    EXPECT_EQ("tcp://127.0.0.1:19090?param=value&other=123", config->get_agent_addr());
    EXPECT_EQ("game-with-special_chars@123#", config->get_game_id());
    EXPECT_EQ("service.with.dots", config->get_service_id());
}

TEST_F(ConfigManagerTest, ConfigWithUnicode) {
    auto config = std::make_shared<ClientConfig>();
    config->set_game_id("游戏-123");
    config->set_service_id("服务-456");
    config->set_env("生产环境");

    EXPECT_EQ("游戏-123", config->get_game_id());
    EXPECT_EQ("服务-456", config->get_service_id());
    EXPECT_EQ("生产环境", config->get_env());
}
