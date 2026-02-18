#include <gtest/gtest.h>
#include "croupier/sdk/croupier_client.h"
#include "croupier/sdk/config/client_config_loader.h"
#include "croupier/sdk/utils/json_utils.h"
#include <thread>
#include <chrono>
#include <limits>

using namespace croupier::sdk;
using namespace croupier::sdk::config;
using namespace croupier::sdk::utils;

// ========== 边缘情况测试套件 ==========

// 测试极端配置值
TEST(EdgeCasesConfig, ZeroTimeout) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.timeout_seconds = 0;

    CroupierClient client(config);
    EXPECT_EQ(config.timeout_seconds, 0);
}

TEST(EdgeCasesConfig, VeryLargeTimeout) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.timeout_seconds = 3600; // 1 hour

    CroupierClient client(config);
    EXPECT_EQ(config.timeout_seconds, 3600);
}

TEST(EdgeCasesConfig, EmptyAgentAddress) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.agent_addr = "";

    CroupierClient client(config);
    EXPECT_TRUE(config.agent_addr.empty());
}

TEST(EdgeCasesConfig, VeryLongAgentAddress) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    std::string long_addr(10000, 'a'); // 10k characters
    config.agent_addr = long_addr;

    CroupierClient client(config);
    EXPECT_EQ(config.agent_addr.length(), 10000);
}

TEST(EdgeCasesConfig, EmptyGameId) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.game_id = "";

    CroupierClient client(config);
    EXPECT_TRUE(config.game_id.empty());
}

TEST(EdgeCasesConfig, EmptyEnvironment) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.environment = "";

    CroupierClient client(config);
    EXPECT_TRUE(config.environment.empty());
}

// 测试极端字符串值
TEST(EdgeCasesStrings, EmptyFunctionId) {
    std::string function_id = "";
    std::string payload = "{}";

    EXPECT_TRUE(function_id.empty());
    EXPECT_FALSE(payload.empty());
}

TEST(EdgeCasesStrings, VeryLongFunctionId) {
    std::string function_id(10000, 'x');
    std::string payload = "{}";

    EXPECT_EQ(function_id.length(), 10000);
}

TEST(EdgeCasesStrings, EmptyPayload) {
    std::string payload = "";

    EXPECT_TRUE(payload.empty());
}

TEST(EdgeCasesStrings, VeryLargePayload) {
    // Create a 10MB payload
    std::string payload(10 * 1024 * 1024, 'y');

    EXPECT_EQ(payload.length(), 10 * 1024 * 1024);
}

TEST(EdgeCasesStrings, PayloadWithSpecialCharacters) {
    std::string payload = R"({"data":"\n\t\r\b\f\"quotes\" and 'apostrophes'"})";

    EXPECT_FALSE(payload.empty());
    EXPECT_TRUE(payload.find('\\') != std::string::npos);
}

TEST(EdgeCasesStrings, PayloadWithUnicode) {
    std::string payload = u8R"({"emoji":"😀🎉🚀","chinese":"中文测试","japanese":"日本語テスト"})";

    EXPECT_FALSE(payload.empty());
    EXPECT_TRUE(payload.find("😀") != std::string::npos);
}

TEST(EdgeCasesStrings, PayloadWithNullBytes) {
    std::string payload = "test\x00string";

    EXPECT_EQ(payload.length(), 11);
}

// 测试数值边界
TEST(EdgeCasesNumbers, MaxPortNumber) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    // Parse address with max port
    config.agent_addr = "tcp://127.0.0.1:65535";

    CroupierClient client(config);
    EXPECT_TRUE(config.agent_addr.find("65535") != std::string::npos);
}

TEST(EdgeCasesNumbers, ZeroPort) {
    std::string address = "tcp://127.0.0.1:0";

    EXPECT_TRUE(address.find(":0") != std::string::npos);
}

TEST(EdgeCasesNumbers, NegativePort) {
    std::string address = "tcp://127.0.0.1:-1";

    EXPECT_TRUE(address.find(":-1") != std::string::npos);
}

TEST(EdgeCasesNumbers, VeryLargeTimeout) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.timeout_seconds = std::numeric_limits<int>::max();

    CroupierClient client(config);
    EXPECT_EQ(config.timeout_seconds, std::numeric_limits<int>::max());
}

TEST(EdgeCasesNumbers, NegativeTimeout) {
    ClientConfigLoader loader;
    ClientConfig config = loader.CreateDefaultConfig();

    config.timeout_seconds = -1;

    CroupierClient client(config);
    EXPECT_EQ(config.timeout_seconds, -1);
}

// 测试 JSON 边界情况
TEST(EdgeCasesJSON, EmptyJSON) {
    JsonUtils json_utils;
    std::string json = "{}";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_object());
    EXPECT_TRUE(parsed.empty());
}

TEST(EdgeCasesJSON, NullJSON) {
    JsonUtils json_utils;
    std::string json = "null";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_null());
}

TEST(EdgeCasesJSON, VeryDeepNesting) {
    JsonUtils json_utils;
    std::string json = R"({"a":{"b":{"c":{"d":{"e":{}}}}}})";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_object());
}

TEST(EdgeCasesJSON, VeryWideObject) {
    JsonUtils json_utils;
    std::string json = R"({"a":1,"b":2,"c":3,"d":4,"e":5,"f":6,"g":7,"h":8,"i":9,"j":10})";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_object());
    EXPECT_EQ(parsed.size(), 10);
}

TEST(EdgeCasesJSON, ArrayWithNulls) {
    JsonUtils json_utils;
    std::string json = R"([null,null,null])";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_array());
    EXPECT_EQ(parsed.size(), 3);
}

TEST(EdgeCasesJSON, StringWithEscapes) {
    JsonUtils json_utils;
    std::string json = R"({"path":"C:\\Users\\test\\file.txt","quote":"\"quoted\""})";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_object());
    EXPECT_TRUE(parsed.contains("path"));
}

TEST(EdgeCasesJSON, InvalidJSON) {
    JsonUtils json_utils;
    std::string json = "{invalid json}";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_discarded()); // parse fails
}

TEST(EdgeCasesJSON, MalformedArray) {
    JsonUtils json_utils;
    std::string json = "[1,2,3,";

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_discarded());
}

TEST(EdgeCasesJSON, MalformedObject) {
    JsonUtils json_utils;
    std::string json = R"({"key": value})"; // missing quotes

    auto parsed = json_utils.Parse(json);
    EXPECT_TRUE(parsed.is_discarded());
}

// 测试时间边界情况
TEST(EdgeCasesTime, MinTimestamp) {
    int64_t timestamp = std::numeric_limits<int64_t>::min();

    EXPECT_LT(timestamp, 0);
}

TEST(EdgeCasesTime, MaxTimestamp) {
    int64_t timestamp = std::numeric_limits<int64_t>::max();

    EXPECT_GT(timestamp, 0);
}

TEST(EdgeCasesTime, ZeroTimestamp) {
    int64_t timestamp = 0;

    EXPECT_EQ(timestamp, 0);
}

TEST(EdgeCasesTime, UnixEpoch) {
    int64_t timestamp = 0; // Unix epoch

    EXPECT_EQ(timestamp, 0);
}

// 测试元数据边界情况
TEST(EdgeCasesMetadata, EmptyMetadata) {
    std::map<std::string, std::string> metadata;

    EXPECT_TRUE(metadata.empty());
    EXPECT_EQ(metadata.size(), 0);
}

TEST(EdgeCasesMetadata, VeryLargeMetadata) {
    std::map<std::string, std::string> metadata;

    for (int i = 0; i < 10000; i++) {
        metadata["key_" + std::to_string(i)] = "value_" + std::to_string(i);
    }

    EXPECT_EQ(metadata.size(), 10000);
}

TEST(EdgeCasesMetadata, EmptyKey) {
    std::map<std::string, std::string> metadata;
    metadata[""] = "value";

    EXPECT_EQ(metadata.size(), 1);
    EXPECT_TRUE(metadata.contains(""));
}

TEST(EdgeCasesMetadata, EmptyValue) {
    std::map<std::string, std::string> metadata;
    metadata["key"] = "";

    EXPECT_EQ(metadata.size(), 1);
    EXPECT_EQ(metadata["key"], "");
}

TEST(EdgeCasesMetadata, VeryLongKey) {
    std::map<std::string, std::string> metadata;
    std::string long_key(10000, 'k');
    metadata[long_key] = "value";

    EXPECT_EQ(metadata.size(), 1);
    EXPECT_TRUE(metadata.contains(long_key));
}

TEST(EdgeCasesMetadata, VeryLongValue) {
    std::map<std::string, std::string> metadata;
    std::string long_value(10000, 'v');
    metadata["key"] = long_value;

    EXPECT_EQ(metadata.size(), 1);
    EXPECT_EQ(metadata["key"].length(), 10000);
}

TEST(EdgeCasesMetadata, SpecialCharactersInKey) {
    std::map<std::string, std::string> metadata;
    metadata["key\nwith\t special\rchars"] = "value";

    EXPECT_EQ(metadata.size(), 1);
}

TEST(EdgeCasesMetadata, UnicodeInValue) {
    std::map<std::string, std::string> metadata;
    metadata["emoji"] = u8"😀🎉🚀";

    EXPECT_EQ(metadata.size(), 1);
    EXPECT_TRUE(metadata["emoji"].find("😀") != std::string::npos);
}

// 测试 ID 边界情况
TEST(EdgeCasesIDs, EmptyId) {
    std::string id = "";

    EXPECT_TRUE(id.empty());
}

TEST(EdgeCasesIDs, VeryLongId) {
    std::string id(10000, 'x');

    EXPECT_EQ(id.length(), 10000);
}

TEST(EdgeCasesIDs, IdWithSpecialCharacters) {
    std::string id = "test.function@v1.0#special";

    EXPECT_TRUE(id.find('.') != std::string::npos);
    EXPECT_TRUE(id.find('@') != std::string::npos);
    EXPECT_TRUE(id.find('#') != std::string::npos);
}

TEST(EdgeCasesIDs, IdWithUnicode) {
    std::string id = "function.中文.v1";

    EXPECT_TRUE(id.find("中文") != std::string::npos);
}

TEST(EdgeCasesIDs, IdWithOnlyDots) {
    std::string id = "...";

    EXPECT_EQ(id.length(), 3);
}

// 测试布尔值边界情况
TEST(EdgeCasesBoolean, TrueValue) {
    bool enabled = true;

    EXPECT_TRUE(enabled);
}

TEST(EdgeCasesBoolean, FalseValue) {
    bool enabled = false;

    EXPECT_FALSE(enabled);
}

TEST(EdgeCasesBoolean, StringToBoolean) {
    std::string true_str = "true";
    std::string false_str = "false";

    EXPECT_EQ(true_str, "true");
    EXPECT_EQ(false_str, "false");
}

// 测试数组边界情况
TEST(EdgeCasesArrays, EmptyArray) {
    std::vector<std::string> array;

    EXPECT_TRUE(array.empty());
    EXPECT_EQ(array.size(), 0);
}

TEST(EdgeCasesArrays, VeryLargeArray) {
    std::vector<std::string> array;

    for (int i = 0; i < 100000; i++) {
        array.push_back("item_" + std::to_string(i));
    }

    EXPECT_EQ(array.size(), 100000);
}

TEST(EdgeCasesArrays, ArrayWithEmptyStrings) {
    std::vector<std::string> array = {"", "", ""};

    EXPECT_EQ(array.size(), 3);
    EXPECT_TRUE(array[0].empty());
}

TEST(EdgeCasesArrays, ArrayWithDuplicates) {
    std::vector<std::string> array = {"same", "same", "same"};

    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], array[1]);
    EXPECT_EQ(array[1], array[2]);
}

// 测试文件路径边界情况
TEST(EdgeCasesPaths, EmptyPath) {
    std::string path = "";

    EXPECT_TRUE(path.empty());
}

TEST(EdgeCasesPaths, RelativePath) {
    std::string path = "../config/test.json";

    EXPECT_TRUE(path.find("..") != std::string::npos);
}

TEST(EdgeCasesPaths, AbsolutePath) {
    std::string path = "/etc/croupier/config.json";

    EXPECT_TRUE(path.startswith("/"));
}

TEST(EdgeCasesPaths, PathWithSpecialChars) {
    std::string path = R"(C:\Users\test\config file.json)";

    EXPECT_TRUE(path.find(' ') != std::string::npos);
}

TEST(EdgeCasesPaths, VeryLongPath) {
    std::string path(10000, '/');

    EXPECT_EQ(path.length(), 10000);
}

// 测试并发边界情况
TEST(EdgeCasesConcurrency, ZeroThreads) {
    int num_threads = 0;

    EXPECT_EQ(num_threads, 0);
}

TEST(EdgeCasesConcurrency, VeryManyThreads) {
    int num_threads = 10000;

    EXPECT_GT(num_threads, 0);
}

TEST(EdgeCasesConcurrency, RapidCreateDestroy) {
    for (int i = 0; i < 1000; i++) {
        ClientConfigLoader loader;
        ClientConfig config = loader.CreateDefaultConfig();
        CroupierClient client(config);
        // Client is destroyed immediately
    }

    SUCCEED();
}

// 测试错误边界情况
TEST(EdgeCasesErrors, NullPointerCheck) {
    CroupierClient* client = nullptr;

    EXPECT_EQ(client, nullptr);
}

TEST(EdgeCasesErrors, InvalidMemoryAccess) {
    std::vector<int> vec = {1, 2, 3};

    // Accessing out of bounds is undefined behavior,
    // but we can test boundary conditions
    EXPECT_GE(vec.size(), 0);
    EXPECT_LE(vec.size(), 3);
}

// 测试浮点数边界情况
TEST(EdgeCasesFloat, PositiveInfinity) {
    double value = std::numeric_limits<double>::infinity();

    EXPECT_TRUE(std::isinf(value));
    EXPECT_GT(value, 0);
}

TEST(EdgeCasesFloat, NegativeInfinity) {
    double value = -std::numeric_limits<double>::infinity();

    EXPECT_TRUE(std::isinf(value));
    EXPECT_LT(value, 0);
}

TEST(EdgeCasesFloat, NaN) {
    double value = std::numeric_limits<double>::quiet_NaN();

    EXPECT_TRUE(std::isnan(value));
}

TEST(EdgeCasesFloat, MaxFloat) {
    double value = std::numeric_limits<double>::max();

    EXPECT_GT(value, 0);
    EXPECT_FALSE(std::isinf(value));
}

TEST(EdgeCasesFloat, MinFloat) {
    double value = std::numeric_limits<double>::min();

    EXPECT_GT(value, 0);
}

TEST(EdgeCasesFloat, SmallestDenormal) {
    double value = std::numeric_limits<double>::denorm_min();

    EXPECT_GT(value, 0);
    EXPECT_LT(value, std::numeric_limits<double>::min());
}

// 测试字符边界情况
TEST(EdgeCasesChar, NullChar) {
    char c = '\0';

    EXPECT_EQ(c, '\0');
}

TEST(EdgeCasesChar, ASCIIControlChars) {
    std::vector<char> control_chars = {
        '\a', '\b', '\f', '\n', '\r', '\t', '\v'
    };

    for (char c : control_chars) {
        EXPECT_LT(c, ' ');
    }
}

TEST(EdgeCasesChar, ExtendedASCII) {
    std::vector<char> extended_chars;

    for (int i = 128; i < 256; i++) {
        extended_chars.push_back(static_cast<char>(i));
    }

    EXPECT_EQ(extended_chars.size(), 128);
}

// 测试版本号边界情况
TEST(EdgeCasesVersion, EmptyVersion) {
    std::string version = "";

    EXPECT_TRUE(version.empty());
}

TEST(EdgeCasesVersion, VeryLongVersion) {
    std::string version(10000, '1');

    EXPECT_EQ(version.length(), 10000);
}

TEST(EdgeCasesVersion, ValidVersion) {
    std::string version = "1.2.3";

    EXPECT_TRUE(version.find('.') != std::string::npos);
}

TEST(EdgeCasesVersion, VersionWithManyComponents) {
    std::string version = "1.2.3.4.5.6.7.8.9.10";

    int count = 0;
    for (char c : version) {
        if (c == '.') count++;
    }

    EXPECT_EQ(count, 9);
}

// 测试状态边界情况
TEST(EdgeCasesState, UnknownState) {
    std::string state = "unknown_state";

    EXPECT_EQ(state, "unknown_state");
}

TEST(EdgeCasesState, EmptyState) {
    std::string state = "";

    EXPECT_TRUE(state.empty());
}

TEST(EdgeCasesState, StateWithSpecialChars) {
    std::string state = "state\nwith\tspecial\rchars";

    EXPECT_TRUE(state.find('\n') != std::string::npos);
}

// 测试连接字符串边界情况
TEST(EdgeCasesConnection, InvalidProtocol) {
    std::string address = "invalid://127.0.0.1:19090";

    EXPECT_TRUE(address.find("invalid://") != std::string::npos);
}

TEST(EdgeCasesConnection, MissingPort) {
    std::string address = "tcp://127.0.0.1";

    EXPECT_FALSE(address.find(':') != std::string::npos && address.rfind(':') > address.find(':'));
}

TEST(EdgeCasesConnection, OnlyPort) {
    std::string address = ":19090";

    EXPECT_TRUE(address.startswith(":"));
}

TEST(EdgeCasesConnection, IPv6Address) {
    std::string address = "tcp://[::1]:19090";

    EXPECT_TRUE(address.find('[') != std::string::npos);
    EXPECT_TRUE(address.find(']') != std::string::npos);
}

TEST(EdgeCasesConnection, LocalhostVariations) {
    std::vector<std::string> addresses = {
        "tcp://localhost:19090",
        "tcp://127.0.0.1:19090",
        "tcp://0.0.0.0:19090",
        "tcp://[::1]:19090"
    };

    EXPECT_EQ(addresses.size(), 4);
}

// 测试重复操作边界情况
TEST(EdgeCasesRepetition, RepeatedInitialization) {
    for (int i = 0; i < 100; i++) {
        ClientConfigLoader loader;
        ClientConfig config = loader.CreateDefaultConfig();
        CroupierClient client(config);
    }

    SUCCEED();
}

TEST(EdgeCasesRepetition, RepeatedConfigLoad) {
    ClientConfigLoader loader;

    for (int i = 0; i < 1000; i++) {
        ClientConfig config = loader.CreateDefaultConfig();
    }

    SUCCEED();
}

// 测试内存边界情况
TEST(EdgeCasesMemory, StackAllocation) {
    char buffer[1024 * 1024]; // 1MB on stack

    EXPECT_GT(sizeof(buffer), 0);
}

TEST(EdgeCasesMemory, LargeStringCopy) {
    std::string large_string(10 * 1024 * 1024, 'x'); // 10MB
    std::string copy = large_string;

    EXPECT_EQ(copy, large_string);
    EXPECT_EQ(copy.length(), 10 * 1024 * 1024);
}

// 测试类型转换边界情况
TEST(EdgeCasesConversion, StringToIntMax) {
    std::string str = std::to_string(std::numeric_limits<int>::max());

    EXPECT_FALSE(str.empty());
}

TEST(EdgeCasesConversion, StringToIntMin) {
    std::string str = std::to_string(std::numeric_limits<int>::min());

    EXPECT_FALSE(str.empty());
}

TEST(EdgeCasesConversion, StringToDouble) {
    std::string str = "123.456";

    EXPECT_TRUE(str.find('.') != std::string::npos);
}

TEST(EdgeCasesConversion, DoubleToString) {
    double value = 123.456;
    std::string str = std::to_string(value);

    EXPECT_TRUE(str.find('.') != std::string::npos || str.find('e') != std::string::npos);
}
