#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>
#include <future>
#include <vector>

namespace croupier {
namespace sdk {

// Forward declarations
class CroupierClient;
class CroupierInvoker;

// Function handler type
using FunctionHandler = std::function<std::string(const std::string& context, const std::string& payload)>;

// Function descriptor with schema support
struct FunctionDescriptor {
    std::string id;
    std::string version;
    std::map<std::string, std::string> schema; // JSON schema as key-value pairs for simplicity
};

// Client configuration
struct ClientConfig {
    std::string agent_addr = "127.0.0.1:19090";
    std::string local_listen = "127.0.0.1:0";
    std::string service_id = "cpp-service";
    std::string service_version = "1.0.0";
    bool insecure = true; // For development; set false for production with TLS
};

// Invoker configuration
struct InvokerConfig {
    std::string address;
    bool insecure = true;
    std::string cert_file;
    std::string key_file;
    std::string ca_file;
    std::string server_name;
    int timeout_seconds = 5;
    std::string auth_token;
    std::string game_id;
    std::string env;
    std::map<std::string, std::string> headers;
};

// Invoke options for function calls
struct InvokeOptions {
    std::string idempotency_key;
    std::string route; // "lb", "broadcast", "targeted", "hash"
    std::string target_service_id;
    std::string hash_key;
    std::string trace_id;
    std::map<std::string, std::string> metadata;
};

// Job event for streaming operations
struct JobEvent {
    std::string event_type;
    std::string job_id;
    std::string payload;
    std::string error;
    bool done = false;
};

// Main SDK client for hosting functions
class CroupierClient {
public:
    explicit CroupierClient(const ClientConfig& config);
    ~CroupierClient();

    // Register a function handler with optional schema
    bool RegisterFunction(const FunctionDescriptor& desc, FunctionHandler handler);

    // Connect to agent and start local service
    bool Connect();

    // Start serving (blocking call until Stop() is called)
    void Serve();

    // Stop the client
    void Stop();

    // Close and cleanup
    void Close();

    // Get local server address after starting
    std::string GetLocalAddress() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

// SDK invoker for calling remote functions
class CroupierInvoker {
public:
    explicit CroupierInvoker(const InvokerConfig& config);
    ~CroupierInvoker();

    // Connect to server/agent
    bool Connect();

    // Invoke a function synchronously
    std::string Invoke(const std::string& function_id, const std::string& payload,
                      const InvokeOptions& options = {});

    // Start an async job
    std::string StartJob(const std::string& function_id, const std::string& payload,
                        const InvokeOptions& options = {});

    // Stream job events (returns a future that yields events)
    std::future<std::vector<JobEvent>> StreamJob(const std::string& job_id);

    // Cancel a running job
    bool CancelJob(const std::string& job_id);

    // Set schema for client-side validation
    void SetSchema(const std::string& function_id, const std::map<std::string, std::string>& schema);

    // Close connection
    void Close();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

// Utility functions
namespace utils {
    // Generate idempotency key
    std::string NewIdempotencyKey();

    // Validate JSON against simple schema (basic validation)
    bool ValidateJSON(const std::string& json, const std::map<std::string, std::string>& schema);

    // Parse JSON to map (simplified)
    std::map<std::string, std::string> ParseJSON(const std::string& json);

    // Serialize map to JSON
    std::string ToJSON(const std::map<std::string, std::string>& data);
}

} // namespace sdk
} // namespace croupier

