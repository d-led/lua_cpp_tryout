#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <LuaBridge.h>
#include <luabind/luabind.hpp>
#include <luabind/iterator_policy.hpp>
#include <string>
#include <vector>

typedef std::vector<int> a;

struct b : a {
    b(int _) :a(_,_) {}
    b(a const&_) :a(_) {}
    a const& each() const {
        return *this;
    }
};


void bind_luabind(lua_State* L) {
    using namespace luabind;

    open(L);

    module(L) [
        class_<a>("A")
        ,

        class_<b>("B")
            .def(constructor<a const&>())
            .def(constructor<int>())
            .def("each", &b::each, return_stl_iterator)
    ];
}

int main() {
    lua::State state;

    try {
        bind_luabind(state.getState());
        state.doString(R"(

local b = B(42)
for v in b:each() do
    print(v)
end

)");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
