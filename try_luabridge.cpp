#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <LuaBridge.h>
#include <luabind/luabind.hpp>
#include <string>

struct a {
    int v;

    a() :v(0){}
    a(int _) :v(_){}
};

struct b : a {
    b(a const&){}
    b(b const&){}
    b(int _) :a(_){}
    void bla(a const&) {
        std::cout << "bla" << std::endl;
    }
    void bla(b const&) {
        std::cout << "bla" << std::endl;
    }
};


void bind_luabind(lua_State* L) {
    using namespace luabind;

    open(L);

    module(L) [
        class_<a>("A")
            .def(constructor<int>())
            .def_readwrite("v",&a::v)
        ,
        class_<b>("B")
            //.def(constructor<a const&>())
            .def(constructor<int>())
            .def("bla", (void (b::*)(a const&))&b::bla)
            .def("bla", (void (b::*)(b const&))&b::bla)
    ];
}

int main() {
    lua::State state;

    try {
        bind_luabind(state.getState());
        state.doString(R"(

local a = A(42)
local b = B(42)
b:bla(a)
b:bla(b)

)");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
