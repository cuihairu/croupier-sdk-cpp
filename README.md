<p align="center">
  <h1 align="center">Croupier C++ SDK</h1>
  <p align="center">
    <strong>高性能 C++ SDK，用于 Croupier 游戏函数注册与虚拟对象管理</strong>
  </p>
</p>

<p align="center">
  <a href="https://github.com/cuihairu/croupier-sdk-cpp/actions/workflows/ci.yml">
    <img src="https://github.com/cuihairu/croupier-sdk-cpp/actions/workflows/ci.yml/badge.svg" alt="CI">
  </a>
  <a href="https://codecov.io/gh/cuihairu/croupier-sdk-cpp">
    <img src="https://codecov.io/gh/cuihairu/croupier-sdk-cpp/branch/main/graph/badge.svg" alt="Coverage">
  </a>
  <a href="https://github.com/cuihairu/croupier-sdk-cpp/actions/workflows/nightly.yml">
    <img src="https://github.com/cuihairu/croupier-sdk-cpp/actions/workflows/nightly.yml/badge.svg" alt="Nightly Build">
  </a>
  <a href="https://github.com/cuihairu/croupier-sdk-cpp/releases">
    <img src="https://img.shields.io/github/v/release/cuihairu/croupier-sdk-cpp?include_prereleases" alt="Release">
  </a>
  <a href="https://www.apache.org/licenses/LICENSE-2.0">
    <img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg" alt="License">
  </a>
  <a href="https://en.cppreference.com/w/cpp/17">
    <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  </a>
</p>

<p align="center">
  <a href="#支持平台">
    <img src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg" alt="Platform">
  </a>
  <a href="https://github.com/cuihairu/croupier">
    <img src="https://img.shields.io/badge/Main%20Project-Croupier-green.svg" alt="Main Project">
  </a>
</p>

---

## 📋 目录

- [简介](#简介)
- [主项目](#主项目)
- [其他语言 SDK](#其他语言-sdk)
- [支持平台](#支持平台)
- [核心特性](#核心特性)
- [快速开始](#快速开始)
- [使用示例](#使用示例)
- [架构设计](#架构设计)
- [API 参考](#api-参考)
- [部署与分发](#部署与分发)
- [开发指南](#开发指南)
- [贡献指南](#贡献指南)
- [许可证](#许可证)

---

## 简介

Croupier C++ SDK 是 [Croupier](https://github.com/cuihairu/croupier) 游戏后端平台的官方 C++ 客户端实现。它提供了高性能的虚拟对象注册、gRPC 通信和多平台构建支持，采用 **ID 引用模式** 解决对象参数传递性能问题，通过 **四层组件化架构** 实现优雅的函数和对象管理。

## 主项目

| 项目 | 描述 | 链接 |
|------|------|------|
| **Croupier** | 游戏后端平台主项目 | [cuihairu/croupier](https://github.com/cuihairu/croupier) |
| **Croupier Proto** | 协议定义（Protobuf/gRPC） | [cuihairu/croupier-proto](https://github.com/cuihairu/croupier-proto) |

## 其他语言 SDK

| 语言 | 仓库 | 状态 |
|------|------|------|
| **Go** | [cuihairu/croupier-sdk-go](https://github.com/cuihairu/croupier-sdk-go) | [![Go Build](https://github.com/cuihairu/croupier-sdk-go/actions/workflows/nightly.yml/badge.svg)](https://github.com/cuihairu/croupier-sdk-go/actions/workflows/nightly.yml) |
| **Java** | [cuihairu/croupier-sdk-java](https://github.com/cuihairu/croupier-sdk-java) | [![Java Build](https://github.com/cuihairu/croupier-sdk-java/actions/workflows/nightly.yml/badge.svg)](https://github.com/cuihairu/croupier-sdk-java/actions/workflows/nightly.yml) |
| **JavaScript/TypeScript** | [cuihairu/croupier-sdk-js](https://github.com/cuihairu/croupier-sdk-js) | [![JS Build](https://github.com/cuihairu/croupier-sdk-js/actions/workflows/nightly.yml/badge.svg)](https://github.com/cuihairu/croupier-sdk-js/actions/workflows/nightly.yml) |
| **Python** | [cuihairu/croupier-sdk-python](https://github.com/cuihairu/croupier-sdk-python) | [![Python Build](https://github.com/cuihairu/croupier-sdk-python/actions/workflows/nightly.yml/badge.svg)](https://github.com/cuihairu/croupier-sdk-python/actions/workflows/nightly.yml) |

## 支持平台

| 平台 | 架构 | 状态 |
|------|------|------|
| **Windows** | x64, x86 | ✅ 支持 |
| **Linux** | x64, ARM64 | ✅ 支持 |
| **macOS** | x64, ARM64 (Apple Silicon) | ✅ 支持 |

## 核心特性

- 🏗️ **虚拟对象注册系统** - 完整的对象和函数组注册机制
- 📡 **gRPC 集成** - 真实的 Protobuf + gRPC 通信（通过 vcpkg）
- 🔧 **多平台支持** - Windows、Linux、macOS（x64/ARM64）
- 📦 **vcpkg 包管理** - 自动依赖管理和跨平台构建
- 🚀 **高性能设计** - ID 引用模式，无状态函数，轻量参数
- 🛡️ **类型安全** - JSON Schema 验证，编译时类型检查
- 🔄 **自动构建** - GitHub Actions 每日构建发布

## 快速开始

### 系统要求

- **C++17** 编译器（GCC 8+, Clang 10+, MSVC 2019+）
- **CMake 3.20+**
- **vcpkg**（推荐，用于依赖管理）

### 依赖库（自动安装）

- gRPC (通过 vcpkg)
- Protobuf 5.29.x LTS (通过 vcpkg)
- nlohmann/json (通过 vcpkg)

### 一键构建

**Linux/macOS:**
```bash
# 基础构建
./scripts/build.sh

# 清理重构建
./scripts/build.sh --clean

# 启用测试
./scripts/build.sh --tests ON
```

**Windows:**
```powershell
# 基础构建
.\scripts\build.ps1

# Debug 构建
.\scripts\build.ps1 -BuildType Debug
```

### 手动 CMake 构建

```bash
# 1. 设置 vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg && ./bootstrap-vcpkg.sh
export VCPKG_ROOT=$(pwd)

# 2. 配置构建
cmake -B build \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_BUILD_TYPE=Release

# 3. 构建
cmake --build build --parallel

# 4. 运行示例（需要本地 Agent）
#
# SDK 示例默认连接 `127.0.0.1:19090`（见 `examples/*.cpp` 里的 `agent_addr`），请先确保 Croupier Agent 已启动。
#
# 如果你在 croupier 主仓库里（包含 `server/`），可以用下面命令启动本地 Server + Agent：
#
#   cd server
#   go run ./services/server -f services/server/etc/server.yaml
#   go run ./services/agent  -f services/agent/etc/agent.yaml
#
# 然后运行 C++ 示例：
./build/bin/croupier-example
./build/bin/croupier-virtual-object-demo
```

### VS Code (CMake Tools) 使用 vcpkg（固定 Protobuf 5.29.5）

`CMake Tools` 本身不会“自动使用 vcpkg”，它只会按你当前的 CMake 配置去 `find_package()`。
如果你本机装过 Homebrew 的 `protobuf/grpc`，而 CMake 没用 vcpkg toolchain，就会误用系统 protobuf，进而报：
`Protobuf C++ gencode is built with an incompatible version of Protobuf C++ headers/runtime`。

本仓库提供了 `croupier-sdk-cpp/CMakePresets.json`（默认走 vcpkg）：
- 先设置环境变量：`export VCPKG_ROOT=/path/to/vcpkg`
- VS Code：`CMake: Select Configure Preset` → 选择 `macos-*-*-vcpkg`
- 如果之前已经 Configure 过（生成了 `croupier-sdk-cpp/build`），请先删掉 `croupier-sdk-cpp/build` 再重新 Configure（toolchain 必须在第一次 configure 时生效）

## 使用示例

### 基础函数注册

```cpp
#include "croupier/sdk/croupier_client.h"
using namespace croupier::sdk;

std::string TransferHandler(const std::string& context, const std::string& payload) {
    auto data = utils::ParseJSON(payload);
    std::string from_player = data["from_player_id"];
    std::string to_player = data["to_player_id"];
    return ExecuteTransfer(from_player, to_player, data["amount"]);
}

int main() {
    ClientConfig config;
    config.game_id = "mmorpg-demo";
    config.env = "development";
    config.agent_addr = "127.0.0.1:19090";

    CroupierClient client(config);

    FunctionDescriptor desc{"wallet.transfer", "1.0.0"};
    client.RegisterFunction(desc, TransferHandler);

    client.Connect();
    client.Serve();
}
```

### 虚拟对象注册

```cpp
VirtualObjectDescriptor wallet_entity;
wallet_entity.id = "wallet.entity";
wallet_entity.version = "1.0.0";
wallet_entity.operations["read"] = "wallet.get";
wallet_entity.operations["transfer"] = "wallet.transfer";

std::map<std::string, FunctionHandler> handlers;
handlers["wallet.get"] = WalletGetHandler;
handlers["wallet.transfer"] = WalletTransferHandler;

client.RegisterVirtualObject(wallet_entity, handlers);
```

## 架构设计

### 四层组件化架构

```
Function Level    ← wallet.transfer (具体函数实现)
     ↓
Entity Level      ← wallet.entity (业务对象模型)
     ↓
Resource Level    ← 钱包管理面板 (UI 资源组织)
     ↓
Component Level   ← economy-system (可分发模块)
```

### ID 引用模式优势

- 🚀 **极致性能**：网络传输只有几十字节
- 🛡️ **线程安全**：无状态函数，天然支持并发
- 🔄 **水平扩展**：函数可以部署到任意节点
- 🧩 **松耦合**：对象管理与业务逻辑完全分离

## API 参考

### 核心类

```cpp
class CroupierClient {
public:
    bool RegisterFunction(const FunctionDescriptor& desc, FunctionHandler handler);
    bool RegisterVirtualObject(const VirtualObjectDescriptor& desc,
                               const std::map<std::string, FunctionHandler>& handlers);
    bool RegisterComponent(const ComponentDescriptor& comp);
    bool Connect();
    void Serve();
    void Stop();
    void Close();
};
```

### 配置结构

```cpp
struct ClientConfig {
    std::string agent_addr = "127.0.0.1:19090";
    std::string game_id;
    std::string env = "development";
    std::string service_id = "cpp-service";
    bool insecure = true;
    bool auto_reconnect = true;
    int reconnect_interval_seconds = 5;
    int reconnect_max_attempts = 0; // 0 = unlimited
};
```

### 连接与重连配置说明

- `auto_reconnect`：默认 `true`；当 Agent 重启/断开时，`Serve()` 会自动尝试重连并重新注册函数；设为 `false` 时，连接断开会退出 `Serve()`。
- `reconnect_interval_seconds`：重连间隔（秒），默认 `5`（最小 `1`）。
- `reconnect_max_attempts`：最大重连次数，默认 `0` 表示无限重试；大于 0 时，达到次数后停止重连并退出 `Serve()`。

### 环境变量覆盖（`CROUPIER_` 前缀）

- `CROUPIER_AUTO_RECONNECT=true|false`
- `CROUPIER_RECONNECT_INTERVAL_SECONDS=5`
- `CROUPIER_RECONNECT_MAX_ATTEMPTS=0`

## 部署与分发

### GitHub Actions 自动构建

每日自动构建，支持多平台产物：

- 静态库 (.a/.lib)
- 动态库 (.so/.dylib/.dll)
- 头文件包
- 示例程序

### 下载预构建包

访问 [Releases 页面](https://github.com/cuihairu/croupier-sdk-cpp/releases) 下载：

**静态库包：**
- `croupier-cpp-sdk-static-{version}-windows-x64.zip`
- `croupier-cpp-sdk-static-{version}-linux-x64.tar.gz`
- `croupier-cpp-sdk-static-{version}-macos-arm64.tar.gz`

**动态库包：**
- `croupier-cpp-sdk-dynamic-{version}-windows-x64.zip`
- `croupier-cpp-sdk-dynamic-{version}-linux-x64.tar.gz`
- `croupier-cpp-sdk-dynamic-{version}-macos-arm64.tar.gz`

> 💡 **提示**：推送 `v*` 格式的 tag（如 `v1.0.0`）会自动触发正式 Release 构建

## 开发指南

### 项目结构

```
croupier-sdk-cpp/
├── include/           # 公共头文件
├── src/               # 源代码
├── examples/          # 示例程序
├── scripts/           # 构建脚本
├── cmake/             # CMake 模块
├── configs/           # 配置文件示例
└── vcpkg.json         # vcpkg 依赖清单
```

### 开发规范

- 遵循 **C++17** 标准
- 使用 **clang-format** 格式化代码
- 编写单元测试
- 更新相关文档

## 贡献指南

1. **Fork** 项目
2. 创建特性分支：`git checkout -b feature/amazing-feature`
3. 提交更改：`git commit -m 'Add amazing feature'`
4. 推送分支：`git push origin feature/amazing-feature`
5. 创建 **Pull Request**

## 许可证

本项目采用 [Apache License 2.0](LICENSE) 开源协议。

---

<p align="center">
  <a href="https://github.com/cuihairu/croupier">🏠 主项目</a> •
  <a href="https://github.com/cuihairu/croupier-sdk-cpp/issues">🐛 问题反馈</a> •
  <a href="https://github.com/cuihairu/croupier/discussions">💬 讨论区</a>
</p>
