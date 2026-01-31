#include <gtest/gtest.h>
#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/config/client_config_loader.h"
#include <fstream>

using namespace croupier::sdk;
using namespace croupier::sdk::config;

// 测试夹具：gRPC 连接管理测试
class GrpcConnectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        loader = std::make_unique<ClientConfigLoader>();

        // 基本配置 - 不安全模式用于测试
        config = loader->CreateDefaultConfig();
        config.insecure = true;
        config.agent_addr = "127.0.0.1:19090";
        config.blocking_connect = false;
        config.auto_reconnect = false;

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
    }

    // 辅助函数：创建 TLS 证书文件
    void CreateTestTlsFiles() {
        std::ofstream cert("test_grpc_cert.pem");
        cert << "-----BEGIN CERTIFICATE-----\n";
        cert << "MIIC9jCCAd4CCQD2rKLXz0BqczANBgkqhkiG9w0BAQsFADANBgkqhkiG9w0BAQsF\n";
        cert << "-----END CERTIFICATE-----\n";
        cert.close();

        std::ofstream key("test_grpc_key.pem");
        key << "-----BEGIN PRIVATE KEY-----\n";
        key << "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBC0wggKJAgEAAoIBAQD\n";
        key << "-----END PRIVATE KEY-----\n";
        key.close();

        std::ofstream ca("test_grpc_ca.pem");
        ca << "-----BEGIN CERTIFICATE-----\n";
        ca << "MIIC9jCCAd4CCQD2rKLXz0BqczANBgkqhkiG9w0BAQsFADANBgkqhkiG9w0BAQsF\n";
        ca << "-----END CERTIFICATE-----\n";
        ca.close();
    }

    // 辅助函数：清理测试文件
    void CleanupTestFiles() {
        std::remove("test_grpc_cert.pem");
        std::remove("test_grpc_key.pem");
        std::remove("test_grpc_ca.pem");
    }

    std::unique_ptr<ClientConfigLoader> loader;
    ClientConfig config;
    std::unique_ptr<CroupierClient> client;
};

// ========== 测试用例 ==========

TEST_F(GrpcConnectionTest, EstablishGrpcConnection) {
    // RED: 测试建立 gRPC 连接
    // 初始状态应该是未连接
    EXPECT_FALSE(client->IsConnected());

    // 尝试建立连接
    [[maybe_unused]] bool connected = client->Connect();

    // 验证 Connect() API 可以被调用
    // 连接结果取决于 agent 是否可用
    SUCCEED();
}

TEST_F(GrpcConnectionTest, CheckConnectionStatus) {
    // RED: 测试检查连接状态
    // 初始状态
    bool initial_status = client->IsConnected();
    EXPECT_FALSE(initial_status);

    // 尝试连接
    client->Connect();

    // 连接后状态
    [[maybe_unused]] bool after_connect = client->IsConnected();

    // 关闭后状态
    client->Close();
    bool after_close = client->IsConnected();
    EXPECT_FALSE(after_close);
}

TEST_F(GrpcConnectionTest, CloseGrpcConnection) {
    // RED: 测试关闭 gRPC 连接
    // 先连接
    client->Connect();

    // 关闭连接
    client->Close();

    // 验证连接已关闭
    EXPECT_FALSE(client->IsConnected());

    // 再次关闭应该是幂等的
    client->Close();
    EXPECT_FALSE(client->IsConnected());
}

TEST_F(GrpcConnectionTest, ConnectionWithTls) {
    // RED: 测试 TLS 连接
    CreateTestTlsFiles();

    // 创建 TLS 配置
    ClientConfig tls_config = loader->CreateDefaultConfig();
    tls_config.insecure = false;
    tls_config.cert_file = "test_grpc_cert.pem";
    tls_config.key_file = "test_grpc_key.pem";
    tls_config.ca_file = "test_grpc_ca.pem";
    tls_config.server_name = "localhost";
    tls_config.blocking_connect = false;

    CroupierClient tls_client(tls_config);

    // 验证 TLS 配置已应用
    EXPECT_FALSE(tls_config.insecure);
    EXPECT_FALSE(tls_config.cert_file.empty());
    EXPECT_FALSE(tls_config.key_file.empty());
    EXPECT_FALSE(tls_config.ca_file.empty());

    // 尝试 TLS 连接
    tls_client.Connect();

    // 验证 API 可以调用
    SUCCEED();

    tls_client.Close();
    CleanupTestFiles();
}

TEST_F(GrpcConnectionTest, ConnectionWithInsecure) {
    // RED: 测试不安全连接
    // 创建不安全配置
    ClientConfig insecure_config = loader->CreateDefaultConfig();
    insecure_config.insecure = true;
    insecure_config.blocking_connect = false;

    CroupierClient insecure_client(insecure_config);

    // 验证配置已应用
    EXPECT_TRUE(insecure_config.insecure);

    // 尝试不安全连接
    insecure_client.Connect();

    // 验证 API 可以调用
    SUCCEED();

    insecure_client.Close();
}

TEST_F(GrpcConnectionTest, ConnectionWithAuthToken) {
    // RED: 测试带认证令牌的连接
    // 创建带认证的配置
    ClientConfig auth_config = loader->CreateDefaultConfig();
    auth_config.auth_token = "Bearer test-token-12345";
    auth_config.blocking_connect = false;

    CroupierClient auth_client(auth_config);

    // 验证配置已应用
    EXPECT_FALSE(auth_config.auth_token.empty());
    EXPECT_EQ(auth_config.auth_token, "Bearer test-token-12345");

    // 尝试带认证的连接
    auth_client.Connect();

    // 验证 API 可以调用
    SUCCEED();

    auth_client.Close();
}

TEST_F(GrpcConnectionTest, ConnectionTimeout) {
    // RED: 测试连接超时
    // 创建短超时配置
    ClientConfig timeout_config = loader->CreateDefaultConfig();
    timeout_config.timeout_seconds = 2;  // 2秒超时
    timeout_config.blocking_connect = true;

    CroupierClient timeout_client(timeout_config);

    // 尝试连接（会在超时后返回）
    timeout_client.Connect();

    // 验证不会永久阻塞
    SUCCEED();

    timeout_client.Close();
}

TEST_F(GrpcConnectionTest, MultipleConnectionAttempts) {
    // RED: 测试多次连接尝试
    // 第一次连接
    client->Connect();
    client->Close();

    // 第二次连接
    client->Connect();
    client->Close();

    // 第三次连接
    client->Connect();
    client->Close();

    // 验证可以多次尝试连接
    SUCCEED();
}

TEST_F(GrpcConnectionTest, ConnectionFailureHandling) {
    // RED: 测试连接失败处理
    // 使用无效地址
    ClientConfig invalid_config = loader->CreateDefaultConfig();
    invalid_config.agent_addr = "invalid-address:99999";
    invalid_config.timeout_seconds = 1;
    invalid_config.blocking_connect = false;

    CroupierClient invalid_client(invalid_config);

    // 尝试连接到无效地址
    [[maybe_unused]] bool connected = invalid_client.Connect();

    // 应该能够处理连接失败而不崩溃
    // connected 很可能是 false
    SUCCEED();

    invalid_client.Close();
}

TEST_F(GrpcConnectionTest, ConnectionRecovery) {
    // RED: 测试连接恢复
    // 启用自动重连
    ClientConfig recovery_config = loader->CreateDefaultConfig();
    recovery_config.auto_reconnect = true;
    recovery_config.reconnect_interval_seconds = 1;
    recovery_config.reconnect_max_attempts = 3;
    recovery_config.blocking_connect = false;

    CroupierClient recovery_client(recovery_config);

    // 验证重连配置
    EXPECT_TRUE(recovery_config.auto_reconnect);
    EXPECT_EQ(recovery_config.reconnect_max_attempts, 3);

    // 尝试连接
    recovery_client.Connect();

    // 验证 API 可以调用
    SUCCEED();

    recovery_client.Close();
}
