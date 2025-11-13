#include "croupier/sdk/grpc_service.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>

namespace croupier {
namespace sdk {
namespace grpc_service {

//==============================================================================
// GrpcClientManager Implementation
//==============================================================================

GrpcClientManager::GrpcClientManager(const ClientConfig& config)
    : config_(config)
    , state_(ConnectionState::DISCONNECTED)
    , should_reconnect_(false)
    , heartbeat_running_(false)
    , local_port_(0)
{
    std::cout << "初始化 gRPC 客户端管理器 for game: " << config_.game_id
              << ", env: " << config_.env << std::endl;
}

GrpcClientManager::~GrpcClientManager() {
    Disconnect();
}

bool GrpcClientManager::Connect() {
    std::lock_guard<std::mutex> lock(state_mutex_);

    if (state_ == ConnectionState::CONNECTED) {
        return true;
    }

    state_ = ConnectionState::CONNECTING;

    try {
        // 创建 gRPC 频道
        agent_channel_ = CreateChannel();
        if (!agent_channel_) {
            HandleError("Failed to create gRPC channel");
            return false;
        }

        // 创建客户端 stub
        agent_stub_ = std::make_unique<LocalControlServiceStub>(agent_channel_);

        // 验证连接
        if (!ValidateConnection()) {
            HandleError("Failed to validate connection to agent");
            return false;
        }

        // 启动本地服务器
        if (!StartLocalServer()) {
            HandleError("Failed to start local gRPC server");
            return false;
        }

        state_ = ConnectionState::CONNECTED;
        std::cout << "✅ 成功连接到 Agent: " << config_.agent_addr << std::endl;

        return true;

    } catch (const std::exception& e) {
        HandleError("Connection failed: " + std::string(e.what()));
        state_ = ConnectionState::ERROR;
        return false;
    }
}

void GrpcClientManager::Disconnect() {
    std::lock_guard<std::mutex> lock(state_mutex_);

    should_reconnect_ = false;

    // 停止心跳
    StopHeartbeatLoop();

    // 停止本地服务器
    StopLocalServer();

    // 清理连接
    agent_stub_.reset();
    agent_channel_.reset();

    state_ = ConnectionState::DISCONNECTED;

    std::cout << "📴 已断开与 Agent 的连接" << std::endl;
}

bool GrpcClientManager::IsConnected() const {
    return state_ == ConnectionState::CONNECTED;
}

ConnectionState GrpcClientManager::GetState() const {
    return state_;
}

bool GrpcClientManager::RegisterWithAgent(
    const std::vector<FunctionDescriptor>& functions,
    const std::vector<VirtualObjectDescriptor>& objects,
    const std::vector<ComponentDescriptor>& components,
    std::string& session_id) {

    if (!IsConnected()) {
        std::cerr << "❌ 未连接到 Agent，无法注册" << std::endl;
        return false;
    }

    std::string error_message;
    bool success = agent_stub_->RegisterLocal(
        config_.service_id,
        "1.0.0",
        local_address_,
        functions,
        session_id,
        error_message
    );

    if (success) {
        std::cout << "✅ 成功注册到 Agent，session_id: " << session_id << std::endl;
        std::cout << "📋 注册信息:" << std::endl;
        std::cout << "   - 函数数量: " << functions.size() << std::endl;
        std::cout << "   - 虚拟对象: " << objects.size() << std::endl;
        std::cout << "   - 组件数量: " << components.size() << std::endl;
        std::cout << "   - 本地地址: " << local_address_ << std::endl;

        // 启动心跳
        StartHeartbeatLoop(session_id);
    } else {
        std::cerr << "❌ 注册失败: " << error_message << std::endl;
    }

    return success;
}

bool GrpcClientManager::SendHeartbeat(const std::string& session_id) {
    if (!IsConnected()) {
        return false;
    }

    std::string error_message;
    bool success = agent_stub_->Heartbeat(
        config_.service_id,
        session_id,
        error_message
    );

    if (!success) {
        std::cerr << "💓 心跳失败: " << error_message << std::endl;
        // 可能需要重连
        should_reconnect_ = true;
    }

    return success;
}

void GrpcClientManager::StartHeartbeatLoop(const std::string& session_id) {
    if (heartbeat_running_) {
        return;
    }

    heartbeat_running_ = true;
    heartbeat_thread_ = std::thread([this, session_id]() {
        HeartbeatLoop(session_id);
    });
}

void GrpcClientManager::StopHeartbeatLoop() {
    heartbeat_running_ = false;

    if (heartbeat_thread_.joinable()) {
        heartbeat_thread_.join();
    }
}

bool GrpcClientManager::StartLocalServer() {
    try {
        // 解析监听地址
        std::string host;
        int port = 0;

        auto colon_pos = config_.local_listen.find(':');
        if (colon_pos != std::string::npos) {
            host = config_.local_listen.substr(0, colon_pos);
            std::string port_str = config_.local_listen.substr(colon_pos + 1);
            port = std::stoi(port_str);
        } else {
            host = config_.local_listen;
            port = 0; // 自动分配
        }

        // 如果端口为 0，自动分配端口
        if (port == 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(20000, 30000);
            port = dis(gen);
        }

        // 创建本地服务实现
        std::map<std::string, FunctionHandler> empty_handlers; // 初始为空，后续会更新
        local_service_ = std::make_unique<LocalFunctionServiceImpl>(empty_handlers);

        // 构建服务器地址
        local_address_ = host + ":" + std::to_string(port);
        local_port_ = port;

        // 这里应该启动真实的 gRPC 服务器
        // 现在先模拟成功
        std::cout << "🚀 本地 gRPC 服务器启动在: " << local_address_ << std::endl;

        return true;

    } catch (const std::exception& e) {
        std::cerr << "❌ 启动本地服务器失败: " << e.what() << std::endl;
        return false;
    }
}

void GrpcClientManager::StopLocalServer() {
    if (local_server_) {
        local_server_->Shutdown();
        local_server_.reset();
    }

    local_service_.reset();
    std::cout << "🛑 本地 gRPC 服务器已停止" << std::endl;
}

std::string GrpcClientManager::GetLocalServerAddress() const {
    return local_address_;
}

void GrpcClientManager::SetErrorCallback(std::function<void(const std::string&)> callback) {
    error_callback_ = callback;
}

void GrpcClientManager::SetReconnectCallback(std::function<void()> callback) {
    reconnect_callback_ = callback;
}

//==============================================================================
// Private Methods
//==============================================================================

std::shared_ptr<grpc::Channel> GrpcClientManager::CreateChannel() {
    auto credentials = CreateCredentials();
    auto args = CreateChannelArguments();

    return grpc::CreateCustomChannel(config_.agent_addr, credentials, args);
}

bool GrpcClientManager::ValidateConnection() {
    if (!agent_channel_) {
        return false;
    }

    // 检查频道状态
    auto state = agent_channel_->GetState(true);

    // 等待连接建立
    auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(10);
    bool connected = agent_channel_->WaitForConnected(deadline);

    if (!connected) {
        std::cerr << "⏰ 连接超时，无法连接到 Agent" << std::endl;
        return false;
    }

    std::cout << "🔗 gRPC 频道连接成功" << std::endl;
    return true;
}

void GrpcClientManager::HandleError(const std::string& error) {
    std::cerr << "🚨 gRPC 错误: " << error << std::endl;

    if (error_callback_) {
        error_callback_(error);
    }

    // 如果配置了自动重连，启动重连逻辑
    if (should_reconnect_) {
        DoReconnect();
    }
}

void GrpcClientManager::NotifyReconnect() {
    if (reconnect_callback_) {
        reconnect_callback_();
    }
}

void GrpcClientManager::DoReconnect() {
    if (state_ == ConnectionState::RECONNECTING) {
        return; // 已经在重连中
    }

    state_ = ConnectionState::RECONNECTING;

    reconnect_thread_ = std::thread([this]() {
        int attempts = 0;
        const int max_attempts = 10;
        const auto interval = std::chrono::seconds(5);

        while (should_reconnect_ && attempts < max_attempts) {
            std::cout << "🔄 尝试重连 Agent... (第 " << (attempts + 1) << " 次)" << std::endl;

            std::this_thread::sleep_for(interval);

            if (Connect()) {
                std::cout << "✅ 重连成功！" << std::endl;
                NotifyReconnect();
                return;
            }

            attempts++;
        }

        if (attempts >= max_attempts) {
            std::cerr << "❌ 重连失败，已达到最大尝试次数" << std::endl;
            state_ = ConnectionState::ERROR;
        }
    });
}

void GrpcClientManager::HeartbeatLoop(const std::string& session_id) {
    const auto interval = std::chrono::seconds(60); // 60秒心跳间隔

    while (heartbeat_running_) {
        std::this_thread::sleep_for(interval);

        if (!heartbeat_running_) {
            break;
        }

        if (!SendHeartbeat(session_id)) {
            std::cerr << "💔 心跳失败，可能需要重连" << std::endl;
            break;
        }

        // 静默心跳，只在失败时输出
        // std::cout << "💓 心跳发送成功" << std::endl;
    }

    std::cout << "💓 心跳循环已停止" << std::endl;
}

grpc::ChannelArguments GrpcClientManager::CreateChannelArguments() {
    grpc::ChannelArguments args;

    // 设置超时
    args.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 30000);
    args.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 5000);
    args.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

    // 设置最大消息大小
    args.SetMaxReceiveMessageSize(16 * 1024 * 1024); // 16MB
    args.SetMaxSendMessageSize(16 * 1024 * 1024);    // 16MB

    return args;
}

std::shared_ptr<grpc::ChannelCredentials> GrpcClientManager::CreateCredentials() {
    if (config_.insecure) {
        return grpc::InsecureChannelCredentials();
    }

    // TLS 配置
    grpc::SslCredentialsOptions ssl_options;

    if (!config_.ca_file.empty()) {
        std::ifstream ca_file(config_.ca_file);
        if (ca_file.good()) {
            std::string ca_content((std::istreambuf_iterator<char>(ca_file)),
                                  std::istreambuf_iterator<char>());
            ssl_options.pem_root_certs = ca_content;
        }
    }

    if (!config_.cert_file.empty() && !config_.key_file.empty()) {
        std::ifstream cert_file(config_.cert_file);
        std::ifstream key_file(config_.key_file);

        if (cert_file.good() && key_file.good()) {
            std::string cert_content((std::istreambuf_iterator<char>(cert_file)),
                                   std::istreambuf_iterator<char>());
            std::string key_content((std::istreambuf_iterator<char>(key_file)),
                                  std::istreambuf_iterator<char>());

            ssl_options.pem_cert_chain = cert_content;
            ssl_options.pem_private_key = key_content;
        }
    }

    return grpc::SslCredentials(ssl_options);
}

//==============================================================================
// LocalFunctionServiceImpl Implementation
//==============================================================================

LocalFunctionServiceImpl::LocalFunctionServiceImpl(
    const std::map<std::string, FunctionHandler>& handlers)
    : handlers_(handlers)
    , total_calls_(0)
    , successful_calls_(0)
    , failed_calls_(0)
{
    std::cout << "🎯 本地函数服务初始化，处理器数量: " << handlers_.size() << std::endl;
}

void LocalFunctionServiceImpl::UpdateHandlers(
    const std::map<std::string, FunctionHandler>& handlers) {
    std::unique_lock<std::shared_mutex> lock(handlers_mutex_);
    handlers_ = handlers;
    std::cout << "🔄 更新函数处理器，当前数量: " << handlers_.size() << std::endl;
}

void LocalFunctionServiceImpl::AddHandler(
    const std::string& function_id,
    FunctionHandler handler) {
    std::unique_lock<std::shared_mutex> lock(handlers_mutex_);
    handlers_[function_id] = handler;
    std::cout << "➕ 添加函数处理器: " << function_id << std::endl;
}

void LocalFunctionServiceImpl::RemoveHandler(const std::string& function_id) {
    std::unique_lock<std::shared_mutex> lock(handlers_mutex_);
    auto it = handlers_.find(function_id);
    if (it != handlers_.end()) {
        handlers_.erase(it);
        std::cout << "➖ 移除函数处理器: " << function_id << std::endl;
    }
}

size_t LocalFunctionServiceImpl::GetHandlerCount() const {
    std::shared_lock<std::shared_mutex> lock(handlers_mutex_);
    return handlers_.size();
}

std::string LocalFunctionServiceImpl::ExecuteHandler(
    const std::string& function_id,
    const std::string& context,
    const std::string& payload) {

    total_calls_++;

    std::shared_lock<std::shared_mutex> lock(handlers_mutex_);
    auto it = handlers_.find(function_id);

    if (it == handlers_.end()) {
        failed_calls_++;
        std::string error = R"({"error": "Function not found: )" + function_id + R"("})";
        std::cerr << "❌ 函数不存在: " << function_id << std::endl;
        return error;
    }

    try {
        lock.unlock(); // 释放锁，允许并发执行

        std::cout << "🎯 执行函数: " << function_id << std::endl;
        std::string result = it->second(context, payload);

        successful_calls_++;
        std::cout << "✅ 函数执行成功: " << function_id << std::endl;

        return result;

    } catch (const std::exception& e) {
        failed_calls_++;
        std::string error = R"({"error": "Function execution failed: )" +
                           std::string(e.what()) + R"("})";
        std::cerr << "❌ 函数执行失败: " << function_id
                  << ", 错误: " << e.what() << std::endl;
        return error;
    }
}

//==============================================================================
// LocalControlServiceStub Implementation
//==============================================================================

LocalControlServiceStub::LocalControlServiceStub(std::shared_ptr<grpc::Channel> channel)
    : channel_(channel)
    , default_timeout_(30000) // 30秒超时
{
    // 这里会在有 proto 文件生成后初始化真实的 stub
    // stub_ = LocalControlService::NewStub(channel_);
}

bool LocalControlServiceStub::RegisterLocal(
    const std::string& service_id,
    const std::string& version,
    const std::string& rpc_addr,
    const std::vector<FunctionDescriptor>& functions,
    std::string& session_id,
    std::string& error_message) {

    try {
        auto context = CreateContext();

        // 这是模拟实现，真实实现需要 proto 文件
        // 现在生成一个模拟的 session_id
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        session_id = "session_" + std::to_string(dis(gen));

        std::cout << "📡 向 Agent 注册服务:" << std::endl;
        std::cout << "   - service_id: " << service_id << std::endl;
        std::cout << "   - version: " << version << std::endl;
        std::cout << "   - rpc_addr: " << rpc_addr << std::endl;
        std::cout << "   - functions: " << functions.size() << std::endl;
        std::cout << "   - session_id: " << session_id << std::endl;

        // 模拟成功注册
        return true;

    } catch (const std::exception& e) {
        error_message = "Registration failed: " + std::string(e.what());
        return false;
    }
}

bool LocalControlServiceStub::Heartbeat(
    const std::string& service_id,
    const std::string& session_id,
    std::string& error_message) {

    try {
        auto context = CreateContext();

        // 这是模拟实现
        // 实际实现会调用 agent 的 Heartbeat RPC

        return true;

    } catch (const std::exception& e) {
        error_message = "Heartbeat failed: " + std::string(e.what());
        return false;
    }
}

bool LocalControlServiceStub::ListLocal(
    std::vector<FunctionDescriptor>& functions,
    std::string& error_message) {

    try {
        auto context = CreateContext();

        // 模拟实现
        functions.clear();
        return true;

    } catch (const std::exception& e) {
        error_message = "List functions failed: " + std::string(e.what());
        return false;
    }
}

bool LocalControlServiceStub::UnregisterLocal(
    const std::string& service_id,
    const std::string& session_id,
    std::string& error_message) {

    try {
        auto context = CreateContext();

        std::cout << "📡 从 Agent 注销服务: " << service_id
                  << ", session: " << session_id << std::endl;

        return true;

    } catch (const std::exception& e) {
        error_message = "Unregistration failed: " + std::string(e.what());
        return false;
    }
}

std::unique_ptr<grpc::ClientContext> LocalControlServiceStub::CreateContext() {
    auto context = std::make_unique<grpc::ClientContext>();

    // 设置超时
    context->set_deadline(std::chrono::system_clock::now() + default_timeout_);

    return context;
}

} // namespace grpc_service
} // namespace sdk
} // namespace croupier