#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <LuaBridge.h>
#include <luabind/luabind.hpp>
#include <string>

class Player {
public:
    void Update() {
        std::cout<<__FUNCTION__<<std::endl;
    }
};

void bind_luabind(lua_State* L) {
    using namespace luabind;

    open(L);

    module(L)
    [
      class_<Player>("Player")
      .def(constructor<>())
      .def("Update",&Player::Update)
    ];
}

int main() {
    lua::State state;

    try {
        bind_luabind(state.getState());
        Player p;
        luabind::globals( state.getState() )["player"] = p;
        state.doString("player:Update()");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
