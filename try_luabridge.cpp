#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <LuaBridge.h>
#include <luabind/luabind.hpp>
#include <string>

void bridge() {
    std::cout << "hello from LuaBridge" << std::endl;
}

void bind() {
    std::cout << "hello from LuaBind" << std::endl;
}

void bind_luabridge(lua_State* L) {
    luabridge::getGlobalNamespace(L)
        .addFunction("bridge", bridge)
    ;
}

void bind_luabind(lua_State* L) {
    using namespace luabind;

    open(L);

    module(L) [
        def("bind",bind)
    ];
}

int main() {
    lua::State state;

    try {
        bind_luabridge(state.getState());
        bind_luabind(state.getState());
        state.doString("bridge() bind()");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
