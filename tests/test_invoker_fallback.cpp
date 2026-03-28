#include <gtest/gtest.h>

#include "croupier/sdk/croupier_client.h"

using namespace croupier::sdk;

namespace {

InvokerConfig MakeConfig() {
    InvokerConfig config;
    config.address = "127.0.0.1:19090";
    config.game_id = "test-game";
    config.env = "testing";
    config.disable_logging = true;
    return config;
}

}  // namespace

TEST(InvokerFallbackTest, ConnectUsesFallbackBehaviorWithoutNNG) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_NNG
    SUCCEED();
#else
    EXPECT_TRUE(invoker.Connect());
#endif
}

TEST(InvokerFallbackTest, InvokeUsesFallbackBehaviorWithoutNNG) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_NNG
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    const std::string response = invoker.Invoke("player.echo", R"({"ok":true})");
    EXPECT_NE(response.find("\"status\":\"success\""), std::string::npos);
    EXPECT_NE(response.find("\"function_id\":\"player.echo\""), std::string::npos);
#endif
}

TEST(InvokerFallbackTest, StartJobUsesFallbackBehaviorWithoutNNG) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_NNG
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    EXPECT_FALSE(invoker.StartJob("player.batch", "{}").empty());
#endif
}

TEST(InvokerFallbackTest, StreamJobUsesFallbackBehaviorWithoutNNG) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_NNG
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    const std::string job_id = invoker.StartJob("player.batch", "{}");
    auto future = invoker.StreamJob(job_id);
    auto events = future.get();

    ASSERT_GE(events.size(), 2U);
    EXPECT_EQ(events.front().event_type, "started");
    EXPECT_TRUE(events.back().done);
#endif
}

TEST(InvokerFallbackTest, CancelJobUsesFallbackBehaviorWithoutNNG) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_NNG
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    const std::string job_id = invoker.StartJob("player.batch", "{}");
    EXPECT_TRUE(invoker.CancelJob(job_id));
#endif
}
