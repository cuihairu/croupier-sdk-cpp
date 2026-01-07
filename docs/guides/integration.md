# Croupier C++ SDK 集成指南

本指南提供完整的 Croupier C++ SDK 集成步骤，帮助开发者快速接入游戏后端平台。

## 目录

- [快速开始](#快速开始)
- [核心概念](#核心概念)
- [完整接口参考](#完整接口参考)
- [配置说明](#配置说明)
- [生产部署](#生产部署)
- [故障排查](#故障排查)

---

## 快速开始

### 1. 安装依赖

**系统要求：**
- 64位操作系统 (Windows x64 / Linux x64 / macOS x64 or ARM64)
- C++17 编译器（GCC 8+, Clang 10+, MSVC 2019+）
- CMake 3.20+
- vcpkg（推荐）

**Linux/macOS:**
```bash
# 安装构建工具
sudo apt-get install build-essential cmake ninja-build  # Linux
brew install cmake ninja                                 # macOS

# 克隆仓库
git clone https://github.com/cuihairu/croupier-sdk-cpp.git
cd croupier-sdk-cpp

# 配置构建
cmake -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=./cmake/vcpkg-bootstrap.cmake \
  -DVCPKG_OVERLAY_PORTS=./vcpkg-overlays \
  -DVCPKG_OVERLAY_TRIPLETS=./vcpkg-overlays/triplets

# 构建
cmake --build build --parallel
```

**Windows:**
```powershell
# 克隆仓库
git clone https://github.com/cuihairu/croupier-sdk-cpp.git
cd croupier-sdk-cpp

# 配置构建 (使用 Visual Studio 2022)
cmake -B build -G "Visual Studio 17 2022" `
  -DCMAKE_TOOLCHAIN_FILE=./cmake/vcpkg-bootstrap.cmake `
  -DVCPKG_OVERLAY_PORTS=./vcpkg-overlays

# 构建
cmake --build build --config Release
```

### 2. 最小集成示例

```cpp
#include "croupier/sdk/croupier_client.h"
#include <iostream>

using namespace croupier::sdk;

// 定义函数处理器
std::string MyGameHandler(const std::string& context, const std::string& payload) {
    // 处理游戏逻辑
    return R"({"status":"success","data":"processed"})";
}

int main() {
    // 1. 配置客户端
    ClientConfig config;
    config.game_id = "my-game";
    config.env = "production";
    config.agent_addr = "agent.croupier.internal:19090";
    config.insecure = false;
    config.cert_file = "/etc/tls/client.crt";
    config.key_file = "/etc/tls/client.key";
    config.ca_file = "/etc/tls/ca.crt";

    // 2. 创建客户端
    CroupierClient client(config);

    // 3. 注册函数
    FunctionDescriptor desc;
    desc.id = "game.action";
    desc.version = "1.0.0";
    desc.category = "gameplay";
    desc.risk = "low";

    client.RegisterFunction(desc, MyGameHandler);

    // 4. 连接并启动服务
    if (!client.Connect()) {
        std::cerr << "连接失败\n";
        return 1;
    }

    client.Serve();  // 阻塞运行

    return 0;
}
```

---

## 核心概念

### 客户端 (Client)

客户端负责注册和管理游戏函数，接收来自 Agent 的调用请求。

```cpp
CroupierClient client(config);
```

### 调用器 (Invoker)

调用器用于主动调用远程函数（可选）。

```cpp
CroupierInvoker invoker(invoker_config);
std::string result = invoker.Invoke("remote.function", payload);
```

### 函数描述符 (FunctionDescriptor)

描述函数的元数据：

```cpp
struct FunctionDescriptor {
    std::string id;           // 函数唯一标识 (如 "player.ban")
    std::string version;      // 版本号 (如 "1.0.0")
    std::string category;     // 分类 (如 "gameplay", "inventory")
    std::string risk;         // 风险级别 ("low", "medium", "high")
    std::string entity;       // 关联实体 (如 "player", "item")
    std::string operation;    // 操作类型 ("create", "read", "update", "delete")
    bool enabled = true;      // 是否启用
};
```

### 虚拟对象 (VirtualObject)

将 CRUD 操作映射到函数：

```cpp
VirtualObjectDescriptor player;
player.id = "player";
player.operations = {
    {"create", "player.create"},
    {"read", "player.get"},
    {"update", "player.update"},
    {"delete", "player.delete"}
};
```

### 组件 (Component)

包含多个虚拟对象和函数的可分发单元：

```cpp
ComponentDescriptor component;
component.id = "economy-system";
component.entities.push_back(wallet_object);
component.functions.push_back(trade_function);
```

---

## 完整接口参考

### CroupierClient 接口

#### 注册相关

| 接口 | 说明 |
|------|------|
| `RegisterFunction(const FunctionDescriptor&, FunctionHandler)` | 注册单个函数 |
| `RegisterVirtualObject(const VirtualObjectDescriptor&, HandlerMap)` | 注册虚拟对象 |
| `RegisterComponent(const ComponentDescriptor&)` | 注册组件 |
| `LoadComponentFromFile(const std::string&)` | 从文件加载组件 |

#### 查询相关

| 接口 | 说明 |
|------|------|
| `GetRegisteredObjects()` | 获取已注册的虚拟对象列表 |
| `GetRegisteredComponents()` | 获取已注册的组件列表 |
| `GetLocalAddress()` | 获取本地服务地址 |

#### 取消注册

| 接口 | 说明 |
|------|------|
| `UnregisterVirtualObject(const std::string&)` | 取消注册虚拟对象 |
| `UnregisterComponent(const std::string&)` | 取消注册组件 |

#### 生命周期

| 接口 | 说明 |
|------|------|
| `Connect()` | 连接到 Agent |
| `Serve()` | 启动服务循环（阻塞） |
| `Stop()` | 停止服务 |
| `Close()` | 完全关闭客户端 |

### CroupierInvoker 接口

| 接口 | 说明 |
|------|------|
| `Connect()` | 连接到服务器 |
| `Invoke(function_id, payload, options)` | 同步调用 |
| `StartJob(function_id, payload, options)` | 启动异步作业 |
| `StreamJob(job_id)` | 流式获取作业事件 |
| `CancelJob(job_id)` | 取消作业 |
| `SetSchema(function_id, schema)` | 设置验证模式 |
| `Close()` | 关闭连接 |

---

## 配置说明

### ClientConfig 完整参数

```cpp
struct ClientConfig {
    // === 连接配置 ===
    std::string agent_addr = "127.0.0.1:19090";  // Agent 地址
    std::string local_listen = "127.0.0.1:0";    // 本地监听地址
    bool insecure = true;                         // 是否禁用 TLS

    // === 身份配置 ===
    std::string game_id;          // 游戏标识 (必填)
    std::string env = "development"; // 环境 (development/staging/production)
    std::string service_id = "cpp-service";
    std::string service_version = "1.0.0";

    // === TLS 配置 (insecure=false 时必填) ===
    std::string cert_file;   // 客户端证书
    std::string key_file;    // 客户端私钥
    std::string ca_file;     // CA 证书
    std::string server_name; // 服务器名称验证

    // === 认证配置 ===
    std::string auth_token;              // Bearer Token
    std::map<std::string, std::string> headers; // 自定义 HTTP 头

    // === 超时配置 ===
    int timeout_seconds = 30;

    // === 重连配置 ===
    bool auto_reconnect = true;
    int reconnect_interval_seconds = 5;
    int reconnect_max_attempts = 0;  // 0 = 无限重试
};
```

### 环境变量覆盖

可通过环境变量覆盖配置：

```bash
export CROUPIER_AUTO_RECONNECT=true
export CROUPIER_RECONNECT_INTERVAL_SECONDS=5
export CROUPIER_RECONNECT_MAX_ATTEMPTS=0
```

---

## 生产部署

### Docker 部署

创建 `Dockerfile`:

```dockerfile
FROM ubuntu:22.04

# 安装依赖
RUN apt-get update && apt-get install -y \
    ca-certificates \
    libgrpc++-dev \
    libprotobuf-dev \
    && rm -rf /var/lib/apt/lists/*

# 复制 SDK 文件
COPY lib/ /usr/local/lib/
COPY include/ /usr/local/include/croupier/

# 复制游戏服务
COPY build/game-server /app/game-server

# 设置 TLS 证书路径
ENV CROUPIER_CERT_FILE=/etc/tls/client.crt
ENV CROUPIER_KEY_FILE=/etc/tls/client.key
ENV CROUPIER_CA_FILE=/etc/tls/ca.crt

# 暴露健康检查端口
EXPOSE 8080

CMD ["/app/game-server"]
```

### Kubernetes 部署

创建 `deployment.yaml`:

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: croupier-game-server
spec:
  replicas: 3
  selector:
    matchLabels:
      app: game-server
  template:
    metadata:
      labels:
        app: game-server
    spec:
      containers:
      - name: game-server
        image: your-registry/croupier-game-server:latest
        ports:
        - containerPort: 8080
          name: health
        env:
        - name: CROUPIER_AGENT_ADDR
          value: "croupier-agent:19090"
        - name: CROUPIER_GAME_ID
          value: "my-game"
        - name: CROUPIER_ENV
          value: "production"
        volumeMounts:
        - name: tls-certs
          mountPath: /etc/tls
          readOnly: true
        livenessProbe:
          httpGet:
            path: /health
            port: 8080
          initialDelaySeconds: 10
          periodSeconds: 30
        readinessProbe:
          httpGet:
            path: /ready
            port: 8080
          initialDelaySeconds: 5
          periodSeconds: 10
      volumes:
      - name: tls-certs
        secret:
          secretName: croupier-tls
---
apiVersion: v1
kind: Service
metadata:
  name: croupier-game-server
spec:
  selector:
    app: game-server
  ports:
  - port: 80
    targetPort: 8080
```

### 健康检查端点

实现健康检查：

```cpp
#include <micro_httpd.hpp>

void startHealthCheckServer(int port) {
    httpd::server server(port);
    server["/health"] = [](auto& req, auto& res) {
        res = httpd::response(200, "OK");
    };
    server["/ready"] = [](auto& req, auto& res) {
        bool connected = client.IsConnected();
        res = httpd::response(connected ? 200 : 503, connected ? "Ready" : "Not Ready");
    };
    server.start();
}
```

---

## 故障排查

### 连接失败

**问题**: 无法连接到 Agent

```cpp
// 检查配置
std::cout << "Agent 地址: " << config.agent_addr << '\n';
std::cout << "TLS 设置: " << (config.insecure ? "禁用" : "启用") << '\n';

// 检查网络连通性
system(("ping -c 1 " + config.agent_addr.substr(0, config.agent_addr.find(':'))).c_str());
```

**解决方案**:
1. 确认 Agent 服务正在运行
2. 检查防火墙规则
3. 验证 TLS 证书路径

### 函数未被调用

**问题**: 函数已注册但从未收到调用

**检查清单**:
- [ ] 函数 ID 与 Agent 侧配置一致
- [ ] 函数版本匹配
- [ ] 函数已启用 (`enabled = true`)
- [ ] 客户端已调用 `Serve()`
- [ ] 网络连接正常

### 性能问题

**问题**: 响应延迟高

**优化建议**:
1. 使用 `'\n'` 而非 `std::endl` 避免频繁刷新缓冲区
2. 启用 gRPC 连接复用
3. 使用异步处理模式

```cpp
// 异步处理示例
std::string AsyncHandler(const std::string& context, const std::string& payload) {
    // 立即返回，异步处理
    std::thread([payload]() {
        processAsync(payload);
    }).detach();

    return R"({"status":"accepted","message":"Processing asynchronously"})";
}
```

---

## 更多资源

- [完整 API 文档](https://cuihairu.github.io/croupier-sdk-cpp/)
- [示例代码](../examples/)
- [架构设计](../README.md#架构设计)
- [问题反馈](https://github.com/cuihairu/croupier-sdk-cpp/issues)
