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

#ifndef CROUPIER_SDK_BINDINGS_LUA_BINDING_H_
#define CROUPIER_SDK_BINDINGS_LUA_BINDING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef __cplusplus
}
#endif

#include <memory>
#include <string>

namespace croupier {
namespace sdk {
namespace lua {

class CroupierClient;

/**
 * @brief Lua binding for Croupier SDK
 *
 * Provides Lua C API bindings for the Croupier C++ SDK.
 * Designed for use with Skynet framework and standalone Lua applications.
 */
class LuaBinding {
public:
    /**
     * @brief Register all Croupier SDK functions to Lua state
     * @param L Lua state pointer
     * @return Number of return values on Lua stack
     *
     * Usage in Lua:
     * local croupier = require("croupier")
     * local client = croupier.Client.new("localhost:50051")
     */
    static int luaopen_croupier(lua_State* L);

    /**
     * @brief Initialize the binding with a client instance
     * @param L Lua state pointer
     * @param client Croupier client instance
     */
    static void initialize(lua_State* L, std::shared_ptr<CroupierClient> client);

private:
    // Client constructor
    static int new_client(lua_State* L);

    // Client methods
    static int client_register_virtual_object(lua_State* L);
    static int client_unregister_virtual_object(lua_State* L);
    static int client_invoke_function(lua_State* L);
    static int client_batch_invoke(lua_State* L);
    static int client_get_virtual_object(lua_State* L);
    static int client_list_virtual_objects(lua_State* L);
    static int client_set_credentials(lua_State* L);
    static int client_close(lua_State* L);

    // Garbage collection for client
    static int client_gc(lua_State* L);

    // Utilities
    static int client_tostring(lua_State* L);

    // Helper to get client pointer from Lua userdata
    static CroupierClient* get_client(lua_State* L, int arg = 1);

    // Push error message to Lua stack
    static int push_error(lua_State* L, const char* msg);

    // Lua metatable names
    static constexpr const char* CLIENT_METATABLE = "croupier.Client";
    static constexpr const char* CLIENT_REGISTRY_KEY = "croupier.client_ptr";
};

} // namespace lua
} // namespace sdk
} // namespace croupier

#endif  // CROUPIER_SDK_BINDINGS_LUA_BINDING_H_
