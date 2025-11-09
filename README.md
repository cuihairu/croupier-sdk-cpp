# Croupier SDK (C++)

A comprehensive C++ SDK for Croupier that provides:
- Function hosting (CroupierClient) - register handlers and serve them to the Agent
- Function calling (CroupierInvoker) - call functions via Server/Agent
- Async job support with streaming and cancellation
- JSON schema validation and utilities
- Thread-safe implementation with modern C++ features

## Features

### CroupierClient (Function Provider)
- Register function handlers with schema validation
- Local gRPC server for handling function calls
- Automatic registration with Croupier Agent
- Thread-safe operation with proper lifecycle management

### CroupierInvoker (Function Caller)
- Synchronous and asynchronous function calling
- Job streaming with real-time event updates
- Client-side payload validation
- Flexible routing options (load balancing, broadcast, targeted, hash)
- Idempotency support

### Utilities
- Idempotency key generation
- Basic JSON parsing and serialization
- JSON schema validation
- Configuration structures for easy setup

## Quick Start

### Building the SDK

```bash
# Generate build files
cmake -S . -B build

# Build the library and examples
cmake --build build -j

# Run the example
./build/croupier_example
```

### Function Provider Example

```cpp
#include "croupier/sdk/croupier_client.h"
using namespace croupier::sdk;

// Define a function handler
std::string MyHandler(const std::string& context, const std::string& payload) {
    auto data = utils::ParseJSON(payload);
    // Process the data...

    std::map<std::string, std::string> response;
    response["status"] = "success";
    response["result"] = "processed";
    return utils::ToJSON(response);
}

int main() {
    // Configure and create client
    ClientConfig config;
    config.agent_addr = "127.0.0.1:19090";
    config.service_id = "my-cpp-service";

    CroupierClient client(config);

    // Register function
    FunctionDescriptor desc;
    desc.id = "my-function";
    desc.version = "1.0.0";

    client.RegisterFunction(desc, MyHandler);

    // Connect and serve
    client.Connect();
    client.Serve();  // Blocking call

    return 0;
}
```

### Function Caller Example

```cpp
#include "croupier/sdk/croupier_client.h"
using namespace croupier::sdk;

int main() {
    // Configure invoker
    InvokerConfig config;
    config.address = "127.0.0.1:8080";
    config.insecure = true;  // For development
    config.game_id = "my-game";

    CroupierInvoker invoker(config);
    invoker.Connect();

    // Call function synchronously
    InvokeOptions options;
    options.idempotency_key = utils::NewIdempotencyKey();
    options.route = "lb";  // Load balance

    std::string payload = "{\"param1\":\"value1\"}";
    std::string response = invoker.Invoke("my-function", payload, options);

    std::cout << "Response: " << response << std::endl;

    // Start async job
    std::string job_id = invoker.StartJob("long-running-function", payload, options);

    // Stream job events
    auto events_future = invoker.StreamJob(job_id);
    auto events = events_future.get();

    for (const auto& event : events) {
        std::cout << "Event: " << event.event_type
                  << ", Payload: " << event.payload << std::endl;
    }

    invoker.Close();
    return 0;
}
```

## API Reference

### ClientConfig
Configuration for CroupierClient:
- `agent_addr`: Agent address (default: "127.0.0.1:19090")
- `local_listen`: Local server bind address (default: "127.0.0.1:0")
- `service_id`: Service identifier for routing
- `service_version`: Service version
- `insecure`: Use insecure connection for development

### InvokerConfig
Configuration for CroupierInvoker:
- `address`: Server/Agent address
- `insecure`: Use insecure connection
- `cert_file`, `key_file`, `ca_file`: TLS certificates for secure connections
- `timeout_seconds`: Request timeout
- `auth_token`: Bearer token for authentication
- `game_id`, `env`: Default metadata for requests

### FunctionDescriptor
- `id`: Function identifier
- `version`: Function version
- `schema`: JSON schema for validation (key-value pairs)

### InvokeOptions
- `idempotency_key`: Prevent duplicate execution
- `route`: Routing strategy ("lb", "broadcast", "targeted", "hash")
- `target_service_id`: For targeted routing
- `hash_key`: For hash-based routing
- `trace_id`: Request tracing
- `metadata`: Additional metadata

### Utilities
- `utils::NewIdempotencyKey()`: Generate unique key
- `utils::ParseJSON(json_string)`: Parse JSON to map
- `utils::ToJSON(data_map)`: Serialize map to JSON
- `utils::ValidateJSON(json, schema)`: Validate JSON against schema

## Architecture

The SDK follows the same patterns as the Go SDK:

1. **Client Pattern**: Register functions locally, serve them via local gRPC server, register with Agent
2. **Invoker Pattern**: Connect to Server/Agent, call functions with various routing options
3. **Async Jobs**: Long-running operations with streaming progress updates
4. **Schema Validation**: Client-side and server-side payload validation

## Development Status

### Current Implementation
✅ Complete API design and structure
✅ Function registration and handling
✅ Synchronous and asynchronous function calling
✅ Job streaming and cancellation
✅ JSON utilities and basic validation
✅ Thread-safe implementation
✅ Comprehensive examples and documentation

### Future Enhancements
🔄 Real gRPC integration (currently simulated)
🔄 Advanced JSON schema validation
🔄 TLS/mTLS support
🔄 Connection pooling and retries
🔄 Performance optimizations
🔄 Unit tests

## Building for Production

For production deployments:

1. Enable TLS by setting `insecure = false` in configurations
2. Provide proper certificate files (cert_file, key_file, ca_file)
3. Use appropriate timeout values
4. Implement proper error handling and logging
5. Consider connection pooling for high-throughput scenarios

## Links

- Main project: https://github.com/cuihairu/croupier
- Go SDK (reference): https://github.com/cuihairu/croupier-sdk-go
- Protocol definitions: https://github.com/cuihairu/croupier/tree/main/proto

## License

See LICENSE file for details.
