# 客户端配置详解

`ClientConfig` 结构定义了 Croupier 客户端的所有配置选项。

## 完整结构

```cpp
struct ClientConfig {
    // 连接配置
    std::string agent_addr = "127.0.0.1:19090";
    std::string game_id;
    std::string env = "development";
    std::string service_id = "cpp-service";

    // 超时
    int timeout_seconds = 30;

    // TLS
    bool insecure = true;
    struct Security {
        std::string cert_file;
        std::string key_file;
        std::string ca_file;
        std::string server_name;
    } security;

    // 重连
    bool auto_reconnect = true;
    int reconnect_interval_seconds = 5;
    int reconnect_max_attempts = 0;

    // 认证
    struct Auth {
        std::string token;
        std::map<std::string, std::string> headers;
    } auth;
};
```

## 字段详解

### agent_addr

Agent 服务器地址，格式 `host:port`。

```cpp
config.agent_addr = "127.0.0.1:19090";      // 本地
config.agent_addr = "agent.internal:19090";  // 内部域名
config.agent_addr = "10.0.0.5:19090";         // IP 地址
```

### game_id

游戏/项目唯一标识符。

```cpp
config.game_id = "my-mmorpg";
config.game_id = "production-game-2024";
```

### env

部署环境标识。

```cpp
config.env = "development";  // 开发
config.env = "staging";      // 预发布
config.env = "production";   // 生产
```

### service_id

服务实例标识符。

```cpp
config.service_id = "game-server-01";
config.service_id = "backend-" + GetHostname();
```

### timeout_seconds

网络操作超时时间（秒）。

```cpp
config.timeout_seconds = 30;   // 默认
config.timeout_seconds = 60;   // 长操作
config.timeout_seconds = 300;  // 非常长的操作
```

### insecure

是否跳过 TLS 验证。

```cpp
config.insecure = true;   // 开发环境
config.insecure = false;  // 生产环境（必须）
```

### security (结构体)

TLS 安全配置。

| 字段 | 说明 |
|------|------|
| `cert_file` | 客户端证书路径 |
| `key_file` | 客户端私钥路径 |
| `ca_file` | CA 证书路径 |
| `server_name` | TLS 服务器名称（SNI） |

```cpp
config.security.cert_file = "/etc/tls/client.crt";
config.security.key_file = "/etc/tls/client.key";
config.security.ca_file = "/etc/tls/ca.crt";
config.security.server_name = "croupier.internal";
```

### auto_reconnect

是否自动重连。

```cpp
config.auto_reconnect = true;   // 断线自动重连
config.auto_reconnect = false;  // 断线退出
```

### reconnect_interval_seconds

重连间隔（秒）。

```cpp
config.reconnect_interval_seconds = 5;   // 每 5 秒
config.reconnect_interval_seconds = 30;  // 每 30 秒
```

### reconnect_max_attempts

最大重连次数（0 = 无限）。

```cpp
config.reconnect_max_attempts = 0;    // 无限重试
config.reconnect_max_attempts = 10;   // 最多 10 次
```

### auth (结构体)

认证配置。

| 字段 | 说明 |
|------|------|
| `token` | JWT 令牌 |
| `headers` | 额外 HTTP 头部 |

```cpp
config.auth.token = "Bearer eyJhbGciOiJIUzI1NiIs...";
config.auth.headers = {
    {"X-Game-Version", "0.1.0"},
    {"X-Service-Region", "us-west-2"}
};
```

## 配置示例

### 最小配置

```json
{
  "game_id": "my-game",
  "agent_addr": "127.0.0.1:19090"
}
```

### 开发环境

```json
{
  "game_id": "dev-game",
  "env": "development",
  "agent_addr": "127.0.0.1:19090",
  "insecure": true,
  "timeout_seconds": 30
}
```

### 生产环境

```json
{
  "game_id": "prod-game",
  "env": "production",
  "service_id": "game-server-01",
  "agent_addr": "croupier-agent.internal:19090",
  "insecure": false,
  "timeout_seconds": 60,
  "security": {
    "cert_file": "/etc/tls/client.crt",
    "key_file": "/etc/tls/client.key",
    "ca_file": "/etc/tls/ca.crt",
    "server_name": "croupier.internal"
  },
  "auth": {
    "token": "Bearer ${JWT_TOKEN}",
    "headers": {
      "X-Game-Version": "0.1.0",
      "X-Service-Region": "us-west-2"
    }
  },
  "auto_reconnect": true,
  "reconnect_interval_seconds": 10,
  "reconnect_max_attempts": 0
}
```

## 默认值

| 字段 | 默认值 |
|------|--------|
| `agent_addr` | `127.0.0.1:19090` |
| `env` | `development` |
| `service_id` | `cpp-service` |
| `timeout_seconds` | `30` |
| `insecure` | `true` |
| `auto_reconnect` | `true` |
| `reconnect_interval_seconds` | `5` |
| `reconnect_max_attempts` | `0` |
| `security.cert_file` | 空 |
| `security.key_file` | 空 |
| `security.ca_file` | 空 |
| `security.server_name` | 空 |
| `auth.token` | 空 |
| `auth.headers` | 空 |
