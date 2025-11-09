#include "croupier/sdk/croupier_client.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace croupier::sdk;

// Example function handlers
std::string HelloWorldHandler(const std::string& context, const std::string& payload) {
    std::cout << "HelloWorld called with payload: " << payload << std::endl;

    auto data = utils::ParseJSON(payload);
    std::string name = data.count("name") ? data["name"] : "World";

    std::map<std::string, std::string> response;
    response["message"] = "Hello, " + name + "!";
    response["timestamp"] = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());

    return utils::ToJSON(response);
}

std::string CalculatorHandler(const std::string& context, const std::string& payload) {
    std::cout << "Calculator called with payload: " << payload << std::endl;

    auto data = utils::ParseJSON(payload);

    if (data.count("operation") && data.count("a") && data.count("b")) {
        double a = std::stod(data["a"]);
        double b = std::stod(data["b"]);
        std::string op = data["operation"];
        double result = 0.0;

        if (op == "add") result = a + b;
        else if (op == "subtract") result = a - b;
        else if (op == "multiply") result = a * b;
        else if (op == "divide" && b != 0) result = a / b;
        else {
            std::map<std::string, std::string> error;
            error["error"] = "Invalid operation or division by zero";
            return utils::ToJSON(error);
        }

        std::map<std::string, std::string> response;
        response["result"] = std::to_string(result);
        response["operation"] = op;
        return utils::ToJSON(response);
    }

    std::map<std::string, std::string> error;
    error["error"] = "Missing required parameters: operation, a, b";
    return utils::ToJSON(error);
}

void DemoClient() {
    std::cout << "\n=== Croupier C++ SDK Client Demo ===" << std::endl;

    // Configure client
    ClientConfig config;
    config.agent_addr = "127.0.0.1:19090";
    config.service_id = "cpp-demo-service";
    config.service_version = "1.0.0";

    // Create client
    CroupierClient client(config);

    // Register functions
    FunctionDescriptor hello_desc;
    hello_desc.id = "hello";
    hello_desc.version = "1.0.0";
    hello_desc.schema["type"] = "object";
    hello_desc.schema["properties"] = "{\"name\":{\"type\":\"string\"}}";

    if (!client.RegisterFunction(hello_desc, HelloWorldHandler)) {
        std::cerr << "Failed to register hello function" << std::endl;
        return;
    }

    FunctionDescriptor calc_desc;
    calc_desc.id = "calculator";
    calc_desc.version = "1.0.0";
    calc_desc.schema["type"] = "object";
    calc_desc.schema["required"] = "[\"operation\",\"a\",\"b\"]";

    if (!client.RegisterFunction(calc_desc, CalculatorHandler)) {
        std::cerr << "Failed to register calculator function" << std::endl;
        return;
    }

    // Connect and serve
    if (!client.Connect()) {
        std::cerr << "Failed to connect to agent" << std::endl;
        return;
    }

    std::cout << "Client local address: " << client.GetLocalAddress() << std::endl;
    std::cout << "Client will serve for 10 seconds..." << std::endl;

    // Start serving in a separate thread
    std::thread serve_thread([&client]() {
        client.Serve();
    });

    // Let it serve for a few seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop the client
    client.Stop();

    if (serve_thread.joinable()) {
        serve_thread.join();
    }

    std::cout << "Client demo completed" << std::endl;
}

void DemoInvoker() {
    std::cout << "\n=== Croupier C++ SDK Invoker Demo ===" << std::endl;

    // Configure invoker
    InvokerConfig config;
    config.address = "127.0.0.1:8080"; // Server address
    config.insecure = true; // For development
    config.game_id = "demo-game";
    config.env = "development";
    config.timeout_seconds = 10;

    // Create invoker
    CroupierInvoker invoker(config);

    try {
        // Connect to server
        if (!invoker.Connect()) {
            std::cerr << "Failed to connect to server" << std::endl;
            return;
        }

        // Set schema for client-side validation
        std::map<std::string, std::string> hello_schema;
        hello_schema["type"] = "object";
        hello_schema["properties"] = "{\"name\":{\"type\":\"string\"}}";
        invoker.SetSchema("hello", hello_schema);

        // Test synchronous function call
        std::cout << "\n--- Testing synchronous function call ---" << std::endl;

        InvokeOptions options;
        options.idempotency_key = utils::NewIdempotencyKey();
        options.route = "lb";

        std::string hello_payload = "{\"name\":\"C++ Developer\"}";
        std::string hello_response = invoker.Invoke("hello", hello_payload, options);
        std::cout << "Hello response: " << hello_response << std::endl;

        // Test calculator function
        std::cout << "\n--- Testing calculator function ---" << std::endl;

        std::string calc_payload = "{\"operation\":\"add\",\"a\":\"15\",\"b\":\"25\"}";
        std::string calc_response = invoker.Invoke("calculator", calc_payload, options);
        std::cout << "Calculator response: " << calc_response << std::endl;

        // Test async job
        std::cout << "\n--- Testing async job ---" << std::endl;

        std::string job_id = invoker.StartJob("calculator", calc_payload, options);
        std::cout << "Started job: " << job_id << std::endl;

        // Stream job events
        auto job_events_future = invoker.StreamJob(job_id);
        auto job_events = job_events_future.get();

        std::cout << "Job events received:" << std::endl;
        for (const auto& event : job_events) {
            std::cout << "  Event: " << event.event_type
                     << ", JobID: " << event.job_id
                     << ", Payload: " << event.payload;
            if (!event.error.empty()) {
                std::cout << ", Error: " << event.error;
            }
            std::cout << ", Done: " << (event.done ? "true" : "false") << std::endl;
        }

        // Test job cancellation
        std::cout << "\n--- Testing job cancellation ---" << std::endl;

        std::string another_job_id = invoker.StartJob("hello", hello_payload, options);
        std::cout << "Started job for cancellation: " << another_job_id << std::endl;

        bool cancelled = invoker.CancelJob(another_job_id);
        std::cout << "Job cancellation " << (cancelled ? "succeeded" : "failed") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error in invoker demo: " << e.what() << std::endl;
    }

    invoker.Close();
    std::cout << "Invoker demo completed" << std::endl;
}

void DemoUtilities() {
    std::cout << "\n=== Croupier C++ SDK Utilities Demo ===" << std::endl;

    // Test idempotency key generation
    std::cout << "Generated idempotency keys:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "  Key " << (i+1) << ": " << utils::NewIdempotencyKey() << std::endl;
    }

    // Test JSON utilities
    std::cout << "\nTesting JSON utilities:" << std::endl;

    std::map<std::string, std::string> test_data;
    test_data["name"] = "John Doe";
    test_data["age"] = "30";
    test_data["city"] = "New York";

    std::string json_str = utils::ToJSON(test_data);
    std::cout << "Serialized JSON: " << json_str << std::endl;

    auto parsed_data = utils::ParseJSON(json_str);
    std::cout << "Parsed data:" << std::endl;
    for (const auto& pair : parsed_data) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // Test JSON validation
    std::cout << "\nTesting JSON validation:" << std::endl;

    std::map<std::string, std::string> simple_schema;
    simple_schema["type"] = "object";

    std::string valid_json = "{\"test\":\"value\"}";
    std::string invalid_json = "{\"test\":\"value\""; // Missing closing brace

    std::cout << "Valid JSON validation: " << (utils::ValidateJSON(valid_json, simple_schema) ? "PASS" : "FAIL") << std::endl;
    std::cout << "Invalid JSON validation: " << (utils::ValidateJSON(invalid_json, simple_schema) ? "PASS" : "FAIL") << std::endl;

    std::cout << "Utilities demo completed" << std::endl;
}

int main() {
    std::cout << "Croupier C++ SDK Example Application" << std::endl;
    std::cout << "====================================" << std::endl;

    // Demo utilities first
    DemoUtilities();

    // Demo client (function provider)
    DemoClient();

    // Demo invoker (function caller)
    DemoInvoker();

    std::cout << "\nAll demos completed successfully!" << std::endl;
    return 0;
}

