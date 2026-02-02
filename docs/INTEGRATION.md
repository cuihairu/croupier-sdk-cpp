# Croupier C++ SDK 集成指南

本文档说明如何在Windows项目中集成Croupier C++ SDK。

## 版本说明

SDK提供两个版本，分别适用于不同的运行时类型：

| 版本 | 运行时类型 | vcpkg triplet | 用户场景 |
|------|-----------|--------------|----------|
| **MT** | 静态运行时 (`/MT`) | `x64-windows-static` | 独立可执行文件 |
| **MD** | 动态运行时 (`/MD`) | `x64-windows-static-md` | DLL插件、多模块项目 |

---

## MT 版本（静态运行时）

### 文件结构

```
mt/
├── include/
│   └── croupier/
│       └── sdk/               # SDK 头文件
└── lib/
    └── croupier-sdk.lib      ← 包含所有依赖的单个静态库（~35MB）
```

### 集成步骤

1. **添加包含目录**
   - 项目属性 → C/C++ → 常规 → 附加包含目录
   - 添加：`path/to/include`

2. **添加库目录**
   - 项目属性 → 链接器 → 常规 → 附加库目录
   - Release: `path/to/mt/lib`

3. **添加依赖库**
   - 项目属性 → 链接器 → 输入 → 附加依赖
   - 添加：`croupier-sdk.lib`

4. **设置运行时类型**
   - 项目属性 → C/C++ → 代码生成 → 运行行时库
   - 选择：**多线程调试 (/MTd)** 或 **多线程 (/MT)**

### ⚠️ 重要

- MT版本的 `croupier-sdk.lib` 已内化以下依赖（无需单独链接）：
  - gRPC::grpc++
  - gRPC::grpc
  - gRPC::gpr
  - protobuf::libprotobuf
  - zlib
  - 所有 abseil 库

- **用户程序必须使用 `/MT` 或 `/MTd` 编译选项**，否则会产生链接错误

---

## MD 版本（动态运行时）

### 文件结构

```
md/
├── include/
│   └── croupier/
│       └── sdk/               # SDK 头文件
├── bin/
│   └── croupier-sdk.dll      ← 包含所有依赖的单个DLL
└── lib/
    └── croupier-sdk.lib      ← 导入库（用于链接）
```

### 集成步骤

1. **添加包含目录**
   - 项目属性 → C/C++ → 常规 → 附加包含目录
   - 添加：`path/to/include`

2. **添加库目录**
   - 项目属性 → 链接器 → 常规 → 附加库目录
   - Release: `path/to/md/lib`

3. **添加依赖库**
   - 项目属性 → 链接器 → 输入 → 附加依赖
   - 添加：`croupier-sdk.lib`

4. **复制DLL**
   - 将 `croupier-sdk.dll` 复制到你的可执行文件所在目录

### ⚠️ 重要

- MD版本的 `croupier-sdk.dll` 已内化以下依赖（无需单独部署）：
  - gRPC::grpc++
  - gRPC::grpc
  - gRPC::gpr
  - protobuf::libprotobuf
  - zlib
  - 所有 abseil 库

- **用户程序可以用 `/MT` 或 `/MD` 编译**，都能使用此DLL

---

## 已内化的依赖（无需用户链接）

两个版本都已内化以下gRPC相关依赖：

| 库名 | 说明 |
|------|------|
| grpc++ | gRPC C++ 高层 API |
| grpc | gRPC 核心库 |
| gpr | gRPC 基础运行时 |
| libprotobuf | Protocol Buffers |
| zlib | 压缩库 |
| absl_* | Abseil 基础库（约20个） |
| ws2_32 | Windows Socket |

**用户无需单独链接以上库！**

---

## 快速示例代码

```cpp
#include <croupier/sdk/croupier_client.h>

using namespace croupier::sdk;

int main() {
    // 创建客户端配置
    ClientConfig config;
    config.game_id = "my-game";
    config.service_id = "my-service";
    config.agent_addr = "127.0.0.1:19090";
    config.insecure = true;

    // 创建客户端
    CroupierClient client(config);

    // 连接并注册
    if (client.Connect()) {
        // 注册虚拟对象
        VirtualObjectDescriptor desc;
        desc.id = "player.entity";
        desc.name = "Player";

        std::map<std::string, FunctionHandler> handlers;
        handlers["get"] = [](const std::string& ctx, const std::string& payload) {
            return "{\"data\": {}}";
        };

        client.RegisterVirtualObject(desc, handlers);
        client.Serve();
    }

    return 0;
}
```

---

## 常见问题

### Q: MT版本链接时出现 LNK2005 错误
**A**: 检查你的项目运行时库设置是否为 `/MT` 或 `/MTd`。必须与SDK使用相同的运行时类型。

### Q: MD版本的DLL运行时缺少依赖DLL
**A**: 不应该缺少。如果出现问题，请检查 `croupier-sdk.dll` 是否正确复制到exe目录。

### Q: 能否在一个项目中同时使用MT和MD版本？
**A**: 不建议。同一个进程中的所有模块必须使用相同的CRT（/MT 或 /MD）。但不同进程可以使用不同版本。

### Q: 如何选择MT还是MD？
**A**:
- **独立exe** → 使用MT版本（部署简单）
- **插件DLL** → 使用MD版本（避免CRT冲突）
