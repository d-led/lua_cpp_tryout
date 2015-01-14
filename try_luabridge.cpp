#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <map>
#include <string>

int call__(lua_State* L) {
    int count = lua_gettop(L);
    lua_pushstring(L, "n");
    lua_gettable(L, 1);
    std::cout 
        << (int)lua_tonumber(L, -1) 
        << ", " << (int)lua_tonumber(L, 2)
        << ", " << (int)lua_tonumber(L, 3)
        << std::endl;
    return 0;
}

static void set(lua_State *L, int table_index, const char *key) {
    lua_pushstring(L, key);
    lua_insert(L, -2);
    lua_settable(L, table_index);
}

int main() {
    lua::State state;

    try {
        state.doString("t={n=42}");

        lua_State* L(state.getState());

        lua_getglobal(L, "t");
        int t = lua_gettop(L);

        luaL_newmetatable(L, "mt");
        lua_pushstring(L, "__call");
        lua_pushcfunction(L, call__);
        lua_settable(L, -3);
        lua_setmetatable(L, t);
        lua_settop(L, 0);

        static const char *test = R"(
t(43,44)
)";
        state.doString(test);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
