// Copyright 2025 Croupier Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bindings/lua_binding.h"
#include "croupier/sdk/croupier_client.h"

#include <cstring>
#include <new>

namespace croupier {
namespace sdk {
namespace lua {

// ============================================================================
// Lua C API Implementation
// ============================================================================

int LuaBinding::luaopen_croupier(lua_State* L) {
    // Create client metatable
    luaL_newmetatable(L, CLIENT_METATABLE);

    // Set metatable.__index = metatable (for method lookup)
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    // Register methods
    static const luaL_Reg client_methods[] = {
        {"register_virtual_object", client_register_virtual_object},
        {"unregister_virtual_object", client_unregister_virtual_object},
        {"invoke_function", client_invoke_function},
        {"batch_invoke", client_batch_invoke},
        {"get_virtual_object", client_get_virtual_object},
        {"list_virtual_objects", client_list_virtual_objects},
        {"set_credentials", client_set_credentials},
        {"close", client_close},
        {"__gc", client_gc},
        {"__tostring", client_tostring},
        {nullptr, nullptr}
    };
    luaL_setfuncs(L, client_methods, 0);
    lua_pop(L, 1);

    // Create main module table
    lua_newtable(L);

    // Add Client constructor
    lua_newtable(L);
    lua_pushcfunction(L, new_client);
    lua_setfield(L, -2, "new");
    lua_setfield(L, -2, "Client");

    // Add version info
    lua_pushliteral(L, CROUPIER_SDK_VERSION);
    lua_setfield(L, -2, "_VERSION");

    return 1;  // Return module table
}

CroupierClient* LuaBinding::get_client(lua_State* L, int arg) {
    void* ud = luaL_checkudata(L, arg, CLIENT_METATABLE);
    if (!ud) {
        luaL_argerror(L, arg, "expected croupier.Client");
        return nullptr;
    }
    CroupierClient** ptr = static_cast<CroupierClient**>(ud);
    return *ptr;
}

int LuaBinding::push_error(lua_State* L, const char* msg) {
    lua_pushnil(L);
    lua_pushstring(L, msg);
    return 2;  // nil, error_msg
}

int LuaBinding::new_client(lua_State* L) {
    const char* server_address = luaL_optstring(L, 1, "localhost:50051");

    // Create client userdata
    CroupierClient** ud = static_cast<CroupierClient**>(
        lua_newuserdata(L, sizeof(CroupierClient*))
    );

    try {
        *ud = new CroupierClient(server_address);
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }

    // Set metatable
    luaL_getmetatable(L, CLIENT_METATABLE);
    lua_setmetatable(L, -2);

    return 1;  // Return client userdata
}

int LuaBinding::client_register_virtual_object(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    // Arguments: client, vo_id, class_id, properties (table)
    const char* vo_id = luaL_checkstring(L, 2);
    const char* class_id = luaL_checkstring(L, 3);

    // Parse properties table (optional)
    std::string properties;
    if (lua_istable(L, 4)) {
        lua_getglobal(L, "cjson");
        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "encode");
            lua_pushvalue(L, 4);  // properties table
            lua_call(L, 1, 1);
            const char* json = lua_tostring(L, -1);
            if (json) {
                properties = json;
            }
            lua_pop(L, 1);  // pop json result
        }
        lua_pop(L, 1);  // pop cjson
    }

    try {
        bool success = client->RegisterVirtualObject(vo_id, class_id, properties);
        lua_pushboolean(L, success);
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_unregister_virtual_object(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    const char* vo_id = luaL_checkstring(L, 2);

    try {
        bool success = client->UnregisterVirtualObject(vo_id);
        lua_pushboolean(L, success);
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_invoke_function(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    // Arguments: client, vo_id, function_name, args (table)
    const char* vo_id = luaL_checkstring(L, 2);
    const char* function_name = luaL_checkstring(L, 3);
    std::string args;

    if (lua_istable(L, 4)) {
        lua_getglobal(L, "cjson");
        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "encode");
            lua_pushvalue(L, 4);
            lua_call(L, 1, 1);
            const char* json = lua_tostring(L, -1);
            if (json) {
                args = json;
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    try {
        std::string result = client->InvokeFunction(vo_id, function_name, args);
        lua_pushstring(L, result.c_str());
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_batch_invoke(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    // Arguments: client, requests (array of tables)
    std::vector<std::tuple<std::string, std::string, std::string>> requests;

    if (lua_istable(L, 2)) {
        // Parse array of request tables
        lua_pushnil(L);  // first key
        while (lua_next(L, 2) != 0) {
            if (lua_istable(L, -1)) {
                // Get vo_id
                lua_getfield(L, -1, "vo_id");
                const char* vo_id = lua_tostring(L, -1);
                lua_pop(L, 1);

                // Get function_name
                lua_getfield(L, -1, "function_name");
                const char* func_name = lua_tostring(L, -1);
                lua_pop(L, 1);

                // Get args (optional)
                lua_getfield(L, -1, "args");
                const char* args_str = lua_tostring(L, -1);
                std::string args = args_str ? args_str : "{}";
                lua_pop(L, 1);

                if (vo_id && func_name) {
                    requests.emplace_back(vo_id, func_name, args);
                }
            }
            lua_pop(L, 1);  // pop value, keep key
        }
    }

    try {
        auto results = client->BatchInvoke(requests);

        // Return results as Lua table
        lua_newtable(L);
        for (size_t i = 0; i < results.size(); ++i) {
            lua_pushinteger(L, i + 1);
            lua_pushstring(L, results[i].c_str());
            lua_settable(L, -3);
        }
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_get_virtual_object(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    const char* vo_id = luaL_checkstring(L, 2);

    try {
        std::string vo_data = client->GetVirtualObject(vo_id);

        // Try to parse as JSON and return as table
        lua_getglobal(L, "cjson");
        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "decode");
            lua_pushstring(L, vo_data.c_str());
            lua_call(L, 1, 1);
            lua_remove(L, -2);  // remove cjson, keep result
            return 1;
        }
        lua_pop(L, 1);

        // Fallback: return as string
        lua_pushstring(L, vo_data.c_str());
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_list_virtual_objects(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    const char* class_id = luaL_optstring(L, 2, nullptr);

    try {
        std::vector<std::string> vos = client->ListVirtualObjects(class_id);

        // Return as Lua table
        lua_newtable(L);
        for (size_t i = 0; i < vos.size(); ++i) {
            lua_pushinteger(L, i + 1);
            lua_pushstring(L, vos[i].c_str());
            lua_settable(L, -3);
        }
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_set_credentials(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    size_t token_len = 0;
    const char* token = luaL_tolstring(L, 2, &token_len);
    if (!token) {
        return push_error(L, "invalid token");
    }

    try {
        client->SetCredentials(std::string(token, token_len));
        lua_pushboolean(L, true);
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_close(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (!client) {
        return push_error(L, "invalid client");
    }

    try {
        client->Close();
        lua_pushboolean(L, true);
        return 1;
    } catch (const std::exception& e) {
        // Intentionally suppress exception - return error to Lua instead
        (void)e;
        return push_error(L, e.what());
    }
}

int LuaBinding::client_gc(lua_State* L) {
    CroupierClient** ud = static_cast<CroupierClient**>(
        luaL_checkudata(L, 1, CLIENT_METATABLE)
    );
    if (*ud) {
        delete *ud;
        *ud = nullptr;
    }
    return 0;
}

int LuaBinding::client_tostring(lua_State* L) {
    CroupierClient* client = get_client(L, 1);
    if (client) {
        lua_pushfstring(L, "croupier.Client: %p", static_cast<void*>(client));
    } else {
        lua_pushliteral(L, "croupier.Client (closed)");
    }
    return 1;
}

} // namespace lua
} // namespace sdk
} // namespace croupier
