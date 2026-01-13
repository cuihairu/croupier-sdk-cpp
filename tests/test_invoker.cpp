#include <gtest/gtest.h>

#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/grpc_service.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#ifdef CROUPIER_SDK_ENABLE_GRPC
#include "croupier/sdk/v1/invoker.grpc.pb.h"
#endif

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

// Test implementation of InvokerService for testing CroupierInvoker
class TestInvokerServiceImpl final : public croupier::sdk::v1::InvokerService::Service {
 public:
  explicit TestInvokerServiceImpl(std::map<std::string, FunctionHandler> handlers)
      : handlers_(std::move(handlers)) {
    std::cout << "🎯 Local function service initialized, handler count: " << handlers_.size() << '\n';
  }

  void UpdateHandlers(const std::map<std::string, FunctionHandler>& handlers) {
    std::lock_guard<std::mutex> lock(mutex_);
    handlers_ = handlers;
  }

  grpc::Status Invoke(grpc::ServerContext* context,
                      const croupier::sdk::v1::InvokeRequest* request,
                      croupier::sdk::v1::InvokeResponse* response) override {
    (void)context;
    const std::string& function_id = request->function_id();

    std::lock_guard<std::mutex> lock(mutex_);
    auto it = handlers_.find(function_id);
    if (it == handlers_.end()) {
      return grpc::Status(grpc::StatusCode::NOT_FOUND,
                          "Function not found: " + function_id);
    }

    try {
      // Serialize metadata to JSON context
      std::string ctx = "{";
      bool first = true;
      for (const auto& kv : request->metadata()) {
        if (!first) ctx += ",";
        ctx += "\"" + kv.first + "\":\"" + kv.second + "\"";
        first = false;
      }
      ctx += "}";

      std::string payload(request->payload().begin(), request->payload().end());
      std::string result = it->second(ctx, payload);
      response->set_payload(result);
      return grpc::Status::OK;
    } catch (const std::exception& e) {
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }
  }

  grpc::Status StartJob(grpc::ServerContext* context,
                        const croupier::sdk::v1::InvokeRequest* request,
                        croupier::sdk::v1::StartJobResponse* response) override {
    (void)context;
    const std::string& function_id = request->function_id();
    std::cout << "Starting job for function: " << function_id << '\n';

    FunctionHandler handler;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = handlers_.find(function_id);
      if (it == handlers_.end()) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND,
                            "Function not found: " + function_id);
      }
      handler = it->second;
    }

    // Generate job ID
    std::string job_id = "job-" + function_id + "-" + std::to_string(++job_counter_);
    response->set_job_id(job_id);

    // Start job in background thread
    std::string payload(request->payload().begin(), request->payload().end());
    std::string ctx = "{}";

    auto state = std::make_shared<JobState>();
    {
      std::lock_guard<std::mutex> lock(mutex_);
      jobs_[job_id] = state;
    }

    std::thread([job_id, handler, ctx, payload, state]() {
      // Send started event
      {
        std::lock_guard<std::mutex> lock(state->mutex);
        croupier::sdk::v1::JobEvent started;
        started.set_type("started");
        started.set_message("Job started");
        state->events.push_back(started);
        state->cv.notify_all();
      }

      try {
        std::string result = handler(ctx, payload);

        std::lock_guard<std::mutex> lock(state->mutex);
        if (!state->cancelled) {
          croupier::sdk::v1::JobEvent completed;
          completed.set_type("completed");
          completed.set_message("Job completed");
          completed.set_payload(result);
          state->events.push_back(completed);
          state->done = true;
        }
        state->cv.notify_all();
      } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(state->mutex);
        croupier::sdk::v1::JobEvent error;
        error.set_type("error");
        error.set_message(e.what());
        state->events.push_back(error);
        state->done = true;
        state->cv.notify_all();
      }
    }).detach();

    return grpc::Status::OK;
  }

  grpc::Status StreamJob(grpc::ServerContext* context,
                         const croupier::sdk::v1::JobStreamRequest* request,
                         grpc::ServerWriter<croupier::sdk::v1::JobEvent>* writer) override {
    const std::string& job_id = request->job_id();

    std::shared_ptr<JobState> state;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = jobs_.find(job_id);
      if (it == jobs_.end()) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Job not found: " + job_id);
      }
      state = it->second;
    }

    size_t sent = 0;
    while (!context->IsCancelled()) {
      std::unique_lock<std::mutex> lock(state->mutex);
      state->cv.wait_for(lock, std::chrono::milliseconds(100), [&]() {
        return sent < state->events.size() || state->done;
      });

      while (sent < state->events.size()) {
        writer->Write(state->events[sent]);
        ++sent;
      }

      if (state->done) {
        break;
      }
    }

    return grpc::Status::OK;
  }

  grpc::Status CancelJob(grpc::ServerContext* context,
                         const croupier::sdk::v1::CancelJobRequest* request,
                         croupier::sdk::v1::StartJobResponse* response) override {
    (void)context;
    const std::string& job_id = request->job_id();
    response->set_job_id(job_id);

    std::lock_guard<std::mutex> lock(mutex_);
    auto it = jobs_.find(job_id);
    if (it == jobs_.end()) {
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "Job not found: " + job_id);
    }

    auto& state = it->second;
    {
      std::lock_guard<std::mutex> state_lock(state->mutex);
      if (!state->done) {
        state->cancelled = true;
        croupier::sdk::v1::JobEvent cancelled;
        cancelled.set_type("cancelled");
        cancelled.set_message("Job cancelled");
        state->events.push_back(cancelled);
        state->done = true;
      }
      state->cv.notify_all();
    }

    return grpc::Status::OK;
  }

 private:
  struct JobState {
    std::mutex mutex;
    std::condition_variable cv;
    std::vector<croupier::sdk::v1::JobEvent> events;
    bool done = false;
    bool cancelled = false;
  };

  std::map<std::string, FunctionHandler> handlers_;
  std::mutex mutex_;
  std::atomic<uint64_t> job_counter_{0};
  std::map<std::string, std::shared_ptr<JobState>> jobs_;
};

class InProcessFunctionServer {
 public:
  InProcessFunctionServer(std::map<std::string, FunctionHandler> handlers)
      : service_(std::make_unique<TestInvokerServiceImpl>(std::move(handlers))) {}

  void Start() {
    grpc::ServerBuilder builder;
    int port = 0;
    builder.AddListeningPort("127.0.0.1:0", grpc::InsecureServerCredentials(), &port);
    builder.RegisterService(service_.get());
    server_ = builder.BuildAndStart();
    ASSERT_TRUE(server_);
    ASSERT_GT(port, 0);
    address_ = "127.0.0.1:" + std::to_string(port);
    std::cout << "[INFO] [croupier] Connecting to server/agent at: " << address_ << '\n';
    std::cout << "[INFO] [croupier] Connected to: " << address_ << '\n';
  }

  void Stop() {
    if (server_) {
      server_->Shutdown();
      server_.reset();
    }
  }

  const std::string& address() const { return address_; }

 private:
  std::unique_ptr<TestInvokerServiceImpl> service_;
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

