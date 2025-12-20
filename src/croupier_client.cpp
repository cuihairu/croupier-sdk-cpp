#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/grpc_service.h"
#include "croupier/sdk/utils/json_utils.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <regex>
#include <cstring>
#include <stdexcept>

#ifdef CROUPIER_SDK_ENABLE_GRPC
#include "croupier/control/v1/control.grpc.pb.h"
#include "croupier/function/v1/function.grpc.pb.h"
#include <zlib.h>
#endif

#ifdef CROUPIER_SDK_ENABLE_JSON
#include <nlohmann/json.hpp>
#endif

namespace croupier {
namespace sdk {

#ifdef CROUPIER_SDK_ENABLE_GRPC
namespace functionv1 = ::croupier::function::v1;
#endif

// Utility function implementations
namespace utils {
    std::string NewIdempotencyKey() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);

        std::stringstream ss;
        for (int i = 0; i < 32; ++i) {
            ss << std::hex << dis(gen);
        }
        return ss.str();
    }

    bool ValidateJSON(const std::string& json, const std::map<std::string, std::string>& schema) {
        // If no schema provided, just check if JSON is valid
        if (schema.empty()) {
            return croupier::sdk::utils::JsonUtils::IsValidJson(json);
        }

        // Convert schema map to JSON schema string
        std::string schema_json = "{";
        bool first = true;
        for (const auto& [key, value] : schema) {
            if (!first) schema_json += ",";
            schema_json += "\"" + key + "\":";

            // Try to parse value as JSON, fallback to string
            if ((value.front() == '{' && value.back() == '}') ||
                (value.front() == '[' && value.back() == ']') ||
                value == "true" || value == "false" || value == "null") {
                schema_json += value;
            } else {
                schema_json += "\"" + value + "\"";
            }
            first = false;
        }
        schema_json += "}";

        // Use the new JSON schema validation
        return croupier::sdk::utils::JsonUtils::ValidateJsonSchema(json, schema_json);
    }

    std::map<std::string, std::string> ParseJSON(const std::string& json) {
        // Simplified JSON parsing for demonstration
        // Real implementation should use a proper JSON library like nlohmann/json
        std::map<std::string, std::string> result;

        if (json.empty()) return result;

        // Very basic key-value extraction using regex
        std::regex pair_regex("\"([^\"]+)\"\\s*:\\s*\"([^\"]*)\"");
        std::sregex_iterator iter(json.begin(), json.end(), pair_regex);
        std::sregex_iterator end;

        for (; iter != end; ++iter) {
            const std::smatch& match = *iter;
            result[match[1].str()] = match[2].str();
        }

        return result;
    }

    std::string ToJSON(const std::map<std::string, std::string>& data) {
        std::stringstream ss;
        ss << "{";
        bool first = true;
        for (const auto& pair : data) {
            if (!first) ss << ",";
            ss << "\"" << pair.first << "\":\"" << pair.second << "\"";
            first = false;
        }
        ss << "}";
        return ss.str();
    }
}

// Client Implementation
class CroupierClient::Impl {
public:
    ClientConfig config_;
    std::map<std::string, FunctionHandler> handlers_;
    std::map<std::string, FunctionDescriptor> descriptors_;

    // New: Virtual object and component storage
    std::map<std::string, VirtualObjectDescriptor> objects_;
    std::map<std::string, ComponentDescriptor> components_;

    // gRPC 管理器
    std::unique_ptr<grpc_service::GrpcClientManager> grpc_manager_;
    std::string session_id_;

    std::atomic<bool> running_{false};
    std::atomic<bool> connected_{false};
    std::thread server_thread_;
    std::string local_address_;

    explicit Impl(const ClientConfig& config) : config_(config) {
        // Validate required configuration
        if (config_.game_id.empty()) {
            std::cerr << "Warning: game_id is required for proper backend separation" << std::endl;
        }

        // Validate environment
        if (config_.env != "development" && config_.env != "staging" && config_.env != "production") {
            std::cerr << "Warning: Unknown environment '" << config_.env
                      << "'. Valid values: development, staging, production" << std::endl;
        }

        std::cout << "Initialized CroupierClient for game '" << config_.game_id
                  << "' in '" << config_.env << "' environment" << std::endl;

        // 初始化 gRPC 管理器
        grpc_manager_ = std::make_unique<grpc_service::GrpcClientManager>(config_);

        // Set error callback
        grpc_manager_->SetErrorCallback([](const std::string& error) {
            std::cerr << "🚨 gRPC Error: " << error << std::endl;
            // Error handling logic can be implemented here
        });

        // Set reconnect callback
        grpc_manager_->SetReconnectCallback([this]() {
            std::cout << "🔄 gRPC Reconnected, re-registering functions..." << std::endl;
            // Re-register all functions
            RegisterAllFunctions();
        });
    }

    ~Impl() {
        Stop();
    }

    bool RegisterFunction(const FunctionDescriptor& desc, FunctionHandler handler) {
        if (running_) {
            std::cerr << "Cannot register functions while client is running" << std::endl;
            return false;
        }

        handlers_[desc.id] = handler;
        descriptors_[desc.id] = desc;

        std::cout << "Registered function: " << desc.id << " (version: " << desc.version << ")" << std::endl;
        return true;
    }

    // New: Register virtual object with associated functions
    bool RegisterVirtualObject(const VirtualObjectDescriptor& desc,
                              const std::map<std::string, FunctionHandler>& handlers) {
        if (running_) {
            std::cerr << "Cannot register virtual objects while client is running" << std::endl;
            return false;
        }

        // Validate object descriptor
        if (!utils::ValidateObjectDescriptor(desc)) {
            std::cerr << "Invalid virtual object descriptor: " << desc.id << std::endl;
            return false;
        }

        // Register all associated functions
        for (const auto& op : desc.operations) {
            const std::string& function_id = op.second;

            // Check if handler exists for this function
            auto handler_it = handlers.find(function_id);
            if (handler_it == handlers.end()) {
                std::cerr << "Missing handler for function: " << function_id << std::endl;
                return false;
            }

            // Create function descriptor
            FunctionDescriptor func_desc;
            func_desc.id = function_id;
            func_desc.version = desc.version;

            // Register the function
            if (!RegisterFunction(func_desc, handler_it->second)) {
                std::cerr << "Failed to register function: " << function_id << std::endl;
                return false;
            }
        }

        // Store virtual object descriptor
        objects_[desc.id] = desc;

        std::cout << "Registered virtual object: " << desc.id
                  << " with " << desc.operations.size() << " operations" << std::endl;
        return true;
    }

    // New: Register complete component
    bool RegisterComponent(const ComponentDescriptor& comp) {
        if (running_) {
            std::cerr << "Cannot register components while client is running" << std::endl;
            return false;
        }

        // Validate component descriptor
        if (!utils::ValidateComponentDescriptor(comp)) {
            std::cerr << "Invalid component descriptor: " << comp.id << std::endl;
            return false;
        }

        // Collect all handlers needed for this component
        std::map<std::string, FunctionHandler> all_handlers;

        // Register standalone functions first
        for (const auto& func_desc : comp.functions) {
            // This is a placeholder - in real implementation, you would need to provide handlers
            std::cout << "Note: Standalone function " << func_desc.id
                      << " needs handler registration" << std::endl;
        }

        // Register virtual objects (they should have handlers already mapped)
        for (const auto& obj_desc : comp.entities) {
            // For entities, we expect handlers to be provided separately
            // This is a design choice - handlers are runtime behavior, descriptors are configuration
            std::cout << "Registered entity definition: " << obj_desc.id
                      << " (handlers need to be registered separately)" << std::endl;
            objects_[obj_desc.id] = obj_desc;
        }

        // Store component descriptor
        components_[comp.id] = comp;

        std::cout << "Registered component: " << comp.id
                  << " with " << comp.entities.size() << " entities and "
                  << comp.functions.size() << " functions" << std::endl;
        return true;
    }

    // New: Load component from JSON file
    bool LoadComponentFromFile(const std::string& config_file) {
        try {
            ComponentDescriptor comp = utils::LoadComponentDescriptor(config_file);
            return RegisterComponent(comp);
        } catch (const std::exception& e) {
            std::cerr << "Failed to load component from file " << config_file
                      << ": " << e.what() << std::endl;
            return false;
        }
    }

    // New: Get registered objects
    std::vector<VirtualObjectDescriptor> GetRegisteredObjects() const {
        std::vector<VirtualObjectDescriptor> result;
        for (const auto& pair : objects_) {
            result.push_back(pair.second);
        }
        return result;
    }

    // New: Get registered components
    std::vector<ComponentDescriptor> GetRegisteredComponents() const {
        std::vector<ComponentDescriptor> result;
        for (const auto& pair : components_) {
            result.push_back(pair.second);
        }
        return result;
    }

    // New: Unregister virtual object
    bool UnregisterVirtualObject(const std::string& object_id) {
        auto it = objects_.find(object_id);
        if (it == objects_.end()) {
            std::cerr << "Virtual object not found: " << object_id << std::endl;
            return false;
        }

        // Remove associated functions
        const VirtualObjectDescriptor& desc = it->second;
        for (const auto& op : desc.operations) {
            const std::string& function_id = op.second;
            handlers_.erase(function_id);
            descriptors_.erase(function_id);
        }

        // Remove object
        objects_.erase(it);

        std::cout << "Unregistered virtual object: " << object_id << std::endl;
        return true;
    }

    // New: Unregister component
    bool UnregisterComponent(const std::string& component_id) {
        auto it = components_.find(component_id);
        if (it == components_.end()) {
            std::cerr << "Component not found: " << component_id << std::endl;
            return false;
        }

        const ComponentDescriptor& comp = it->second;

        // Remove all entities in this component
        for (const auto& entity : comp.entities) {
            UnregisterVirtualObject(entity.id);
        }

        // Remove standalone functions
        for (const auto& func : comp.functions) {
            handlers_.erase(func.id);
            descriptors_.erase(func.id);
        }

        // Remove component
        components_.erase(it);

        std::cout << "Unregistered component: " << component_id << std::endl;
        return true;
    }

    // Re-register all functions to gRPC manager
    void RegisterAllFunctions() {
        if (!grpc_manager_->IsConnected()) {
            return;
        }

        grpc_manager_->UpdateHandlers(handlers_);

        // Convert FunctionDescriptor to LocalFunctionDescriptor (for local registration)
        std::vector<LocalFunctionDescriptor> local_functions;
        for (const auto& desc : descriptors_) {
            LocalFunctionDescriptor local_func;
            local_func.id = desc.second.id;
            local_func.version = desc.second.version;
            local_functions.push_back(local_func);
        }

        // Register with Agent (first layer: SDK -> Agent)
        std::string new_session_id;
        if (grpc_manager_->RegisterWithAgent(local_functions, new_session_id)) {
            session_id_ = new_session_id;
            std::cout << "✅ Re-registration successful, session_id: " << session_id_ << std::endl;
        } else {
            std::cerr << "❌ Re-registration failed" << std::endl;
        }
    }

    bool Connect() {
        if (connected_) return true;

        std::cout << "🔌 连接到 Croupier Agent: " << config_.agent_addr << std::endl;

        grpc_manager_->UpdateHandlers(handlers_);

        // 使用 gRPC 管理器连接
        if (!grpc_manager_->Connect()) {
            std::cerr << "❌ 无法连接到 Agent" << std::endl;
            return false;
        }

        // Convert FunctionDescriptor to LocalFunctionDescriptor for agent registration
        std::vector<LocalFunctionDescriptor> local_functions;
        for (const auto& desc : descriptors_) {
            LocalFunctionDescriptor local_func;
            local_func.id = desc.second.id;
            local_func.version = desc.second.version;
            local_functions.push_back(local_func);
        }

        // Register with Agent (first layer: SDK -> Agent)
        if (!grpc_manager_->RegisterWithAgent(local_functions, session_id_)) {
            std::cerr << "❌ Failed to register service with Agent" << std::endl;
            grpc_manager_->Disconnect();
            return false;
        }

        // 更新本地服务器地址
        local_address_ = grpc_manager_->GetLocalServerAddress();

        connected_ = true;
        std::cout << "✅ 成功连接并注册到 Agent" << std::endl;
        std::cout << "📍 本地服务地址: " << local_address_ << std::endl;
        std::cout << "🔑 会话 ID: " << session_id_ << std::endl;

#ifdef CROUPIER_SDK_ENABLE_GRPC
        if (!config_.control_addr.empty()) {
            if (!UploadCapabilitiesManifest()) {
                std::cerr << "⚠️  Failed to upload provider capabilities manifest" << std::endl;
            }
        }
#endif

        return true;
    }

    void Serve() {
        if (!connected_ && !Connect()) {
            std::cerr << "❌ 连接失败，无法启动服务" << std::endl;
            return;
        }

        running_ = true;
        std::cout << "🚀 Croupier 客户端服务启动" << std::endl;
        std::cout << "📍 本地服务地址: " << local_address_ << std::endl;
        std::cout << "🎯 已注册函数: " << handlers_.size() << " 个" << std::endl;
        std::cout << "📦 已注册虚拟对象: " << objects_.size() << " 个" << std::endl;
        std::cout << "🔧 已注册组件: " << components_.size() << " 个" << std::endl;
        std::cout << "💡 使用 Stop() 方法停止服务" << std::endl;
        std::cout << "===============================================" << std::endl;

        // 保持服务运行，等待来自 Agent 的调用
        while (running_) {
            // 检查连接状态
            if (!grpc_manager_->IsConnected()) {
                std::cerr << "⚠️ 与 Agent 的连接已断开" << std::endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << "🛑 服务已停止" << std::endl;
    }

    void Stop() {
        running_ = false;
        connected_ = false;

        std::cout << "🛑 正在停止 Croupier 客户端..." << std::endl;

        // 断开 gRPC 连接
        if (grpc_manager_) {
            grpc_manager_->Disconnect();
        }

        // 等待服务器线程结束
        if (server_thread_.joinable()) {
            server_thread_.join();
        }

        std::cout << "✅ 客户端已完全停止" << std::endl;
    }

    void Close() {
        Stop();
        handlers_.clear();
        descriptors_.clear();
    }

    std::string GetLocalAddress() const {
        return local_address_;
    }

private:
    // 这些方法现在由 gRPC 管理器处理
#ifdef CROUPIER_SDK_ENABLE_GRPC
    bool UploadCapabilitiesManifest();
    std::string BuildCapabilitiesManifest() const;
    std::string EscapeJson(const std::string& value) const;
    std::string DefaultVersion(const std::string& version) const;
    std::string SafeString(const std::string& value, const std::string& fallback) const;
    std::string GzipCompress(const std::string& input) const;
#endif
};

#ifdef CROUPIER_SDK_ENABLE_GRPC
bool CroupierClient::Impl::UploadCapabilitiesManifest() {
    if (!grpc_manager_) {
        std::cerr << "⚠️  gRPC manager is not initialized; skipping capability upload" << std::endl;
        return false;
    }
    try {
        const std::string manifest = BuildCapabilitiesManifest();
        const std::string compressed = GzipCompress(manifest);

        auto credentials = grpc_manager_->BuildClientCredentials();
        auto channel_args = grpc_manager_->BuildClientChannelArguments();
        auto channel = grpc::CreateCustomChannel(config_.control_addr, credentials, channel_args);

        const auto timeout = std::chrono::seconds(config_.timeout_seconds > 0 ? config_.timeout_seconds : 30);
        auto connect_deadline = std::chrono::system_clock::now() + timeout;
        if (!channel->WaitForConnected(connect_deadline)) {
            std::cerr << "⚠️  Unable to connect to control service at "
                      << config_.control_addr << std::endl;
            return false;
        }

        auto stub = croupier::control::v1::ControlService::NewStub(channel);
        grpc::ClientContext ctx;
        if (config_.timeout_seconds > 0) {
            ctx.set_deadline(std::chrono::system_clock::now() + timeout);
        }

        croupier::control::v1::RegisterCapabilitiesRequest request;
        auto* provider = request.mutable_provider();
        provider->set_id(SafeString(config_.service_id, "cpp-service"));
        provider->set_version(DefaultVersion(config_.service_version));
        provider->set_lang(SafeString(config_.provider_lang, "cpp"));
        provider->set_sdk(SafeString(config_.provider_sdk, "croupier-cpp-sdk"));
        request.set_manifest_json_gz(compressed);

        croupier::control::v1::RegisterCapabilitiesResponse response;
        grpc::Status status = stub->RegisterCapabilities(&ctx, request, &response);
        if (!status.ok()) {
            std::cerr << "⚠️  ControlService.RegisterCapabilities failed: "
                      << status.error_message() << std::endl;
            return false;
        }

        std::cout << "📤 Uploaded provider capabilities manifest ("
                  << descriptors_.size() << " functions)" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️  Failed to upload capabilities: " << e.what() << std::endl;
        return false;
    }
}

std::string CroupierClient::Impl::BuildCapabilitiesManifest() const {
    std::ostringstream oss;
    oss << "{\"provider\":{";
    oss << "\"id\":\"" << EscapeJson(SafeString(config_.service_id, "cpp-service")) << "\",";
    oss << "\"version\":\"" << EscapeJson(DefaultVersion(config_.service_version)) << "\",";
    oss << "\"lang\":\"" << EscapeJson(SafeString(config_.provider_lang, "cpp")) << "\",";
    oss << "\"sdk\":\"" << EscapeJson(SafeString(config_.provider_sdk, "croupier-cpp-sdk")) << "\"}";

    bool has_functions = false;
    for (const auto& entry : descriptors_) {
        const auto& descriptor = entry.second;
        if (descriptor.id.empty()) {
            continue;
        }
        if (!has_functions) {
            oss << ",\"functions\":[";
            has_functions = true;
        } else {
            oss << ",";
        }

        oss << "{";
        oss << "\"id\":\"" << EscapeJson(descriptor.id) << "\",";
        oss << "\"version\":\"" << EscapeJson(DefaultVersion(descriptor.version)) << "\"";
        if (!descriptor.category.empty()) {
            oss << ",\"category\":\"" << EscapeJson(descriptor.category) << "\"";
        }
        if (!descriptor.risk.empty()) {
            oss << ",\"risk\":\"" << EscapeJson(descriptor.risk) << "\"";
        }
        if (!descriptor.entity.empty()) {
            oss << ",\"entity\":\"" << EscapeJson(descriptor.entity) << "\"";
        }
        if (!descriptor.operation.empty()) {
            oss << ",\"operation\":\"" << EscapeJson(descriptor.operation) << "\"";
        }
        if (descriptor.enabled) {
            oss << ",\"enabled\":true";
        }
        oss << "}";
    }
    if (has_functions) {
        oss << "]";
    }

    oss << "}";
    return oss.str();
}

std::string CroupierClient::Impl::EscapeJson(const std::string& value) const {
    std::ostringstream oss;
    for (const char ch : value) {
        switch (ch) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (static_cast<unsigned char>(ch) < 0x20) {
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                        << static_cast<int>(static_cast<unsigned char>(ch))
                        << std::dec << std::setfill(' ');
                } else {
                    oss << ch;
                }
        }
    }
    return oss.str();
}

std::string CroupierClient::Impl::DefaultVersion(const std::string& version) const {
    return version.empty() ? "1.0.0" : version;
}

std::string CroupierClient::Impl::SafeString(const std::string& value, const std::string& fallback) const {
    return value.empty() ? fallback : value;
}

std::string CroupierClient::Impl::GzipCompress(const std::string& input) const {
    if (input.empty()) {
        return "";
    }

    z_stream zs;
    std::memset(&zs, 0, sizeof(zs));
    int ret = deflateInit2(&zs, Z_BEST_SPEED, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
        throw std::runtime_error("deflateInit2 failed");
    }

    zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(input.data()));
    zs.avail_in = static_cast<uInt>(input.size());

    std::string output;
    output.reserve(input.size());

    char buffer[4096];
    do {
        zs.next_out = reinterpret_cast<Bytef*>(buffer);
        zs.avail_out = sizeof(buffer);

        ret = deflate(&zs, zs.avail_in > 0 ? Z_NO_FLUSH : Z_FINISH);
        if (ret == Z_STREAM_ERROR) {
            deflateEnd(&zs);
            throw std::runtime_error("deflate failed");
        }

        std::size_t produced = sizeof(buffer) - zs.avail_out;
        output.append(buffer, produced);
    } while (ret != Z_STREAM_END);

    deflateEnd(&zs);
    return output;
}
#endif

// Invoker Implementation
class CroupierInvoker::Impl {
public:
    InvokerConfig config_;
    std::map<std::string, std::map<std::string, std::string>> schemas_;
    std::atomic<bool> connected_{false};

#ifdef CROUPIER_SDK_ENABLE_GRPC
    // gRPC components
    std::shared_ptr<grpc::Channel> channel_;
    std::unique_ptr<functionv1::FunctionService::Stub> stub_;
#endif

    explicit Impl(const InvokerConfig& config) : config_(config) {}

    bool Connect() {
        if (connected_) return true;

        std::cout << "Connecting to server/agent at: " << config_.address << std::endl;

#ifdef CROUPIER_SDK_ENABLE_GRPC
        try {
            // Create gRPC channel
            grpc::ChannelArguments args;
            args.SetMaxReceiveMessageSize(INT_MAX);
            args.SetMaxSendMessageSize(INT_MAX);

            // Use insecure credentials for now, can be enhanced to support TLS
            channel_ = grpc::CreateCustomChannel(config_.address,
                                                grpc::InsecureChannelCredentials(),
                                                args);

            if (!channel_) {
                std::cerr << "Failed to create gRPC channel" << std::endl;
                return false;
            }

            // Create stub
            stub_ = functionv1::FunctionService::NewStub(channel_);
            if (!stub_) {
                std::cerr << "Failed to create gRPC stub" << std::endl;
                return false;
            }

            connected_ = true;
            std::cout << "✅ Connected to: " << config_.address << std::endl;
            return true;

        } catch (const std::exception& e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
            return false;
        }
#else
        // Fallback to simulated connection when gRPC is not enabled
        connected_ = true;
        std::cout << "⚠️  Connected to: " << config_.address << " (simulated, gRPC not enabled)" << std::endl;
        return true;
#endif
    }

    std::string Invoke(const std::string& function_id, const std::string& payload,
                      const InvokeOptions& options) {
        if (!connected_ && !Connect()) {
            throw std::runtime_error("Not connected to server");
        }

        // Client-side validation
        auto it = schemas_.find(function_id);
        if (it != schemas_.end()) {
            if (!utils::ValidateJSON(payload, it->second)) {
                throw std::runtime_error("Payload validation failed for function: " + function_id);
            }
        }

        std::cout << "Invoking function: " << function_id << std::endl;

 #ifdef CROUPIER_SDK_ENABLE_GRPC
        try {
            // Create gRPC context
            grpc::ClientContext context;

            // Set timeout from options or invoker default
            const int timeout_seconds = options.timeout_seconds > 0 ? options.timeout_seconds : config_.timeout_seconds;
            auto timeout = std::chrono::seconds(timeout_seconds > 0 ? timeout_seconds : 30);
            context.set_deadline(std::chrono::system_clock::now() + timeout);

            // Set metadata
            if (!config_.game_id.empty()) {
                context.AddMetadata("x-game-id", config_.game_id);
            }
            if (!config_.env.empty()) {
                context.AddMetadata("x-env", config_.env);
            }
            if (!options.idempotency_key.empty()) {
                context.AddMetadata("idempotency-key", options.idempotency_key);
            }
            if (!config_.auth_token.empty()) {
                context.AddMetadata("authorization", "Bearer " + config_.auth_token);
            }
            for (const auto& [k, v] : config_.headers) {
                context.AddMetadata(k, v);
            }

            // Create request
            functionv1::InvokeRequest request;
            request.set_function_id(function_id);
            if (!options.idempotency_key.empty()) {
                request.set_idempotency_key(options.idempotency_key);
            }
            request.set_payload(payload);
            auto* request_metadata = request.mutable_metadata();
            if (!options.route.empty()) (*request_metadata)["route"] = options.route;
            if (!options.target_service_id.empty()) (*request_metadata)["target_service_id"] = options.target_service_id;
            if (!options.hash_key.empty()) (*request_metadata)["hash_key"] = options.hash_key;
            if (!options.trace_id.empty()) (*request_metadata)["trace_id"] = options.trace_id;
            for (const auto& [k, v] : options.metadata) {
                (*request_metadata)[k] = v;
            }

            // Send request
            functionv1::InvokeResponse response;
            grpc::Status status = stub_->Invoke(&context, request, &response);

            if (!status.ok()) {
                std::string error_msg = "gRPC error: " + status.error_message() +
                                     " (code: " + std::to_string(status.error_code()) + ")";
                throw std::runtime_error(error_msg);
            }

            std::string result = response.payload();
            std::cout << "✅ Invoke successful, response size: " << result.size() << " bytes" << std::endl;
            return result;

        } catch (const std::exception& e) {
            std::cerr << "❌ Invoke failed: " << e.what() << std::endl;
            throw;
        }
#else
        // Fallback simulation when gRPC is not enabled
        std::string response = "{\"status\":\"success\",\"function_id\":\"" + function_id + "\"}";
        std::cout << "⚠️  Simulated invoke response: " << response << std::endl;
        return response;
#endif
    }

    std::string StartJob(const std::string& function_id, const std::string& payload,
                        const InvokeOptions& options) {
        if (!connected_ && !Connect()) {
            throw std::runtime_error("Not connected to server");
        }

        // Client-side validation
        auto it = schemas_.find(function_id);
        if (it != schemas_.end()) {
            if (!utils::ValidateJSON(payload, it->second)) {
                throw std::runtime_error("Payload validation failed for function: " + function_id);
            }
        }

        std::cout << "Starting job for function: " << function_id << std::endl;

#ifdef CROUPIER_SDK_ENABLE_GRPC
        try {
            // Create gRPC context
            grpc::ClientContext context;

            // Set timeout from options or invoker default
            const int timeout_seconds = options.timeout_seconds > 0 ? options.timeout_seconds : config_.timeout_seconds;
            auto timeout = std::chrono::seconds(timeout_seconds > 0 ? timeout_seconds : 30);
            context.set_deadline(std::chrono::system_clock::now() + timeout);

            // Set metadata
            if (!config_.game_id.empty()) {
                context.AddMetadata("x-game-id", config_.game_id);
            }
            if (!config_.env.empty()) {
                context.AddMetadata("x-env", config_.env);
            }
            if (!options.idempotency_key.empty()) {
                context.AddMetadata("idempotency-key", options.idempotency_key);
            }
            if (!config_.auth_token.empty()) {
                context.AddMetadata("authorization", "Bearer " + config_.auth_token);
            }
            for (const auto& [k, v] : config_.headers) {
                context.AddMetadata(k, v);
            }

            // Create request
            functionv1::InvokeRequest request;
            request.set_function_id(function_id);
            if (!options.idempotency_key.empty()) {
                request.set_idempotency_key(options.idempotency_key);
            }
            request.set_payload(payload);
            auto* request_metadata = request.mutable_metadata();
            if (!options.route.empty()) (*request_metadata)["route"] = options.route;
            if (!options.target_service_id.empty()) (*request_metadata)["target_service_id"] = options.target_service_id;
            if (!options.hash_key.empty()) (*request_metadata)["hash_key"] = options.hash_key;
            if (!options.trace_id.empty()) (*request_metadata)["trace_id"] = options.trace_id;
            for (const auto& [k, v] : options.metadata) {
                (*request_metadata)[k] = v;
            }

            // Send request
            functionv1::StartJobResponse response;
            grpc::Status status = stub_->StartJob(&context, request, &response);

            if (!status.ok()) {
                std::string error_msg = "gRPC error: " + status.error_message() +
                                     " (code: " + std::to_string(status.error_code()) + ")";
                throw std::runtime_error(error_msg);
            }

            std::string job_id = response.job_id();
            std::cout << "✅ Job started successfully: " << job_id << std::endl;
            return job_id;

        } catch (const std::exception& e) {
            std::cerr << "❌ StartJob failed: " << e.what() << std::endl;
            throw;
        }
#else
        // Fallback simulation when gRPC is not enabled
        std::string job_id = "job-" + function_id + "-" + utils::NewIdempotencyKey().substr(0, 8);
        std::cout << "⚠️  Simulated job started: " << job_id << std::endl;
        return job_id;
#endif
    }

    std::future<std::vector<JobEvent>> StreamJob(const std::string& job_id) {
        return std::async(std::launch::async, [this, job_id]() {
            std::vector<JobEvent> events;

            if (!connected_ && !Connect()) {
                JobEvent error_event;
                error_event.job_id = job_id;
                error_event.error = "Not connected to server";
                error_event.done = true;
                events.push_back(error_event);
                return events;
            }

            std::cout << "Streaming job events for: " << job_id << std::endl;

#ifdef CROUPIER_SDK_ENABLE_GRPC
            try {
                // Create gRPC context
                grpc::ClientContext context;
                context.set_deadline(std::chrono::system_clock::now() + std::chrono::minutes(30)); // Long timeout for streaming

                // Create request
                functionv1::JobStreamRequest request;
                request.set_job_id(job_id);

                // Create streaming reader
                std::unique_ptr<grpc::ClientReader<functionv1::JobEvent>> reader(
                    stub_->StreamJob(&context, request));

                // Read events
                functionv1::JobEvent grpc_event;
                while (reader->Read(&grpc_event)) {
                    JobEvent event;
                    event.job_id = job_id;
                    event.event_type = grpc_event.type();
                    event.message = grpc_event.message();
                    event.progress = grpc_event.progress();
                    event.payload = grpc_event.payload();
                    if (event.event_type == "error") {
                        event.error = event.message;
                    }
                    event.done = (event.event_type == "done" || event.event_type == "error");

                    events.push_back(event);

                    std::cout << "📡 Received event: " << event.event_type << std::endl;

                    // Stop reading if job is done
                    if (event.done) {
                        break;
                    }
                }

                // Check streaming status
                grpc::Status status = reader->Finish();
                if (!status.ok() && status.error_code() != grpc::StatusCode::OK) {
                    std::cerr << "Stream error: " << status.error_message() << std::endl;

                    // Add error event if stream failed
                    JobEvent error_event;
                    error_event.job_id = job_id;
                    error_event.error = "Stream error: " + status.error_message();
                    error_event.done = true;
                    events.push_back(error_event);
                }

                std::cout << "✅ Streaming completed for job: " << job_id << std::endl;
                return events;

            } catch (const std::exception& e) {
                std::cerr << "❌ StreamJob failed: " << e.what() << std::endl;

                JobEvent error_event;
                error_event.job_id = job_id;
                error_event.error = e.what();
                error_event.done = true;
                events.push_back(error_event);
                return events;
            }
#else
            // Fallback simulation when gRPC is not enabled
            JobEvent start_event;
            start_event.event_type = "started";
            start_event.job_id = job_id;
            start_event.payload = "{\"status\":\"job_started\"}";
            events.push_back(start_event);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            JobEvent progress_event;
            progress_event.event_type = "progress";
            progress_event.job_id = job_id;
            progress_event.payload = "{\"progress\":50}";
            events.push_back(progress_event);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            JobEvent done_event;
            done_event.event_type = "completed";
            done_event.job_id = job_id;
            done_event.payload = "{\"result\":\"success\"}";
            done_event.done = true;
            events.push_back(done_event);

            std::cout << "⚠️  Simulated streaming for job: " << job_id << std::endl;
            return events;
#endif
        });
    }

    bool CancelJob(const std::string& job_id) {
        if (!connected_ && !Connect()) {
            std::cerr << "Not connected to server" << std::endl;
            return false;
        }

        std::cout << "Cancelling job: " << job_id << std::endl;

#ifdef CROUPIER_SDK_ENABLE_GRPC
        try {
            // Create gRPC context
            grpc::ClientContext context;
            context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(30));

            // Create request
            functionv1::CancelJobRequest request;
            request.set_job_id(job_id);

            // Send request
            functionv1::StartJobResponse response;
            grpc::Status status = stub_->CancelJob(&context, request, &response);

            if (!status.ok()) {
                std::cerr << "❌ CancelJob failed: " << status.error_message() << std::endl;
                return false;
            }

            std::cout << "✅ Job cancelled successfully: " << job_id << std::endl;
            return true;

        } catch (const std::exception& e) {
            std::cerr << "❌ CancelJob failed: " << e.what() << std::endl;
            return false;
        }
#else
        // Fallback simulation when gRPC is not enabled
        std::cout << "⚠️  Simulated job cancellation: " << job_id << std::endl;
        return true;
#endif
    }

    void SetSchema(const std::string& function_id, const std::map<std::string, std::string>& schema) {
        schemas_[function_id] = schema;
        std::cout << "Set schema for function: " << function_id << std::endl;
    }

    void Close() {
        connected_ = false;
        schemas_.clear();
        std::cout << "Invoker closed" << std::endl;
    }
};

// CroupierClient public interface
CroupierClient::CroupierClient(const ClientConfig& config)
    : impl_(std::make_unique<Impl>(config)) {}

CroupierClient::~CroupierClient() = default;

// ========== Existing Function Registration ==========
bool CroupierClient::RegisterFunction(const FunctionDescriptor& desc, FunctionHandler handler) {
    return impl_->RegisterFunction(desc, handler);
}

// ========== Virtual Object Registration ==========
bool CroupierClient::RegisterVirtualObject(
    const VirtualObjectDescriptor& desc,
    const std::map<std::string, FunctionHandler>& handlers) {
    return impl_->RegisterVirtualObject(desc, handlers);
}

bool CroupierClient::RegisterComponent(const ComponentDescriptor& comp) {
    return impl_->RegisterComponent(comp);
}

bool CroupierClient::LoadComponentFromFile(const std::string& config_file) {
    return impl_->LoadComponentFromFile(config_file);
}

// ========== Management Interface ==========
std::vector<VirtualObjectDescriptor> CroupierClient::GetRegisteredObjects() const {
    return impl_->GetRegisteredObjects();
}

std::vector<ComponentDescriptor> CroupierClient::GetRegisteredComponents() const {
    return impl_->GetRegisteredComponents();
}

bool CroupierClient::UnregisterVirtualObject(const std::string& object_id) {
    return impl_->UnregisterVirtualObject(object_id);
}

bool CroupierClient::UnregisterComponent(const std::string& component_id) {
    return impl_->UnregisterComponent(component_id);
}

// ========== Core Operations ==========

bool CroupierClient::Connect() {
    return impl_->Connect();
}

void CroupierClient::Serve() {
    impl_->Serve();
}

void CroupierClient::Stop() {
    impl_->Stop();
}

void CroupierClient::Close() {
    impl_->Close();
}

std::string CroupierClient::GetLocalAddress() const {
    return impl_->GetLocalAddress();
}

// CroupierInvoker public interface
CroupierInvoker::CroupierInvoker(const InvokerConfig& config)
    : impl_(std::make_unique<Impl>(config)) {}

CroupierInvoker::~CroupierInvoker() = default;

bool CroupierInvoker::Connect() {
    return impl_->Connect();
}

std::string CroupierInvoker::Invoke(const std::string& function_id, const std::string& payload,
                                   const InvokeOptions& options) {
    return impl_->Invoke(function_id, payload, options);
}

std::string CroupierInvoker::StartJob(const std::string& function_id, const std::string& payload,
                                     const InvokeOptions& options) {
    return impl_->StartJob(function_id, payload, options);
}

std::future<std::vector<JobEvent>> CroupierInvoker::StreamJob(const std::string& job_id) {
    return impl_->StreamJob(job_id);
}

bool CroupierInvoker::CancelJob(const std::string& job_id) {
    return impl_->CancelJob(job_id);
}

void CroupierInvoker::SetSchema(const std::string& function_id,
                               const std::map<std::string, std::string>& schema) {
    impl_->SetSchema(function_id, schema);
}

void CroupierInvoker::Close() {
    impl_->Close();
}

// ========== Virtual Object Utility Functions Implementation ==========
namespace utils {

// Load virtual object descriptor from JSON file
VirtualObjectDescriptor LoadObjectDescriptor(const std::string& file_path) {
    VirtualObjectDescriptor desc;

    try {
        // Read file content
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }

        std::string json_content((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

        // Parse JSON
#ifdef CROUPIER_SDK_ENABLE_JSON
        nlohmann::json json_obj = nlohmann::json::parse(json_content);

        // Extract basic fields
        if (json_obj.contains("id")) {
            desc.id = json_obj["id"];
        }
        if (json_obj.contains("version")) {
            desc.version = json_obj["version"];
        }
        if (json_obj.contains("name")) {
            desc.name = json_obj["name"];
        }
        if (json_obj.contains("description")) {
            desc.description = json_obj["description"];
        }

        // Extract functions if present
        if (json_obj.contains("functions") && json_obj["functions"].is_array()) {
            for (const auto& func : json_obj["functions"]) {
                FunctionDescriptor func_desc;
                if (func.contains("id")) {
                    func_desc.id = func["id"];
                }
                if (func.contains("name")) {
                    func_desc.name = func["name"];
                }
                if (func.contains("description")) {
                    func_desc.description = func["description"];
                }
                desc.functions.push_back(func_desc);
            }
        }

        // Extract metadata if present
        if (json_obj.contains("metadata") && json_obj["metadata"].is_object()) {
            for (auto& [key, value] : json_obj["metadata"].items()) {
                if (value.is_string()) {
                    desc.metadata[key] = value.get<std::string>();
                } else {
                    desc.metadata[key] = value.dump();
                }
            }
        }
#else
        // Fallback: use simple JSON parsing
        auto json_simple = utils::JsonUtils::ParseJson(json_content);

        desc.id = json_simple.value("id", "unknown");
        desc.version = json_simple.value("version", "1.0.0");
        desc.name = json_simple.value("name", "Unnamed Object");
        desc.description = json_simple.value("description", "No description");
#endif

        std::cout << "✅ Successfully loaded virtual object descriptor from: " << file_path << std::endl;
        return desc;

    } catch (const std::exception& e) {
        std::cerr << "❌ Failed to load object descriptor from " << file_path << ": " << e.what() << std::endl;

        // Return default descriptor on error
        desc.id = "error";
        desc.version = "0.0.0";
        desc.name = "Error Loading Object";
        desc.description = "Failed to load: " + std::string(e.what());
        return desc;
    }
}

// Load component descriptor from JSON file
ComponentDescriptor LoadComponentDescriptor(const std::string& file_path) {
    ComponentDescriptor desc;

    try {
        // Read file content
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }

        std::string json_content((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

        // Parse JSON
#ifdef CROUPIER_SDK_ENABLE_JSON
        nlohmann::json json_obj = nlohmann::json::parse(json_content);

        // Extract basic fields
        if (json_obj.contains("id")) {
            desc.id = json_obj["id"];
        }
        if (json_obj.contains("version")) {
            desc.version = json_obj["version"];
        }
        if (json_obj.contains("name")) {
            desc.name = json_obj["name"];
        }
        if (json_obj.contains("description")) {
            desc.description = json_obj["description"];
        }
        if (json_obj.contains("type")) {
            desc.type = json_obj["type"];
        }

        // Extract dependencies if present
        if (json_obj.contains("dependencies") && json_obj["dependencies"].is_array()) {
            for (const auto& dep : json_obj["dependencies"]) {
                if (dep.is_string()) {
                    desc.dependencies.push_back(dep.get<std::string>());
                }
            }
        }

        // Extract config if present
        if (json_obj.contains("config") && json_obj["config"].is_object()) {
            for (auto& [key, value] : json_obj["config"].items()) {
                if (value.is_string()) {
                    desc.config[key] = value.get<std::string>();
                } else {
                    desc.config[key] = value.dump();
                }
            }
        }

        // Extract metadata if present
        if (json_obj.contains("metadata") && json_obj["metadata"].is_object()) {
            for (auto& [key, value] : json_obj["metadata"].items()) {
                if (value.is_string()) {
                    desc.metadata[key] = value.get<std::string>();
                } else {
                    desc.metadata[key] = value.dump();
                }
            }
        }

        // Check if component is enabled (default to true if not specified)
        if (json_obj.contains("enabled")) {
            desc.enabled = json_obj["enabled"].get<bool>();
        }
#else
        // Fallback: use simple JSON parsing
        auto json_simple = utils::JsonUtils::ParseJson(json_content);

        desc.id = json_simple.value("id", "unknown");
        desc.version = json_simple.value("version", "1.0.0");
        desc.name = json_simple.value("name", "Unnamed Component");
        desc.description = json_simple.value("description", "No description");
        desc.type = json_simple.value("type", "generic");
        desc.enabled = true; // Default to enabled
#endif

        std::cout << "✅ Successfully loaded component descriptor from: " << file_path << std::endl;
        return desc;

    } catch (const std::exception& e) {
        std::cerr << "❌ Failed to load component descriptor from " << file_path << ": " << e.what() << std::endl;

        // Return default descriptor on error
        desc.id = "error";
        desc.version = "0.0.0";
        desc.name = "Error Loading Component";
        desc.description = "Failed to load: " + std::string(e.what());
        desc.type = "error";
        desc.enabled = false;
        return desc;
    }
}

// Validate virtual object descriptor completeness
bool ValidateObjectDescriptor(const VirtualObjectDescriptor& desc) {
    // Basic validation
    if (desc.id.empty()) {
        std::cerr << "Object descriptor validation failed: empty ID" << std::endl;
        return false;
    }

    if (desc.version.empty()) {
        std::cerr << "Object descriptor validation failed: empty version" << std::endl;
        return false;
    }

    if (desc.operations.empty()) {
        std::cerr << "Object descriptor validation failed: no operations defined" << std::endl;
        return false;
    }

    // Validate operation mappings
    for (const auto& op : desc.operations) {
        if (op.first.empty() || op.second.empty()) {
            std::cerr << "Object descriptor validation failed: invalid operation mapping" << std::endl;
            return false;
        }
    }

    // Validate relationships
    for (const auto& rel : desc.relationships) {
        if (rel.second.type.empty() || rel.second.entity.empty()) {
            std::cerr << "Object descriptor validation failed: invalid relationship definition" << std::endl;
            return false;
        }

        // Check relationship type
        const std::string& type = rel.second.type;
        if (type != "one-to-many" && type != "many-to-one" && type != "many-to-many" && type != "one-to-one") {
            std::cerr << "Object descriptor validation failed: invalid relationship type: " << type << std::endl;
            return false;
        }
    }

    return true;
}

// Validate component descriptor completeness
bool ValidateComponentDescriptor(const ComponentDescriptor& comp) {
    // Basic validation
    if (comp.id.empty()) {
        std::cerr << "Component descriptor validation failed: empty ID" << std::endl;
        return false;
    }

    if (comp.version.empty()) {
        std::cerr << "Component descriptor validation failed: empty version" << std::endl;
        return false;
    }

    // Validate all entities
    for (const auto& entity : comp.entities) {
        if (!ValidateObjectDescriptor(entity)) {
            std::cerr << "Component descriptor validation failed: invalid entity " << entity.id << std::endl;
            return false;
        }
    }

    // Validate all functions
    for (const auto& func : comp.functions) {
        if (func.id.empty() || func.version.empty()) {
            std::cerr << "Component descriptor validation failed: invalid function descriptor" << std::endl;
            return false;
        }
    }

    return true;
}

// Generate default object configuration template
std::string GenerateObjectTemplate(const std::string& object_id) {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"id\": \"" << object_id << "\",\n";
    ss << "  \"version\": \"1.0.0\",\n";
    ss << "  \"name\": \"" << object_id << " Entity\",\n";
    ss << "  \"description\": \"Auto-generated template for " << object_id << "\",\n";
    ss << "  \"schema\": {\n";
    ss << "    \"type\": \"object\",\n";
    ss << "    \"properties\": {\n";
    ss << "      \"id\": {\"type\": \"string\", \"title\": \"ID\"},\n";
    ss << "      \"name\": {\"type\": \"string\", \"title\": \"Name\"}\n";
    ss << "    },\n";
    ss << "    \"required\": [\"id\"]\n";
    ss << "  },\n";
    ss << "  \"operations\": {\n";
    ss << "    \"create\": \"" << object_id << ".create\",\n";
    ss << "    \"read\": \"" << object_id << ".get\",\n";
    ss << "    \"update\": \"" << object_id << ".update\",\n";
    ss << "    \"delete\": \"" << object_id << ".delete\"\n";
    ss << "  },\n";
    ss << "  \"relationships\": {}\n";
    ss << "}";
    return ss.str();
}

// Generate default component configuration template
std::string GenerateComponentTemplate(const std::string& component_id) {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"id\": \"" << component_id << "\",\n";
    ss << "  \"version\": \"1.0.0\",\n";
    ss << "  \"name\": \"" << component_id << " Component\",\n";
    ss << "  \"description\": \"Auto-generated template for " << component_id << "\",\n";
    ss << "  \"entities\": [],\n";
    ss << "  \"functions\": [],\n";
    ss << "  \"resources\": {},\n";
    ss << "  \"config\": {}\n";
    ss << "}";
    return ss.str();
}

// Parse object descriptor from JSON string
VirtualObjectDescriptor ParseObjectDescriptor(const std::string& json) {
    (void)json; // Suppress unused parameter warning - JSON parsing not implemented yet

    // TODO: Implement proper JSON parsing
    // For now, return a placeholder
    VirtualObjectDescriptor desc;
    desc.id = "parsed-object";
    desc.version = "1.0.0";
    std::cerr << "ParseObjectDescriptor: JSON parsing not yet implemented" << std::endl;
    return desc;
}

// Parse component descriptor from JSON string
ComponentDescriptor ParseComponentDescriptor(const std::string& json) {
    (void)json; // Suppress unused parameter warning - JSON parsing not implemented yet

    // TODO: Implement proper JSON parsing
    // For now, return a placeholder
    ComponentDescriptor comp;
    comp.id = "parsed-component";
    comp.version = "1.0.0";
    std::cerr << "ParseComponentDescriptor: JSON parsing not yet implemented" << std::endl;
    return comp;
}

// Serialize object descriptor to JSON string
std::string ObjectDescriptorToJSON(const VirtualObjectDescriptor& desc) {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"id\": \"" << desc.id << "\",\n";
    ss << "  \"version\": \"" << desc.version << "\",\n";
    ss << "  \"name\": \"" << desc.name << "\",\n";
    ss << "  \"description\": \"" << desc.description << "\",\n";
    ss << "  \"schema\": {";

    bool first_schema = true;
    for (const auto& schema_item : desc.schema) {
        if (!first_schema) ss << ",";
        ss << "\n    \"" << schema_item.first << "\": \"" << schema_item.second << "\"";
        first_schema = false;
    }
    ss << "\n  },\n";

    ss << "  \"operations\": {";
    bool first_op = true;
    for (const auto& op : desc.operations) {
        if (!first_op) ss << ",";
        ss << "\n    \"" << op.first << "\": \"" << op.second << "\"";
        first_op = false;
    }
    ss << "\n  },\n";

    ss << "  \"relationships\": {";
    bool first_rel = true;
    for (const auto& rel : desc.relationships) {
        if (!first_rel) ss << ",";
        ss << "\n    \"" << rel.first << "\": {";
        ss << "\n      \"type\": \"" << rel.second.type << "\",";
        ss << "\n      \"entity\": \"" << rel.second.entity << "\",";
        ss << "\n      \"foreign_key\": \"" << rel.second.foreign_key << "\"";
        ss << "\n    }";
        first_rel = false;
    }
    ss << "\n  }\n";
    ss << "}";

    return ss.str();
}

// Serialize component descriptor to JSON string
std::string ComponentDescriptorToJSON(const ComponentDescriptor& comp) {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"id\": \"" << comp.id << "\",\n";
    ss << "  \"version\": \"" << comp.version << "\",\n";
    ss << "  \"name\": \"" << comp.name << "\",\n";
    ss << "  \"description\": \"" << comp.description << "\",\n";
    ss << "  \"entities\": [";

    bool first_entity = true;
    for (const auto& entity : comp.entities) {
        if (!first_entity) ss << ",";
        ss << "\n    \"" << entity.id << "\"";  // Simplified - just show ID
        first_entity = false;
    }
    ss << "\n  ],\n";

    ss << "  \"functions\": [";
    bool first_func = true;
    for (const auto& func : comp.functions) {
        if (!first_func) ss << ",";
        ss << "\n    \"" << func.id << "\"";  // Simplified - just show ID
        first_func = false;
    }
    ss << "\n  ],\n";

    ss << "  \"resources\": {},\n";  // TODO: Implement resources serialization
    ss << "  \"config\": {}\n";      // TODO: Implement config serialization
    ss << "}";

    return ss.str();
}

} // namespace utils

} // namespace sdk
} // namespace croupier
