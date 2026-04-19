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

TEST(InvokerFallbackTest, ConnectUsesFallbackBehaviorWithoutTCP) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_TCP
    SUCCEED();
#else
    EXPECT_TRUE(invoker.Connect());
#endif
}

TEST(InvokerFallbackTest, InvokeUsesFallbackBehaviorWithoutTCP) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_TCP
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    const std::string response = invoker.Invoke("player.echo", R"({"ok":true})");
    EXPECT_NE(response.find("\"status\":\"success\""), std::string::npos);
    EXPECT_NE(response.find("\"function_id\":\"player.echo\""), std::string::npos);
#endif
}

TEST(InvokerFallbackTest, StartJobUsesFallbackBehaviorWithoutTCP) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_TCP
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    EXPECT_FALSE(invoker.StartJob("player.batch", "{}").empty());
#endif
}

TEST(InvokerFallbackTest, StreamJobUsesFallbackBehaviorWithoutTCP) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_TCP
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

TEST(InvokerFallbackTest, CancelJobUsesFallbackBehaviorWithoutTCP) {
    CroupierInvoker invoker(MakeConfig());

#ifdef CROUPIER_SDK_HAS_TCP
    SUCCEED();
#else
    ASSERT_TRUE(invoker.Connect());
    const std::string job_id = invoker.StartJob("player.batch", "{}");
    EXPECT_TRUE(invoker.CancelJob(job_id));
#endif
}
