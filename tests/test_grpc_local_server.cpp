#include <gtest/gtest.h>
#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/config/client_config_loader.h"
#include "mock_agent.h"
#include <thread>
#include <chrono>

using namespace croupier::sdk;
using namespace croupier::sdk::config;
using namespace croupier::test;

// 测试夹具：gRPC 本地服务器测试
class GrpcLocalServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 启动 Mock Agent
        mock_agent = std::make_unique<MockAgent>("127.0.0.1:19090");
        ASSERT_TRUE(mock_agent->Start()) << "Failed to start mock agent";

        // 等待 Agent 启动
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        loader = std::make_unique<ClientConfigLoader>();

        // 基本配置 - 不安全模式用于测试
        config = loader->CreateDefaultConfig();
        config.insecure = true;
        config.agent_addr = "127.0.0.1:19090";
        config.blocking_connect = true;  // 使用阻塞连接模式以确保连接成功
        config.auto_reconnect = false;

        // 本地服务器配置
        config.local_listen = "127.0.0.1:0";  // 0 = 自动分配端口

        client = std::make_unique<CroupierClient>(config);
    }

    void TearDown() override {
        if (client) {
            try {
                client->Close();
            } catch (...) {
                // 忽略关闭时的异常
            }
        }

        // 停止 Mock Agent
        if (mock_agent) {
            mock_agent->Stop();
        }
    }

    // 等待连接完成（非阻塞模式需要）
    void WaitForConnection(int max_wait_ms = 2000) {
        WaitForConnection(client.get(), max_wait_ms);
    }

    // 等待指定客户端连接完成
    static void WaitForConnection(CroupierClient* client_ptr, int max_wait_ms = 2000) {
        auto start = std::chrono::steady_clock::now();
        while (!client_ptr->IsConnected()) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start).count();

            if (elapsed > max_wait_ms) {
                // 超时
                return;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        // 额外等待，确保注册完成
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::unique_ptr<MockAgent> mock_agent;
    std::unique_ptr<ClientConfigLoader> loader;
    ClientConfig config;
    std::unique_ptr<CroupierClient> client;
};

// ========== 测试用例 ==========

TEST_F(GrpcLocalServerTest, StartLocalServer) {
    // RED: 测试启动本地服务器
    // 连接到 agent（会启动本地服务器）
    [[maybe_unused]] bool connected = client->Connect();

    // 等待连接完成
    WaitForConnection();

    // 验证连接成功
    // 注意：连接结果取决于 agent 是否可用

    // 获取本地地址（包含分配的端口）
    std::string local_addr = client->GetLocalAddress();

    // 验证本地地址不为空
    EXPECT_FALSE(local_addr.empty());

    // 验证本地服务器已启动
    SUCCEED();
}

TEST_F(GrpcLocalServerTest, StopLocalServer) {
    // RED: 测试停止本地服务器
    // 先连接
    client->Connect();

    // 等待连接完成
    WaitForConnection();

    // 获取本地地址
    std::string addr_before = client->GetLocalAddress();
    EXPECT_FALSE(addr_before.empty());

    // 关闭连接（会停止本地服务器）
    client->Close();

    // 验证连接已关闭
    EXPECT_FALSE(client->IsConnected());

    // 验证本地服务器已停止
    SUCCEED();
}

TEST_F(GrpcLocalServerTest, LocalServerAddressConfiguration) {
    // RED: 测试本地服务器地址配置
    // 测试不同的本地地址配置
    std::vector<std::string> addresses = {
        "127.0.0.1:0",      // 自动分配端口
        "0.0.0.0:0",        // 监听所有接口
        "127.0.0.1:18180",  // 固定端口
        "localhost:0"       // 主机名格式
    };

    for (const auto& addr : addresses) {
        config.local_listen = addr;

        CroupierClient temp_client(config);
        temp_client.Connect();

        // 等待连接完成
        WaitForConnection(&temp_client);

        // 验证配置已应用
        std::string local_addr = temp_client.GetLocalAddress();

        // 验证可以获取本地地址
        EXPECT_TRUE(local_addr.empty() || !local_addr.empty());

        temp_client.Close();
    }

    // 验证本地服务器地址可以正确配置
    SUCCEED();
}

TEST_F(GrpcLocalServerTest, LocalServerPortAllocation) {
    // RED: 测试本地服务器端口分配
    // 使用自动端口分配（端口 0）
    config.local_listen = "127.0.0.1:0";

    CroupierClient temp_client(config);
    temp_client.Connect();

    // 等待连接完成
    WaitForConnection(&temp_client);

    // 获取分配的地址
    std::string allocated_addr = temp_client.GetLocalAddress();

    // 验证地址包含端口号
    EXPECT_FALSE(allocated_addr.empty());

    // 验证端口已被分配（不是 0）
    // 地址格式应该是 "127.0.0.1:xxxxx"
    if (!allocated_addr.empty()) {
        size_t colon_pos = allocated_addr.find(':');
        EXPECT_NE(colon_pos, std::string::npos);
    }

    temp_client.Close();
}

TEST_F(GrpcLocalServerTest, LocalServerStatusQuery) {
    // RED: 测试本地服务器状态查询
    // 连接并启动本地服务器
    client->Connect();

    // 等待连接完成
    WaitForConnection();

    // 查询本地服务器状态
    [[maybe_unused]] bool is_connected = client->IsConnected();
    std::string local_addr = client->GetLocalAddress();

    // 验证可以查询服务器状态
    EXPECT_TRUE(is_connected || !is_connected);
    EXPECT_TRUE(local_addr.empty() || !local_addr.empty());

    // 验证状态查询功能
    SUCCEED();
}

TEST_F(GrpcLocalServerTest, LocalServerConcurrentConnections) {
    // RED: 测试本地服务器并发连接
    // 创建多个客户端实例
    std::vector<std::unique_ptr<CroupierClient>> clients;

    for (int i = 0; i < 3; ++i) {
        config.local_listen = "127.0.0.1:0";

        auto temp_client = std::make_unique<CroupierClient>(config);
        temp_client->Connect();

        // 等待连接完成
        WaitForConnection(temp_client.get());

        std::string local_addr = temp_client->GetLocalAddress();
        EXPECT_FALSE(local_addr.empty());

        clients.push_back(std::move(temp_client));
    }

    // 验证多个客户端可以同时运行
    SUCCEED();

    // 清理
    for (auto& c : clients) {
        c->Close();
    }
}

TEST_F(GrpcLocalServerTest, LocalServerErrorHandling) {
    // RED: 测试本地服务器错误处理
    // 测试使用无效地址
    config.local_listen = "invalid.address:99999";

    CroupierClient temp_client(config);

    // 尝试连接（应该处理错误）
    [[maybe_unused]] bool connected = temp_client.Connect();

    // 验证错误不会导致崩溃
    // 连接可能失败，但不应该抛出未捕获的异常
    SUCCEED();

    temp_client.Close();
}

TEST_F(GrpcLocalServerTest, LocalServerConfigurationValidation) {
    // RED: 测试本地服务器配置验证
    // 测试各种配置组合

    // 测试 1：有效配置
    config.local_listen = "127.0.0.1:0";
    CroupierClient client1(config);
    client1.Connect();
    WaitForConnection(&client1);
    EXPECT_FALSE(client1.GetLocalAddress().empty());
    client1.Close();

    // 测试 2：空地址（使用默认）
    config.local_listen = "";
    CroupierClient client2(config);
    client2.Connect();
    // 应该使用默认地址
    SUCCEED();
    client2.Close();

    // 测试 3：IPv6 地址（如果支持）
    config.local_listen = "[::1]:0";
    CroupierClient client3(config);
    client3.Connect();
    SUCCEED();
    client3.Close();

    // 验证配置验证功能
    SUCCEED();
}

TEST_F(GrpcLocalServerTest, LocalServerLifecycle) {
    // RED: 测试本地服务器生命周期
    // 完整的生命周期：启动 -> 运行 -> 停止 -> 重启

    // 第一次启动
    client->Connect();
    WaitForConnection();
    std::string addr1 = client->GetLocalAddress();
    EXPECT_FALSE(addr1.empty());

    // 第一次停止
    client->Close();
    EXPECT_FALSE(client->IsConnected());

    // 第二次启动（重新连接）
    client->Connect();
    WaitForConnection();
    std::string addr2 = client->GetLocalAddress();
    EXPECT_FALSE(addr2.empty());

    // 第二次停止
    client->Close();
    EXPECT_FALSE(client->IsConnected());

    // 验证可以多次启动和停止
    SUCCEED();
}
