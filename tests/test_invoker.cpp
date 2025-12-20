#include <gtest/gtest.h>

#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/grpc_service.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

using namespace croupier::sdk;

TEST(InvokerTest, ValidateJsonBasic) {
  EXPECT_TRUE(utils::ValidateJSON(R"({"ok":true})", {}));
  EXPECT_FALSE(utils::ValidateJSON("{not json", {}));
}

#ifndef CROUPIER_SDK_ENABLE_GRPC

TEST(InvokerTest, MockInvokeAndJobFlow) {
  InvokerConfig cfg;
  cfg.address = "127.0.0.1:19090";  // not used in mock mode
  cfg.timeout_seconds = 1;
  cfg.insecure = true;

  CroupierInvoker invoker(cfg);
  ASSERT_TRUE(invoker.Connect());

  InvokeOptions opts;
  opts.idempotency_key = "k1";

  const std::string out = invoker.Invoke("player.ping", R"({"x":1})", opts);
  EXPECT_NE(out.find("\"status\":\"success\""), std::string::npos);
  EXPECT_NE(out.find("\"function_id\":\"player.ping\""), std::string::npos);

  const std::string job_id = invoker.StartJob("player.job", R"({"x":2})", {});
  EXPECT_NE(job_id.find("job-player.job-"), std::string::npos);

  const auto events = invoker.StreamJob(job_id).get();
  ASSERT_EQ(events.size(), 3u);
  EXPECT_EQ(events[0].event_type, "started");
  EXPECT_EQ(events[1].event_type, "progress");
  EXPECT_EQ(events[2].event_type, "completed");
  EXPECT_TRUE(events[2].done);

  EXPECT_TRUE(invoker.CancelJob(job_id));
}

#else

namespace {

class InProcessFunctionServer {
 public:
  InProcessFunctionServer(std::map<std::string, FunctionHandler> handlers)
      : handlers_(std::move(handlers)),
        service_(handlers_) {}

  void Start() {
    grpc::ServerBuilder builder;
    int port = 0;
    builder.AddListeningPort("127.0.0.1:0", grpc::InsecureServerCredentials(), &port);
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
    ASSERT_TRUE(server_);
    ASSERT_GT(port, 0);
    address_ = "127.0.0.1:" + std::to_string(port);
  }

  void Stop() {
    if (server_) {
      server_->Shutdown();
      server_.reset();
    }
  }

  const std::string& address() const { return address_; }

 private:
  std::map<std::string, FunctionHandler> handlers_;
  croupier::sdk::grpc_service::LocalFunctionServiceImpl service_;
  std::unique_ptr<grpc::Server> server_;
  std::string address_;
};

}  // namespace

TEST(InvokerTest, GrpcInvokePassesRequestMetadataToHandler) {
  std::mutex mu;
  std::string last_context;
  std::string last_payload;

  InProcessFunctionServer server({
      {"fn.echo",
       [&](const std::string& context, const std::string& payload) -> std::string {
         std::lock_guard<std::mutex> lock(mu);
         last_context = context;
         last_payload = payload;
         return payload;
       }},
  });
  server.Start();

  InvokerConfig cfg;
  cfg.address = server.address();
  cfg.timeout_seconds = 5;
  cfg.insecure = true;

  CroupierInvoker invoker(cfg);
  ASSERT_TRUE(invoker.Connect());

  InvokeOptions opts;
  opts.metadata["k"] = "v";
  const std::string out = invoker.Invoke("fn.echo", "hello", opts);
  EXPECT_EQ(out, "hello");

  {
    std::lock_guard<std::mutex> lock(mu);
    EXPECT_EQ(last_payload, "hello");
    EXPECT_NE(last_context.find("\"k\":\"v\""), std::string::npos);
  }

  server.Stop();
}

TEST(InvokerTest, GrpcJobStartStreamAndCancel) {
  std::atomic<bool> handler_started{false};

  InProcessFunctionServer server({
      {"job.slow",
       [&](const std::string& /*context*/, const std::string& /*payload*/) -> std::string {
         handler_started.store(true);
         std::this_thread::sleep_for(std::chrono::milliseconds(200));
         return R"({"ok":true})";
       }},
  });
  server.Start();

  InvokerConfig cfg;
  cfg.address = server.address();
  cfg.timeout_seconds = 5;
  cfg.insecure = true;

  CroupierInvoker invoker(cfg);
  ASSERT_TRUE(invoker.Connect());

  const std::string job_id = invoker.StartJob("job.slow", "{}", {});
  EXPECT_FALSE(job_id.empty());

  // Ensure the job thread is running before cancellation to exercise CancelJob path.
  for (int i = 0; i < 50 && !handler_started.load(); i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  EXPECT_TRUE(invoker.CancelJob(job_id));

  const auto events = invoker.StreamJob(job_id).get();
  ASSERT_FALSE(events.empty());
  EXPECT_EQ(events.front().event_type, "started");

  bool saw_cancelled = false;
  for (const auto& e : events) {
    if (e.event_type == "cancelled") {
      saw_cancelled = true;
    }
  }
  EXPECT_TRUE(saw_cancelled);

  server.Stop();
}

#endif

