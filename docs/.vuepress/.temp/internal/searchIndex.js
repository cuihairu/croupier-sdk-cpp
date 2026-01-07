export const SEARCH_INDEX = [
  {
    "title": "Croupier C++ SDK",
    "headers": [
      {
        "level": 2,
        "title": "📋 简介",
        "slug": "📋-简介",
        "link": "#📋-简介",
        "children": []
      },
      {
        "level": 2,
        "title": "🚀 快速开始",
        "slug": "🚀-快速开始",
        "link": "#🚀-快速开始",
        "children": [
          {
            "level": 3,
            "title": "安装依赖",
            "slug": "安装依赖",
            "link": "#安装依赖",
            "children": []
          },
          {
            "level": 3,
            "title": "基础使用",
            "slug": "基础使用",
            "link": "#基础使用",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "🔗 相关链接",
        "slug": "🔗-相关链接",
        "link": "#🔗-相关链接",
        "children": []
      }
    ],
    "path": "/",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "API 参考",
    "headers": [
      {
        "level": 2,
        "title": "命名空间",
        "slug": "命名空间",
        "link": "#命名空间",
        "children": []
      },
      {
        "level": 2,
        "title": "核心类型",
        "slug": "核心类型",
        "link": "#核心类型",
        "children": [
          {
            "level": 3,
            "title": "FunctionHandler",
            "slug": "functionhandler",
            "link": "#functionhandler",
            "children": []
          },
          {
            "level": 3,
            "title": "ClientConfig",
            "slug": "clientconfig",
            "link": "#clientconfig",
            "children": []
          },
          {
            "level": 3,
            "title": "FunctionDescriptor",
            "slug": "functiondescriptor",
            "link": "#functiondescriptor",
            "children": []
          },
          {
            "level": 3,
            "title": "VirtualObjectDescriptor",
            "slug": "virtualobjectdescriptor",
            "link": "#virtualobjectdescriptor",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "类: CroupierClient",
        "slug": "类-croupierclient",
        "link": "#类-croupierclient",
        "children": [
          {
            "level": 3,
            "title": "构造函数",
            "slug": "构造函数",
            "link": "#构造函数",
            "children": []
          },
          {
            "level": 3,
            "title": "公共方法",
            "slug": "公共方法",
            "link": "#公共方法",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "工具函数",
        "slug": "工具函数",
        "link": "#工具函数",
        "children": [
          {
            "level": 3,
            "title": "utils::ParseJSON",
            "slug": "utils-parsejson",
            "link": "#utils-parsejson",
            "children": []
          },
          {
            "level": 3,
            "title": "utils::ToJSON",
            "slug": "utils-tojson",
            "link": "#utils-tojson",
            "children": []
          },
          {
            "level": 3,
            "title": "utils::ValidateJSON",
            "slug": "utils-validatejson",
            "link": "#utils-validatejson",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置加载",
        "slug": "配置加载",
        "link": "#配置加载",
        "children": [
          {
            "level": 3,
            "title": "ClientConfigLoader",
            "slug": "clientconfigloader",
            "link": "#clientconfigloader",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "错误处理",
        "slug": "错误处理",
        "link": "#错误处理",
        "children": [
          {
            "level": 3,
            "title": "CroupierException",
            "slug": "croupierexception",
            "link": "#croupierexception",
            "children": []
          },
          {
            "level": 3,
            "title": "异常类型",
            "slug": "异常类型",
            "link": "#异常类型",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "回调类型",
        "slug": "回调类型",
        "link": "#回调类型",
        "children": [
          {
            "level": 3,
            "title": "ConnectionCallback",
            "slug": "connectioncallback",
            "link": "#connectioncallback",
            "children": []
          },
          {
            "level": 3,
            "title": "ErrorCallback",
            "slug": "errorcallback",
            "link": "#errorcallback",
            "children": []
          },
          {
            "level": 3,
            "title": "LogCallback",
            "slug": "logcallback",
            "link": "#logcallback",
            "children": []
          }
        ]
      }
    ],
    "path": "/api/",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "CroupierClient API 详解",
    "headers": [
      {
        "level": 2,
        "title": "类定义",
        "slug": "类定义",
        "link": "#类定义",
        "children": []
      },
      {
        "level": 2,
        "title": "方法详解",
        "slug": "方法详解",
        "link": "#方法详解",
        "children": [
          {
            "level": 3,
            "title": "构造函数",
            "slug": "构造函数",
            "link": "#构造函数",
            "children": []
          },
          {
            "level": 3,
            "title": "RegisterFunction",
            "slug": "registerfunction",
            "link": "#registerfunction",
            "children": []
          },
          {
            "level": 3,
            "title": "RegisterVirtualObject",
            "slug": "registervirtualobject",
            "link": "#registervirtualobject",
            "children": []
          },
          {
            "level": 3,
            "title": "Connect",
            "slug": "connect",
            "link": "#connect",
            "children": []
          },
          {
            "level": 3,
            "title": "Serve",
            "slug": "serve",
            "link": "#serve",
            "children": []
          },
          {
            "level": 3,
            "title": "Stop",
            "slug": "stop",
            "link": "#stop",
            "children": []
          },
          {
            "level": 3,
            "title": "SetConnectionCallback",
            "slug": "setconnectioncallback",
            "link": "#setconnectioncallback",
            "children": []
          },
          {
            "level": 3,
            "title": "SetErrorCallback",
            "slug": "seterrorcallback",
            "link": "#seterrorcallback",
            "children": []
          },
          {
            "level": 3,
            "title": "SetLogCallback",
            "slug": "setlogcallback",
            "link": "#setlogcallback",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "使用模式",
        "slug": "使用模式",
        "link": "#使用模式",
        "children": [
          {
            "level": 3,
            "title": "基础模式",
            "slug": "基础模式",
            "link": "#基础模式",
            "children": []
          },
          {
            "level": 3,
            "title": "多线程模式",
            "slug": "多线程模式",
            "link": "#多线程模式",
            "children": []
          },
          {
            "level": 3,
            "title": "优雅退出模式",
            "slug": "优雅退出模式",
            "link": "#优雅退出模式",
            "children": []
          }
        ]
      }
    ],
    "path": "/api/client.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "ClientConfig API 详解",
    "headers": [
      {
        "level": 2,
        "title": "结构定义",
        "slug": "结构定义",
        "link": "#结构定义",
        "children": []
      },
      {
        "level": 2,
        "title": "配置字段详解",
        "slug": "配置字段详解",
        "link": "#配置字段详解",
        "children": [
          {
            "level": 3,
            "title": "基础连接配置",
            "slug": "基础连接配置",
            "link": "#基础连接配置",
            "children": []
          },
          {
            "level": 3,
            "title": "超时配置",
            "slug": "超时配置",
            "link": "#超时配置",
            "children": []
          },
          {
            "level": 3,
            "title": "TLS 配置",
            "slug": "tls-配置",
            "link": "#tls-配置",
            "children": []
          },
          {
            "level": 3,
            "title": "重连配置",
            "slug": "重连配置",
            "link": "#重连配置",
            "children": []
          },
          {
            "level": 3,
            "title": "认证配置",
            "slug": "认证配置",
            "link": "#认证配置",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置加载",
        "slug": "配置加载",
        "link": "#配置加载",
        "children": [
          {
            "level": 3,
            "title": "从文件加载",
            "slug": "从文件加载",
            "link": "#从文件加载",
            "children": []
          },
          {
            "level": 3,
            "title": "从环境变量覆盖",
            "slug": "从环境变量覆盖",
            "link": "#从环境变量覆盖",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置验证",
        "slug": "配置验证",
        "link": "#配置验证",
        "children": []
      },
      {
        "level": 2,
        "title": "配置示例",
        "slug": "配置示例",
        "link": "#配置示例",
        "children": [
          {
            "level": 3,
            "title": "开发环境",
            "slug": "开发环境",
            "link": "#开发环境",
            "children": []
          },
          {
            "level": 3,
            "title": "生产环境",
            "slug": "生产环境",
            "link": "#生产环境",
            "children": []
          },
          {
            "level": 3,
            "title": "Kubernetes 环境",
            "slug": "kubernetes-环境",
            "link": "#kubernetes-环境",
            "children": []
          }
        ]
      }
    ],
    "path": "/api/config.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "函数 API 详解",
    "headers": [
      {
        "level": 2,
        "title": "FunctionDescriptor",
        "slug": "functiondescriptor",
        "link": "#functiondescriptor",
        "children": []
      },
      {
        "level": 2,
        "title": "字段说明",
        "slug": "字段说明",
        "link": "#字段说明",
        "children": [
          {
            "level": 3,
            "title": "id",
            "slug": "id",
            "link": "#id",
            "children": []
          },
          {
            "level": 3,
            "title": "version",
            "slug": "version",
            "link": "#version",
            "children": []
          },
          {
            "level": 3,
            "title": "name & description",
            "slug": "name-description",
            "link": "#name-description",
            "children": []
          },
          {
            "level": 3,
            "title": "input_schema",
            "slug": "input-schema",
            "link": "#input-schema",
            "children": []
          },
          {
            "level": 3,
            "title": "output_schema",
            "slug": "output-schema",
            "link": "#output-schema",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "FunctionHandler",
        "slug": "functionhandler",
        "link": "#functionhandler",
        "children": [
          {
            "level": 3,
            "title": "参数说明",
            "slug": "参数说明",
            "link": "#参数说明",
            "children": []
          },
          {
            "level": 3,
            "title": "返回值",
            "slug": "返回值",
            "link": "#返回值",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "注册函数",
        "slug": "注册函数",
        "link": "#注册函数",
        "children": [
          {
            "level": 3,
            "title": "单个注册",
            "slug": "单个注册",
            "link": "#单个注册",
            "children": []
          },
          {
            "level": 3,
            "title": "完整描述符注册",
            "slug": "完整描述符注册",
            "link": "#完整描述符注册",
            "children": []
          },
          {
            "level": 3,
            "title": "批量注册",
            "slug": "批量注册",
            "link": "#批量注册",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "函数模式",
        "slug": "函数模式",
        "link": "#函数模式",
        "children": [
          {
            "level": 3,
            "title": "简单函数",
            "slug": "简单函数",
            "link": "#简单函数",
            "children": []
          },
          {
            "level": 3,
            "title": "业务逻辑函数",
            "slug": "业务逻辑函数",
            "link": "#业务逻辑函数",
            "children": []
          },
          {
            "level": 3,
            "title": "类成员函数",
            "slug": "类成员函数",
            "link": "#类成员函数",
            "children": []
          },
          {
            "level": 3,
            "title": "异步处理函数",
            "slug": "异步处理函数",
            "link": "#异步处理函数",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "错误处理",
        "slug": "错误处理",
        "link": "#错误处理",
        "children": [
          {
            "level": 3,
            "title": "标准错误响应",
            "slug": "标准错误响应",
            "link": "#标准错误响应",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 输入验证",
            "slug": "_1-输入验证",
            "link": "#_1-输入验证",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 超时控制",
            "slug": "_2-超时控制",
            "link": "#_2-超时控制",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 版本管理",
            "slug": "_3-版本管理",
            "link": "#_3-版本管理",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 日志记录",
            "slug": "_4-日志记录",
            "link": "#_4-日志记录",
            "children": []
          }
        ]
      }
    ],
    "path": "/api/functions.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "虚拟对象 API 详解",
    "headers": [
      {
        "level": 2,
        "title": "VirtualObjectDescriptor",
        "slug": "virtualobjectdescriptor",
        "link": "#virtualobjectdescriptor",
        "children": []
      },
      {
        "level": 2,
        "title": "字段说明",
        "slug": "字段说明",
        "link": "#字段说明",
        "children": [
          {
            "level": 3,
            "title": "id",
            "slug": "id",
            "link": "#id",
            "children": []
          },
          {
            "level": 3,
            "title": "operations",
            "slug": "operations",
            "link": "#operations",
            "children": []
          },
          {
            "level": 3,
            "title": "schema",
            "slug": "schema",
            "link": "#schema",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "注册虚拟对象",
        "slug": "注册虚拟对象",
        "link": "#注册虚拟对象",
        "children": [
          {
            "level": 3,
            "title": "基础注册",
            "slug": "基础注册",
            "link": "#基础注册",
            "children": []
          },
          {
            "level": 3,
            "title": "完整示例",
            "slug": "完整示例",
            "link": "#完整示例",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "操作处理器",
        "slug": "操作处理器",
        "link": "#操作处理器",
        "children": [
          {
            "level": 3,
            "title": "CRUD 操作模式",
            "slug": "crud-操作模式",
            "link": "#crud-操作模式",
            "children": []
          },
          {
            "level": 3,
            "title": "自定义操作",
            "slug": "自定义操作",
            "link": "#自定义操作",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Schema 验证",
        "slug": "schema-验证",
        "link": "#schema-验证",
        "children": [
          {
            "level": 3,
            "title": "定义 Schema",
            "slug": "定义-schema",
            "link": "#定义-schema",
            "children": []
          },
          {
            "level": 3,
            "title": "验证数据",
            "slug": "验证数据",
            "link": "#验证数据",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "元数据",
        "slug": "元数据",
        "link": "#元数据",
        "children": [
          {
            "level": 3,
            "title": "添加元数据",
            "slug": "添加元数据",
            "link": "#添加元数据",
            "children": []
          },
          {
            "level": 3,
            "title": "使用元数据",
            "slug": "使用元数据",
            "link": "#使用元数据",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "关联关系",
        "slug": "关联关系",
        "link": "#关联关系",
        "children": [
          {
            "level": 3,
            "title": "父子关系",
            "slug": "父子关系",
            "link": "#父子关系",
            "children": []
          },
          {
            "level": 3,
            "title": "引用关系",
            "slug": "引用关系",
            "link": "#引用关系",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 使用类封装",
            "slug": "_1-使用类封装",
            "link": "#_1-使用类封装",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 操作命名规范",
            "slug": "_2-操作命名规范",
            "link": "#_2-操作命名规范",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 统一响应格式",
            "slug": "_3-统一响应格式",
            "link": "#_3-统一响应格式",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 权限检查",
            "slug": "_4-权限检查",
            "link": "#_4-权限检查",
            "children": []
          }
        ]
      }
    ],
    "path": "/api/virtual-objects.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "配置指南",
    "headers": [
      {
        "level": 2,
        "title": "目录",
        "slug": "目录",
        "link": "#目录",
        "children": []
      },
      {
        "level": 2,
        "title": "快速开始",
        "slug": "快速开始",
        "link": "#快速开始",
        "children": [
          {
            "level": 3,
            "title": "基础配置文件",
            "slug": "基础配置文件",
            "link": "#基础配置文件",
            "children": []
          },
          {
            "level": 3,
            "title": "加载配置",
            "slug": "加载配置",
            "link": "#加载配置",
            "children": []
          },
          {
            "level": 3,
            "title": "环境变量覆盖",
            "slug": "环境变量覆盖",
            "link": "#环境变量覆盖",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置加载器",
        "slug": "配置加载器",
        "link": "#配置加载器",
        "children": [
          {
            "level": 3,
            "title": "ClientConfigLoader 方法",
            "slug": "clientconfigloader-方法",
            "link": "#clientconfigloader-方法",
            "children": []
          },
          {
            "level": 3,
            "title": "示例",
            "slug": "示例",
            "link": "#示例",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "环境变量",
        "slug": "环境变量",
        "link": "#环境变量",
        "children": [
          {
            "level": 3,
            "title": "嵌套字段",
            "slug": "嵌套字段",
            "link": "#嵌套字段",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置文件位置",
        "slug": "配置文件位置",
        "link": "#配置文件位置",
        "children": []
      },
      {
        "level": 2,
        "title": "配置验证",
        "slug": "配置验证",
        "link": "#配置验证",
        "children": [
          {
            "level": 3,
            "title": "自定义验证",
            "slug": "自定义验证",
            "link": "#自定义验证",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "下一步",
        "slug": "下一步",
        "link": "#下一步",
        "children": []
      }
    ],
    "path": "/configuration/",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "客户端配置详解",
    "headers": [
      {
        "level": 2,
        "title": "完整结构",
        "slug": "完整结构",
        "link": "#完整结构",
        "children": []
      },
      {
        "level": 2,
        "title": "字段详解",
        "slug": "字段详解",
        "link": "#字段详解",
        "children": [
          {
            "level": 3,
            "title": "agent_addr",
            "slug": "agent-addr",
            "link": "#agent-addr",
            "children": []
          },
          {
            "level": 3,
            "title": "game_id",
            "slug": "game-id",
            "link": "#game-id",
            "children": []
          },
          {
            "level": 3,
            "title": "env",
            "slug": "env",
            "link": "#env",
            "children": []
          },
          {
            "level": 3,
            "title": "service_id",
            "slug": "service-id",
            "link": "#service-id",
            "children": []
          },
          {
            "level": 3,
            "title": "timeout_seconds",
            "slug": "timeout-seconds",
            "link": "#timeout-seconds",
            "children": []
          },
          {
            "level": 3,
            "title": "insecure",
            "slug": "insecure",
            "link": "#insecure",
            "children": []
          },
          {
            "level": 3,
            "title": "security (结构体)",
            "slug": "security-结构体",
            "link": "#security-结构体",
            "children": []
          },
          {
            "level": 3,
            "title": "auto_reconnect",
            "slug": "auto-reconnect",
            "link": "#auto-reconnect",
            "children": []
          },
          {
            "level": 3,
            "title": "reconnect_interval_seconds",
            "slug": "reconnect-interval-seconds",
            "link": "#reconnect-interval-seconds",
            "children": []
          },
          {
            "level": 3,
            "title": "reconnect_max_attempts",
            "slug": "reconnect-max-attempts",
            "link": "#reconnect-max-attempts",
            "children": []
          },
          {
            "level": 3,
            "title": "auth (结构体)",
            "slug": "auth-结构体",
            "link": "#auth-结构体",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置示例",
        "slug": "配置示例",
        "link": "#配置示例",
        "children": [
          {
            "level": 3,
            "title": "最小配置",
            "slug": "最小配置",
            "link": "#最小配置",
            "children": []
          },
          {
            "level": 3,
            "title": "开发环境",
            "slug": "开发环境",
            "link": "#开发环境",
            "children": []
          },
          {
            "level": 3,
            "title": "生产环境",
            "slug": "生产环境",
            "link": "#生产环境",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "默认值",
        "slug": "默认值",
        "link": "#默认值",
        "children": []
      }
    ],
    "path": "/configuration/client-config.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "多环境配置",
    "headers": [
      {
        "level": 2,
        "title": "目录结构",
        "slug": "目录结构",
        "link": "#目录结构",
        "children": []
      },
      {
        "level": 2,
        "title": "基础配置 (base.json)",
        "slug": "基础配置-base-json",
        "link": "#基础配置-base-json",
        "children": []
      },
      {
        "level": 2,
        "title": "开发环境 (development.json)",
        "slug": "开发环境-development-json",
        "link": "#开发环境-development-json",
        "children": []
      },
      {
        "level": 2,
        "title": "预发布环境 (staging.json)",
        "slug": "预发布环境-staging-json",
        "link": "#预发布环境-staging-json",
        "children": []
      },
      {
        "level": 2,
        "title": "生产环境 (production.json)",
        "slug": "生产环境-production-json",
        "link": "#生产环境-production-json",
        "children": []
      },
      {
        "level": 2,
        "title": "加载配置",
        "slug": "加载配置",
        "link": "#加载配置",
        "children": [
          {
            "level": 3,
            "title": "指定环境",
            "slug": "指定环境",
            "link": "#指定环境",
            "children": []
          },
          {
            "level": 3,
            "title": "使用环境变量",
            "slug": "使用环境变量",
            "link": "#使用环境变量",
            "children": []
          },
          {
            "level": 3,
            "title": "程序运行时切换",
            "slug": "程序运行时切换",
            "link": "#程序运行时切换",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置合并",
        "slug": "配置合并",
        "link": "#配置合并",
        "children": [
          {
            "level": 3,
            "title": "示例",
            "slug": "示例",
            "link": "#示例",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "环境特定覆盖",
        "slug": "环境特定覆盖",
        "link": "#环境特定覆盖",
        "children": [
          {
            "level": 3,
            "title": "开发环境特有",
            "slug": "开发环境特有",
            "link": "#开发环境特有",
            "children": []
          },
          {
            "level": 3,
            "title": "生产环境特有",
            "slug": "生产环境特有",
            "link": "#生产环境特有",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Kubernetes ConfigMap",
        "slug": "kubernetes-configmap",
        "link": "#kubernetes-configmap",
        "children": [
          {
            "level": 3,
            "title": "创建 ConfigMap",
            "slug": "创建-configmap",
            "link": "#创建-configmap",
            "children": []
          },
          {
            "level": 3,
            "title": "挂载到 Pod",
            "slug": "挂载到-pod",
            "link": "#挂载到-pod",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Docker 环境",
        "slug": "docker-环境",
        "link": "#docker-环境",
        "children": [
          {
            "level": 3,
            "title": "Dockerfile",
            "slug": "dockerfile",
            "link": "#dockerfile",
            "children": []
          },
          {
            "level": 3,
            "title": "docker-compose.yml",
            "slug": "docker-compose-yml",
            "link": "#docker-compose-yml",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 敏感信息不写入配置文件",
            "slug": "_1-敏感信息不写入配置文件",
            "link": "#_1-敏感信息不写入配置文件",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 使用配置验证",
            "slug": "_2-使用配置验证",
            "link": "#_2-使用配置验证",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 配置文件版本控制",
            "slug": "_3-配置文件版本控制",
            "link": "#_3-配置文件版本控制",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 使用 .gitignore",
            "slug": "_4-使用-gitignore",
            "link": "#_4-使用-gitignore",
            "children": []
          }
        ]
      }
    ],
    "path": "/configuration/environments.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "安全配置",
    "headers": [
      {
        "level": 2,
        "title": "TLS 配置",
        "slug": "tls-配置",
        "link": "#tls-配置",
        "children": [
          {
            "level": 3,
            "title": "基础 TLS",
            "slug": "基础-tls",
            "link": "#基础-tls",
            "children": []
          },
          {
            "level": 3,
            "title": "配置文件",
            "slug": "配置文件",
            "link": "#配置文件",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "证书生成",
        "slug": "证书生成",
        "link": "#证书生成",
        "children": [
          {
            "level": 3,
            "title": "生成 CA 证书",
            "slug": "生成-ca-证书",
            "link": "#生成-ca-证书",
            "children": []
          },
          {
            "level": 3,
            "title": "生成服务器证书",
            "slug": "生成服务器证书",
            "link": "#生成服务器证书",
            "children": []
          },
          {
            "level": 3,
            "title": "生成客户端证书",
            "slug": "生成客户端证书",
            "link": "#生成客户端证书",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "认证配置",
        "slug": "认证配置",
        "link": "#认证配置",
        "children": [
          {
            "level": 3,
            "title": "JWT Token",
            "slug": "jwt-token",
            "link": "#jwt-token",
            "children": []
          },
          {
            "level": 3,
            "title": "使用环境变量",
            "slug": "使用环境变量",
            "link": "#使用环境变量",
            "children": []
          },
          {
            "level": 3,
            "title": "配置文件",
            "slug": "配置文件-1",
            "link": "#配置文件-1",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Kubernetes Secrets",
        "slug": "kubernetes-secrets",
        "link": "#kubernetes-secrets",
        "children": [
          {
            "level": 3,
            "title": "创建 TLS Secret",
            "slug": "创建-tls-secret",
            "link": "#创建-tls-secret",
            "children": []
          },
          {
            "level": 3,
            "title": "创建 Token Secret",
            "slug": "创建-token-secret",
            "link": "#创建-token-secret",
            "children": []
          },
          {
            "level": 3,
            "title": "Pod 中使用",
            "slug": "pod-中使用",
            "link": "#pod-中使用",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "证书验证",
        "slug": "证书验证",
        "link": "#证书验证",
        "children": [
          {
            "level": 3,
            "title": "验证证书文件存在",
            "slug": "验证证书文件存在",
            "link": "#验证证书文件存在",
            "children": []
          },
          {
            "level": 3,
            "title": "验证证书有效期",
            "slug": "验证证书有效期",
            "link": "#验证证书有效期",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 永不在生产环境使用 insecure: true",
            "slug": "_1-永不在生产环境使用-insecure-true",
            "link": "#_1-永不在生产环境使用-insecure-true",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 使用密钥管理系统",
            "slug": "_2-使用密钥管理系统",
            "link": "#_2-使用密钥管理系统",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 定期轮换证书",
            "slug": "_3-定期轮换证书",
            "link": "#_3-定期轮换证书",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 证书监控",
            "slug": "_4-证书监控",
            "link": "#_4-证书监控",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "故障排查",
        "slug": "故障排查",
        "link": "#故障排查",
        "children": [
          {
            "level": 3,
            "title": "证书验证失败",
            "slug": "证书验证失败",
            "link": "#证书验证失败",
            "children": []
          },
          {
            "level": 3,
            "title": "私钥不匹配",
            "slug": "私钥不匹配",
            "link": "#私钥不匹配",
            "children": []
          },
          {
            "level": 3,
            "title": "连接超时",
            "slug": "连接超时",
            "link": "#连接超时",
            "children": []
          }
        ]
      }
    ],
    "path": "/configuration/security.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "入门指南",
    "headers": [
      {
        "level": 2,
        "title": "系统要求",
        "slug": "系统要求",
        "link": "#系统要求",
        "children": [
          {
            "level": 3,
            "title": "必需组件",
            "slug": "必需组件",
            "link": "#必需组件",
            "children": []
          },
          {
            "level": 3,
            "title": "支持的平台",
            "slug": "支持的平台",
            "link": "#支持的平台",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "目录结构",
        "slug": "目录结构",
        "link": "#目录结构",
        "children": []
      },
      {
        "level": 2,
        "title": "下一步",
        "slug": "下一步",
        "link": "#下一步",
        "children": []
      }
    ],
    "path": "/guide/",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "架构设计",
    "headers": [
      {
        "level": 2,
        "title": "四层组件化架构",
        "slug": "四层组件化架构",
        "link": "#四层组件化架构",
        "children": [
          {
            "level": 3,
            "title": "Function Level（函数层）",
            "slug": "function-level-函数层",
            "link": "#function-level-函数层",
            "children": []
          },
          {
            "level": 3,
            "title": "Entity Level（实体层）",
            "slug": "entity-level-实体层",
            "link": "#entity-level-实体层",
            "children": []
          },
          {
            "level": 3,
            "title": "Resource Level（资源层）",
            "slug": "resource-level-资源层",
            "link": "#resource-level-资源层",
            "children": []
          },
          {
            "level": 3,
            "title": "Component Level（组件层）",
            "slug": "component-level-组件层",
            "link": "#component-level-组件层",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "ID 引用模式",
        "slug": "id-引用模式",
        "link": "#id-引用模式",
        "children": [
          {
            "level": 3,
            "title": "设计理念",
            "slug": "设计理念",
            "link": "#设计理念",
            "children": []
          },
          {
            "level": 3,
            "title": "优势",
            "slug": "优势",
            "link": "#优势",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "通信架构",
        "slug": "通信架构",
        "link": "#通信架构",
        "children": [
          {
            "level": 3,
            "title": "连接流程",
            "slug": "连接流程",
            "link": "#连接流程",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "核心组件",
        "slug": "核心组件",
        "link": "#核心组件",
        "children": [
          {
            "level": 3,
            "title": "CroupierClient",
            "slug": "croupierclient",
            "link": "#croupierclient",
            "children": []
          },
          {
            "level": 3,
            "title": "GrpcService",
            "slug": "grpcservice",
            "link": "#grpcservice",
            "children": []
          },
          {
            "level": 3,
            "title": "ConfigManager",
            "slug": "configmanager",
            "link": "#configmanager",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "数据流",
        "slug": "数据流",
        "link": "#数据流",
        "children": [
          {
            "level": 3,
            "title": "请求流",
            "slug": "请求流",
            "link": "#请求流",
            "children": []
          },
          {
            "level": 3,
            "title": "响应流",
            "slug": "响应流",
            "link": "#响应流",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "线程模型",
        "slug": "线程模型",
        "link": "#线程模型",
        "children": []
      },
      {
        "level": 2,
        "title": "错误处理",
        "slug": "错误处理",
        "link": "#错误处理",
        "children": [
          {
            "level": 3,
            "title": "错误传播",
            "slug": "错误传播",
            "link": "#错误传播",
            "children": []
          },
          {
            "level": 3,
            "title": "错误格式",
            "slug": "错误格式",
            "link": "#错误格式",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/architecture.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "构建指南",
    "headers": [
      {
        "level": 2,
        "title": "构建脚本",
        "slug": "构建脚本",
        "link": "#构建脚本",
        "children": [
          {
            "level": 3,
            "title": "Linux/macOS: build.sh",
            "slug": "linux-macos-build-sh",
            "link": "#linux-macos-build-sh",
            "children": []
          },
          {
            "level": 3,
            "title": "Windows: build.ps1",
            "slug": "windows-build-ps1",
            "link": "#windows-build-ps1",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "CMake 选项",
        "slug": "cmake-选项",
        "link": "#cmake-选项",
        "children": [
          {
            "level": 3,
            "title": "基础选项",
            "slug": "基础选项",
            "link": "#基础选项",
            "children": []
          },
          {
            "level": 3,
            "title": "vcpkg 相关",
            "slug": "vcpkg-相关",
            "link": "#vcpkg-相关",
            "children": []
          },
          {
            "level": 3,
            "title": "示例配置",
            "slug": "示例配置",
            "link": "#示例配置",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "CMake Presets",
        "slug": "cmake-presets",
        "link": "#cmake-presets",
        "children": [
          {
            "level": 3,
            "title": "可用 Presets",
            "slug": "可用-presets",
            "link": "#可用-presets",
            "children": []
          },
          {
            "level": 3,
            "title": "使用 Presets",
            "slug": "使用-presets",
            "link": "#使用-presets",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "自定义构建",
        "slug": "自定义构建",
        "link": "#自定义构建",
        "children": [
          {
            "level": 3,
            "title": "禁用自动下载 vcpkg",
            "slug": "禁用自动下载-vcpkg",
            "link": "#禁用自动下载-vcpkg",
            "children": []
          },
          {
            "level": 3,
            "title": "使用全局 vcpkg",
            "slug": "使用全局-vcpkg",
            "link": "#使用全局-vcpkg",
            "children": []
          },
          {
            "level": 3,
            "title": "指定安装前缀",
            "slug": "指定安装前缀",
            "link": "#指定安装前缀",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "编译器特定选项",
        "slug": "编译器特定选项",
        "link": "#编译器特定选项",
        "children": [
          {
            "level": 3,
            "title": "GCC",
            "slug": "gcc",
            "link": "#gcc",
            "children": []
          },
          {
            "level": 3,
            "title": "Clang",
            "slug": "clang",
            "link": "#clang",
            "children": []
          },
          {
            "level": 3,
            "title": "MSVC (Visual Studio)",
            "slug": "msvc-visual-studio",
            "link": "#msvc-visual-studio",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "性能优化",
        "slug": "性能优化",
        "link": "#性能优化",
        "children": [
          {
            "level": 3,
            "title": "Release 构建优化",
            "slug": "release-构建优化",
            "link": "#release-构建优化",
            "children": []
          },
          {
            "level": 3,
            "title": "特定架构优化",
            "slug": "特定架构优化",
            "link": "#特定架构优化",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "静态分析",
        "slug": "静态分析",
        "link": "#静态分析",
        "children": [
          {
            "level": 3,
            "title": "使用 clang-tidy",
            "slug": "使用-clang-tidy",
            "link": "#使用-clang-tidy",
            "children": []
          },
          {
            "level": 3,
            "title": "使用 cppcheck",
            "slug": "使用-cppcheck",
            "link": "#使用-cppcheck",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "调试构建",
        "slug": "调试构建",
        "link": "#调试构建",
        "children": [
          {
            "level": 3,
            "title": "启用调试符号",
            "slug": "启用调试符号",
            "link": "#启用调试符号",
            "children": []
          },
          {
            "level": 3,
            "title": "启用地址清理器 (ASAN)",
            "slug": "启用地址清理器-asan",
            "link": "#启用地址清理器-asan",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "构建产物",
        "slug": "构建产物",
        "link": "#构建产物",
        "children": []
      },
      {
        "level": 2,
        "title": "故障排除",
        "slug": "故障排除",
        "link": "#故障排除",
        "children": [
          {
            "level": 3,
            "title": "构建失败",
            "slug": "构建失败",
            "link": "#构建失败",
            "children": []
          },
          {
            "level": 3,
            "title": "vcpkg 依赖安装失败",
            "slug": "vcpkg-依赖安装失败",
            "link": "#vcpkg-依赖安装失败",
            "children": []
          },
          {
            "level": 3,
            "title": "Protobuf 版本冲突",
            "slug": "protobuf-版本冲突",
            "link": "#protobuf-版本冲突",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/building.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "部署指南",
    "headers": [
      {
        "level": 2,
        "title": "部署模式",
        "slug": "部署模式",
        "link": "#部署模式",
        "children": [
          {
            "level": 3,
            "title": "模式对比",
            "slug": "模式对比",
            "link": "#模式对比",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "独立进程部署",
        "slug": "独立进程部署",
        "link": "#独立进程部署",
        "children": [
          {
            "level": 3,
            "title": "目录结构",
            "slug": "目录结构",
            "link": "#目录结构",
            "children": []
          },
          {
            "level": 3,
            "title": "启动脚本",
            "slug": "启动脚本",
            "link": "#启动脚本",
            "children": []
          },
          {
            "level": 3,
            "title": "停止脚本",
            "slug": "停止脚本",
            "link": "#停止脚本",
            "children": []
          },
          {
            "level": 3,
            "title": "系统服务（systemd）",
            "slug": "系统服务-systemd",
            "link": "#系统服务-systemd",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "容器化部署",
        "slug": "容器化部署",
        "link": "#容器化部署",
        "children": [
          {
            "level": 3,
            "title": "Dockerfile",
            "slug": "dockerfile",
            "link": "#dockerfile",
            "children": []
          },
          {
            "level": 3,
            "title": "构建镜像",
            "slug": "构建镜像",
            "link": "#构建镜像",
            "children": []
          },
          {
            "level": 3,
            "title": "Docker Compose",
            "slug": "docker-compose",
            "link": "#docker-compose",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Kubernetes 部署",
        "slug": "kubernetes-部署",
        "link": "#kubernetes-部署",
        "children": [
          {
            "level": 3,
            "title": "Deployment",
            "slug": "deployment",
            "link": "#deployment",
            "children": []
          },
          {
            "level": 3,
            "title": "ConfigMap",
            "slug": "configmap",
            "link": "#configmap",
            "children": []
          },
          {
            "level": 3,
            "title": "Secret",
            "slug": "secret",
            "link": "#secret",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "负载均衡",
        "slug": "负载均衡",
        "link": "#负载均衡",
        "children": [
          {
            "level": 3,
            "title": "Nginx 配置",
            "slug": "nginx-配置",
            "link": "#nginx-配置",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "监控和日志",
        "slug": "监控和日志",
        "link": "#监控和日志",
        "children": [
          {
            "level": 3,
            "title": "健康检查端点",
            "slug": "健康检查端点",
            "link": "#健康检查端点",
            "children": []
          },
          {
            "level": 3,
            "title": "日志配置",
            "slug": "日志配置",
            "link": "#日志配置",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "安全加固",
        "slug": "安全加固",
        "link": "#安全加固",
        "children": [
          {
            "level": 3,
            "title": "TLS 配置",
            "slug": "tls-配置",
            "link": "#tls-配置",
            "children": []
          },
          {
            "level": 3,
            "title": "Secret 管理",
            "slug": "secret-管理",
            "link": "#secret-管理",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "高可用配置",
        "slug": "高可用配置",
        "link": "#高可用配置",
        "children": [
          {
            "level": 3,
            "title": "多区域部署",
            "slug": "多区域部署",
            "link": "#多区域部署",
            "children": []
          },
          {
            "level": 3,
            "title": "故障转移",
            "slug": "故障转移",
            "link": "#故障转移",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/deployment.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "函数注册",
    "headers": [
      {
        "level": 2,
        "title": "函数处理器",
        "slug": "函数处理器",
        "link": "#函数处理器",
        "children": [
          {
            "level": 3,
            "title": "基础签名",
            "slug": "基础签名",
            "link": "#基础签名",
            "children": []
          },
          {
            "level": 3,
            "title": "简单函数示例",
            "slug": "简单函数示例",
            "link": "#简单函数示例",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "注册函数",
        "slug": "注册函数",
        "link": "#注册函数",
        "children": [
          {
            "level": 3,
            "title": "单个函数注册",
            "slug": "单个函数注册",
            "link": "#单个函数注册",
            "children": []
          },
          {
            "level": 3,
            "title": "批量函数注册",
            "slug": "批量函数注册",
            "link": "#批量函数注册",
            "children": []
          },
          {
            "level": 3,
            "title": "使用 Lambda 函数",
            "slug": "使用-lambda-函数",
            "link": "#使用-lambda-函数",
            "children": []
          },
          {
            "level": 3,
            "title": "使用类成员函数",
            "slug": "使用类成员函数",
            "link": "#使用类成员函数",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "函数描述符",
        "slug": "函数描述符",
        "link": "#函数描述符",
        "children": [
          {
            "level": 3,
            "title": "完整描述符",
            "slug": "完整描述符",
            "link": "#完整描述符",
            "children": []
          },
          {
            "level": 3,
            "title": "带输入输出 Schema 的函数",
            "slug": "带输入输出-schema-的函数",
            "link": "#带输入输出-schema-的函数",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "上下文信息",
        "slug": "上下文信息",
        "link": "#上下文信息",
        "children": [
          {
            "level": 3,
            "title": "解析上下文",
            "slug": "解析上下文",
            "link": "#解析上下文",
            "children": []
          },
          {
            "level": 3,
            "title": "上下文字段",
            "slug": "上下文字段",
            "link": "#上下文字段",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "错误处理",
        "slug": "错误处理",
        "link": "#错误处理",
        "children": [
          {
            "level": 3,
            "title": "返回错误",
            "slug": "返回错误",
            "link": "#返回错误",
            "children": []
          },
          {
            "level": 3,
            "title": "统一错误响应",
            "slug": "统一错误响应",
            "link": "#统一错误响应",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "异步处理",
        "slug": "异步处理",
        "link": "#异步处理",
        "children": [
          {
            "level": 3,
            "title": "使用线程池",
            "slug": "使用线程池",
            "link": "#使用线程池",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 函数命名规范",
            "slug": "_1-函数命名规范",
            "link": "#_1-函数命名规范",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 版本管理",
            "slug": "_2-版本管理",
            "link": "#_2-版本管理",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 参数验证",
            "slug": "_3-参数验证",
            "link": "#_3-参数验证",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 超时处理",
            "slug": "_4-超时处理",
            "link": "#_4-超时处理",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/functions.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "安装指南",
    "headers": [
      {
        "level": 2,
        "title": "方法一：使用预构建包（推荐）",
        "slug": "方法一-使用预构建包-推荐",
        "link": "#方法一-使用预构建包-推荐",
        "children": [
          {
            "level": 3,
            "title": "下载预构建包",
            "slug": "下载预构建包",
            "link": "#下载预构建包",
            "children": []
          },
          {
            "level": 3,
            "title": "使用预构建包",
            "slug": "使用预构建包",
            "link": "#使用预构建包",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "方法二：从源代码构建",
        "slug": "方法二-从源代码构建",
        "link": "#方法二-从源代码构建",
        "children": [
          {
            "level": 3,
            "title": "Linux/macOS",
            "slug": "linux-macos",
            "link": "#linux-macos",
            "children": []
          },
          {
            "level": 3,
            "title": "Windows",
            "slug": "windows",
            "link": "#windows",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "方法三：手动 CMake 构建",
        "slug": "方法三-手动-cmake-构建",
        "link": "#方法三-手动-cmake-构建",
        "children": []
      },
      {
        "level": 2,
        "title": "依赖库",
        "slug": "依赖库",
        "link": "#依赖库",
        "children": []
      },
      {
        "level": 2,
        "title": "VS Code 配置",
        "slug": "vs-code-配置",
        "link": "#vs-code-配置",
        "children": []
      },
      {
        "level": 2,
        "title": "验证安装",
        "slug": "验证安装",
        "link": "#验证安装",
        "children": []
      },
      {
        "level": 2,
        "title": "故障排除",
        "slug": "故障排除",
        "link": "#故障排除",
        "children": [
          {
            "level": 3,
            "title": "Protobuf 版本冲突",
            "slug": "protobuf-版本冲突",
            "link": "#protobuf-版本冲突",
            "children": []
          },
          {
            "level": 3,
            "title": "vcpkg 下载失败",
            "slug": "vcpkg-下载失败",
            "link": "#vcpkg-下载失败",
            "children": []
          },
          {
            "level": 3,
            "title": "Windows 上找不到 DLL",
            "slug": "windows-上找不到-dll",
            "link": "#windows-上找不到-dll",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/installation.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "插件系统",
    "headers": [
      {
        "level": 2,
        "title": "插件概述",
        "slug": "插件概述",
        "link": "#插件概述",
        "children": [
          {
            "level": 3,
            "title": "插件类型",
            "slug": "插件类型",
            "link": "#插件类型",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "创建插件",
        "slug": "创建插件",
        "link": "#创建插件",
        "children": [
          {
            "level": 3,
            "title": "基础插件结构",
            "slug": "基础插件结构",
            "link": "#基础插件结构",
            "children": []
          },
          {
            "level": 3,
            "title": "插件 CMakeLists.txt",
            "slug": "插件-cmakelists-txt",
            "link": "#插件-cmakelists-txt",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "加载插件",
        "slug": "加载插件",
        "link": "#加载插件",
        "children": [
          {
            "level": 3,
            "title": "使用插件加载器",
            "slug": "使用插件加载器",
            "link": "#使用插件加载器",
            "children": []
          },
          {
            "level": 3,
            "title": "批量加载插件",
            "slug": "批量加载插件",
            "link": "#批量加载插件",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "插件配置",
        "slug": "插件配置",
        "link": "#插件配置",
        "children": [
          {
            "level": 3,
            "title": "配置文件",
            "slug": "配置文件",
            "link": "#配置文件",
            "children": []
          },
          {
            "level": 3,
            "title": "配置加载器",
            "slug": "配置加载器",
            "link": "#配置加载器",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "中间件插件",
        "slug": "中间件插件",
        "link": "#中间件插件",
        "children": [
          {
            "level": 3,
            "title": "请求拦截",
            "slug": "请求拦截",
            "link": "#请求拦截",
            "children": []
          },
          {
            "level": 3,
            "title": "认证中间件",
            "slug": "认证中间件",
            "link": "#认证中间件",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "内置插件",
        "slug": "内置插件",
        "link": "#内置插件",
        "children": [
          {
            "level": 3,
            "title": "限流插件",
            "slug": "限流插件",
            "link": "#限流插件",
            "children": []
          },
          {
            "level": 3,
            "title": "缓存插件",
            "slug": "缓存插件",
            "link": "#缓存插件",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 错误处理",
            "slug": "_1-错误处理",
            "link": "#_1-错误处理",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 资源清理",
            "slug": "_2-资源清理",
            "link": "#_2-资源清理",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 版本兼容性",
            "slug": "_3-版本兼容性",
            "link": "#_3-版本兼容性",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/plugins.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "快速开始",
    "headers": [
      {
        "level": 2,
        "title": "前置准备",
        "slug": "前置准备",
        "link": "#前置准备",
        "children": []
      },
      {
        "level": 2,
        "title": "第一个程序",
        "slug": "第一个程序",
        "link": "#第一个程序",
        "children": [
          {
            "level": 3,
            "title": "1. 创建项目文件",
            "slug": "_1-创建项目文件",
            "link": "#_1-创建项目文件",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 创建 CMakeLists.txt",
            "slug": "_2-创建-cmakelists-txt",
            "link": "#_2-创建-cmakelists-txt",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 构建和运行",
            "slug": "_3-构建和运行",
            "link": "#_3-构建和运行",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "虚拟对象示例",
        "slug": "虚拟对象示例",
        "link": "#虚拟对象示例",
        "children": []
      },
      {
        "level": 2,
        "title": "使用配置文件",
        "slug": "使用配置文件",
        "link": "#使用配置文件",
        "children": [
          {
            "level": 3,
            "title": "创建配置文件 config.json:",
            "slug": "创建配置文件-config-json",
            "link": "#创建配置文件-config-json",
            "children": []
          },
          {
            "level": 3,
            "title": "使用配置加载器：",
            "slug": "使用配置加载器",
            "link": "#使用配置加载器",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "下一步",
        "slug": "下一步",
        "link": "#下一步",
        "children": []
      }
    ],
    "path": "/guide/quick-start.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "测试指南",
    "headers": [
      {
        "level": 2,
        "title": "单元测试",
        "slug": "单元测试",
        "link": "#单元测试",
        "children": [
          {
            "level": 3,
            "title": "使用 Google Test",
            "slug": "使用-google-test",
            "link": "#使用-google-test",
            "children": []
          },
          {
            "level": 3,
            "title": "运行测试",
            "slug": "运行测试",
            "link": "#运行测试",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Mock 测试",
        "slug": "mock-测试",
        "link": "#mock-测试",
        "children": [
          {
            "level": 3,
            "title": "Mock Agent",
            "slug": "mock-agent",
            "link": "#mock-agent",
            "children": []
          },
          {
            "level": 3,
            "title": "函数 Mock",
            "slug": "函数-mock",
            "link": "#函数-mock",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "集成测试",
        "slug": "集成测试",
        "link": "#集成测试",
        "children": [
          {
            "level": 3,
            "title": "测试场景",
            "slug": "测试场景",
            "link": "#测试场景",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "性能测试",
        "slug": "性能测试",
        "link": "#性能测试",
        "children": [
          {
            "level": 3,
            "title": "基准测试",
            "slug": "基准测试",
            "link": "#基准测试",
            "children": []
          },
          {
            "level": 3,
            "title": "运行性能测试",
            "slug": "运行性能测试",
            "link": "#运行性能测试",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "端到端测试",
        "slug": "端到端测试",
        "link": "#端到端测试",
        "children": [
          {
            "level": 3,
            "title": "测试脚本",
            "slug": "测试脚本",
            "link": "#测试脚本",
            "children": []
          },
          {
            "level": 3,
            "title": "Python 测试客户端",
            "slug": "python-测试客户端",
            "link": "#python-测试客户端",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "测试配置",
        "slug": "测试配置",
        "link": "#测试配置",
        "children": [
          {
            "level": 3,
            "title": "测试配置文件",
            "slug": "测试配置文件",
            "link": "#测试配置文件",
            "children": []
          },
          {
            "level": 3,
            "title": "CMake 测试配置",
            "slug": "cmake-测试配置",
            "link": "#cmake-测试配置",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "覆盖率报告",
        "slug": "覆盖率报告",
        "link": "#覆盖率报告",
        "children": [
          {
            "level": 3,
            "title": "启用代码覆盖率",
            "slug": "启用代码覆盖率",
            "link": "#启用代码覆盖率",
            "children": []
          },
          {
            "level": 3,
            "title": "覆盖率目标",
            "slug": "覆盖率目标",
            "link": "#覆盖率目标",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 测试隔离",
            "slug": "_1-测试隔离",
            "link": "#_1-测试隔离",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 清理资源",
            "slug": "_2-清理资源",
            "link": "#_2-清理资源",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 超时控制",
            "slug": "_3-超时控制",
            "link": "#_3-超时控制",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 参数化测试",
            "slug": "_4-参数化测试",
            "link": "#_4-参数化测试",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/testing.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "虚拟对象",
    "headers": [
      {
        "level": 2,
        "title": "什么是虚拟对象",
        "slug": "什么是虚拟对象",
        "link": "#什么是虚拟对象",
        "children": []
      },
      {
        "level": 2,
        "title": "基础用法",
        "slug": "基础用法",
        "link": "#基础用法",
        "children": [
          {
            "level": 3,
            "title": "定义虚拟对象",
            "slug": "定义虚拟对象",
            "link": "#定义虚拟对象",
            "children": []
          },
          {
            "level": 3,
            "title": "注册处理器",
            "slug": "注册处理器",
            "link": "#注册处理器",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "Schema 定义",
        "slug": "schema-定义",
        "link": "#schema-定义",
        "children": [
          {
            "level": 3,
            "title": "定义数据结构",
            "slug": "定义数据结构",
            "link": "#定义数据结构",
            "children": []
          },
          {
            "level": 3,
            "title": "验证输入",
            "slug": "验证输入",
            "link": "#验证输入",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "完整示例",
        "slug": "完整示例",
        "link": "#完整示例",
        "children": [
          {
            "level": 3,
            "title": "钱包虚拟对象",
            "slug": "钱包虚拟对象",
            "link": "#钱包虚拟对象",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "最佳实践",
        "slug": "最佳实践",
        "link": "#最佳实践",
        "children": [
          {
            "level": 3,
            "title": "1. 使用类封装",
            "slug": "_1-使用类封装",
            "link": "#_1-使用类封装",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 统一错误格式",
            "slug": "_2-统一错误格式",
            "link": "#_2-统一错误格式",
            "children": []
          },
          {
            "level": 3,
            "title": "3. 输入验证",
            "slug": "_3-输入验证",
            "link": "#_3-输入验证",
            "children": []
          },
          {
            "level": 3,
            "title": "4. 日志记录",
            "slug": "_4-日志记录",
            "link": "#_4-日志记录",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "高级特性",
        "slug": "高级特性",
        "link": "#高级特性",
        "children": [
          {
            "level": 3,
            "title": "条件操作",
            "slug": "条件操作",
            "link": "#条件操作",
            "children": []
          },
          {
            "level": 3,
            "title": "权限控制",
            "slug": "权限控制",
            "link": "#权限控制",
            "children": []
          },
          {
            "level": 3,
            "title": "生命周期钩子",
            "slug": "生命周期钩子",
            "link": "#生命周期钩子",
            "children": []
          }
        ]
      }
    ],
    "path": "/guide/virtual-objects.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "使用示例",
    "headers": [
      {
        "level": 2,
        "title": "示例列表",
        "slug": "示例列表",
        "link": "#示例列表",
        "children": []
      },
      {
        "level": 2,
        "title": "运行示例",
        "slug": "运行示例",
        "link": "#运行示例",
        "children": [
          {
            "level": 3,
            "title": "构建示例",
            "slug": "构建示例",
            "link": "#构建示例",
            "children": []
          },
          {
            "level": 3,
            "title": "运行示例",
            "slug": "运行示例-1",
            "link": "#运行示例-1",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "前置准备",
        "slug": "前置准备",
        "link": "#前置准备",
        "children": []
      },
      {
        "level": 2,
        "title": "示例配置",
        "slug": "示例配置",
        "link": "#示例配置",
        "children": []
      },
      {
        "level": 2,
        "title": "下一步",
        "slug": "下一步",
        "link": "#下一步",
        "children": []
      }
    ],
    "path": "/examples/",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "基础函数示例",
    "headers": [
      {
        "level": 2,
        "title": "完整代码",
        "slug": "完整代码",
        "link": "#完整代码",
        "children": []
      },
      {
        "level": 2,
        "title": "编译",
        "slug": "编译",
        "link": "#编译",
        "children": [
          {
            "level": 3,
            "title": "CMakeLists.txt",
            "slug": "cmakelists-txt",
            "link": "#cmakelists-txt",
            "children": []
          },
          {
            "level": 3,
            "title": "构建命令",
            "slug": "构建命令",
            "link": "#构建命令",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "运行",
        "slug": "运行",
        "link": "#运行",
        "children": []
      },
      {
        "level": 2,
        "title": "测试",
        "slug": "测试",
        "link": "#测试",
        "children": [
          {
            "level": 3,
            "title": "使用 curl 调用",
            "slug": "使用-curl-调用",
            "link": "#使用-curl-调用",
            "children": []
          },
          {
            "level": 3,
            "title": "预期响应",
            "slug": "预期响应",
            "link": "#预期响应",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "输出示例",
        "slug": "输出示例",
        "link": "#输出示例",
        "children": []
      }
    ],
    "path": "/examples/basic-function.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "综合示例",
    "headers": [
      {
        "level": 2,
        "title": "架构概览",
        "slug": "架构概览",
        "link": "#架构概览",
        "children": []
      },
      {
        "level": 2,
        "title": "完整代码",
        "slug": "完整代码",
        "link": "#完整代码",
        "children": []
      },
      {
        "level": 2,
        "title": "编译",
        "slug": "编译",
        "link": "#编译",
        "children": [
          {
            "level": 3,
            "title": "CMakeLists.txt",
            "slug": "cmakelists-txt",
            "link": "#cmakelists-txt",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "运行测试",
        "slug": "运行测试",
        "link": "#运行测试",
        "children": [
          {
            "level": 3,
            "title": "创建玩家",
            "slug": "创建玩家",
            "link": "#创建玩家",
            "children": []
          },
          {
            "level": 3,
            "title": "创建钱包",
            "slug": "创建钱包",
            "link": "#创建钱包",
            "children": []
          },
          {
            "level": 3,
            "title": "查询玩家",
            "slug": "查询玩家",
            "link": "#查询玩家",
            "children": []
          },
          {
            "level": 3,
            "title": "查询钱包",
            "slug": "查询钱包",
            "link": "#查询钱包",
            "children": []
          },
          {
            "level": 3,
            "title": "转账",
            "slug": "转账",
            "link": "#转账",
            "children": []
          },
          {
            "level": 3,
            "title": "获取服务器信息",
            "slug": "获取服务器信息",
            "link": "#获取服务器信息",
            "children": []
          }
        ]
      }
    ],
    "path": "/examples/comprehensive.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "插件示例",
    "headers": [
      {
        "level": 2,
        "title": "插件代码",
        "slug": "插件代码",
        "link": "#插件代码",
        "children": [
          {
            "level": 3,
            "title": "my_plugin.cpp",
            "slug": "my-plugin-cpp",
            "link": "#my-plugin-cpp",
            "children": []
          },
          {
            "level": 3,
            "title": "插件 CMakeLists.txt",
            "slug": "插件-cmakelists-txt",
            "link": "#插件-cmakelists-txt",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "主程序代码",
        "slug": "主程序代码",
        "link": "#主程序代码",
        "children": [
          {
            "level": 3,
            "title": "main.cpp",
            "slug": "main-cpp",
            "link": "#main-cpp",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "构建",
        "slug": "构建",
        "link": "#构建",
        "children": [
          {
            "level": 3,
            "title": "构建插件",
            "slug": "构建插件",
            "link": "#构建插件",
            "children": []
          },
          {
            "level": 3,
            "title": "构建主程序",
            "slug": "构建主程序",
            "link": "#构建主程序",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "目录结构",
        "slug": "目录结构",
        "link": "#目录结构",
        "children": []
      },
      {
        "level": 2,
        "title": "测试",
        "slug": "测试",
        "link": "#测试",
        "children": []
      },
      {
        "level": 2,
        "title": "插件配置",
        "slug": "插件配置",
        "link": "#插件配置",
        "children": [
          {
            "level": 3,
            "title": "plugin_config.json",
            "slug": "plugin-config-json",
            "link": "#plugin-config-json",
            "children": []
          },
          {
            "level": 3,
            "title": "加载配置",
            "slug": "加载配置",
            "link": "#加载配置",
            "children": []
          }
        ]
      }
    ],
    "path": "/examples/plugin.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "虚拟对象示例",
    "headers": [
      {
        "level": 2,
        "title": "完整代码",
        "slug": "完整代码",
        "link": "#完整代码",
        "children": []
      },
      {
        "level": 2,
        "title": "测试",
        "slug": "测试",
        "link": "#测试",
        "children": [
          {
            "level": 3,
            "title": "创建钱包",
            "slug": "创建钱包",
            "link": "#创建钱包",
            "children": []
          },
          {
            "level": 3,
            "title": "查询钱包",
            "slug": "查询钱包",
            "link": "#查询钱包",
            "children": []
          },
          {
            "level": 3,
            "title": "转账",
            "slug": "转账",
            "link": "#转账",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "扩展",
        "slug": "扩展",
        "link": "#扩展",
        "children": [
          {
            "level": 3,
            "title": "添加新操作",
            "slug": "添加新操作",
            "link": "#添加新操作",
            "children": []
          },
          {
            "level": 3,
            "title": "添加权限检查",
            "slug": "添加权限检查",
            "link": "#添加权限检查",
            "children": []
          }
        ]
      }
    ],
    "path": "/examples/virtual-object.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "Croupier C++ SDK 集成指南",
    "headers": [
      {
        "level": 2,
        "title": "目录",
        "slug": "目录",
        "link": "#目录",
        "children": []
      },
      {
        "level": 2,
        "title": "快速开始",
        "slug": "快速开始",
        "link": "#快速开始",
        "children": [
          {
            "level": 3,
            "title": "1. 安装依赖",
            "slug": "_1-安装依赖",
            "link": "#_1-安装依赖",
            "children": []
          },
          {
            "level": 3,
            "title": "2. 最小集成示例",
            "slug": "_2-最小集成示例",
            "link": "#_2-最小集成示例",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "核心概念",
        "slug": "核心概念",
        "link": "#核心概念",
        "children": [
          {
            "level": 3,
            "title": "客户端 (Client)",
            "slug": "客户端-client",
            "link": "#客户端-client",
            "children": []
          },
          {
            "level": 3,
            "title": "调用器 (Invoker)",
            "slug": "调用器-invoker",
            "link": "#调用器-invoker",
            "children": []
          },
          {
            "level": 3,
            "title": "函数描述符 (FunctionDescriptor)",
            "slug": "函数描述符-functiondescriptor",
            "link": "#函数描述符-functiondescriptor",
            "children": []
          },
          {
            "level": 3,
            "title": "虚拟对象 (VirtualObject)",
            "slug": "虚拟对象-virtualobject",
            "link": "#虚拟对象-virtualobject",
            "children": []
          },
          {
            "level": 3,
            "title": "组件 (Component)",
            "slug": "组件-component",
            "link": "#组件-component",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "完整接口参考",
        "slug": "完整接口参考",
        "link": "#完整接口参考",
        "children": [
          {
            "level": 3,
            "title": "CroupierClient 接口",
            "slug": "croupierclient-接口",
            "link": "#croupierclient-接口",
            "children": []
          },
          {
            "level": 3,
            "title": "CroupierInvoker 接口",
            "slug": "croupierinvoker-接口",
            "link": "#croupierinvoker-接口",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "配置说明",
        "slug": "配置说明",
        "link": "#配置说明",
        "children": [
          {
            "level": 3,
            "title": "ClientConfig 完整参数",
            "slug": "clientconfig-完整参数",
            "link": "#clientconfig-完整参数",
            "children": []
          },
          {
            "level": 3,
            "title": "环境变量覆盖",
            "slug": "环境变量覆盖",
            "link": "#环境变量覆盖",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "生产部署",
        "slug": "生产部署",
        "link": "#生产部署",
        "children": [
          {
            "level": 3,
            "title": "Docker 部署",
            "slug": "docker-部署",
            "link": "#docker-部署",
            "children": []
          },
          {
            "level": 3,
            "title": "Kubernetes 部署",
            "slug": "kubernetes-部署",
            "link": "#kubernetes-部署",
            "children": []
          },
          {
            "level": 3,
            "title": "健康检查端点",
            "slug": "健康检查端点",
            "link": "#健康检查端点",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "故障排查",
        "slug": "故障排查",
        "link": "#故障排查",
        "children": [
          {
            "level": 3,
            "title": "连接失败",
            "slug": "连接失败",
            "link": "#连接失败",
            "children": []
          },
          {
            "level": 3,
            "title": "函数未被调用",
            "slug": "函数未被调用",
            "link": "#函数未被调用",
            "children": []
          },
          {
            "level": 3,
            "title": "性能问题",
            "slug": "性能问题",
            "link": "#性能问题",
            "children": []
          }
        ]
      },
      {
        "level": 2,
        "title": "更多资源",
        "slug": "更多资源",
        "link": "#更多资源",
        "children": []
      }
    ],
    "path": "/guides/integration.html",
    "pathLocale": "/",
    "extraFields": []
  },
  {
    "title": "",
    "headers": [],
    "path": "/404.html",
    "pathLocale": "/",
    "extraFields": []
  }
]
