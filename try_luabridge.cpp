#include <lua.hpp>
#include <LuaBridge.h>
#include <RefCountedPtr.h>
#include <LuaState.h>
#include <iostream>

namespace {
void luabridge_bind(lua_State* L) {
	class Test {
	public:
		Test() {
			std::cout<<__FUNCTION__<<std::endl;
		}

		~Test() {
			std::cout<<__FUNCTION__<<std::endl;
		}
	};

	luabridge::getGlobalNamespace(L)
		.beginClass<Test>("Test")
			.addConstructor<void(*)(),RefCountedPtr<Test>>()
		.endClass()
	;
}
}

int main() {
    lua::State state;
    luabridge_bind(state.getState());
    try {
    	state.doString("Test()");
    	state.doString("blabla()");
    } catch (std::exception& e) {
    	std::cerr<<e.what()<<std::endl;
    }
}
