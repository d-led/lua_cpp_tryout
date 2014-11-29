#include <lua.hpp>
#include <LuaBridge.h>
#include <RefCountedPtr.h>
#include <LuaState.h>
#include <iostream>
#include <map>
#include <string>


class Entity {
    std::map<std::string, int> attributes;

public:
    void attribute(std::string const& key,int value) {
        attributes[key] = value;
    }

    int& attribute(std::string const& key) {
        return attributes[key];
    }
};

class EntityWrapper {
    Entity entity;
public:
    void set_int(std::string const& key,int value) {
        entity.attribute(key,value);
    }

    int get_int(std::string const& key) {
        return entity.attribute(key);
    }
};

void luabridge_bind(lua_State *L) {
 luabridge::getGlobalNamespace(L)
 .beginClass<EntityWrapper>("Entity")
 .addConstructor<void(*)(), RefCountedPtr<EntityWrapper> /* creation policy */ >()
    .addFunction("get_int", &EntityWrapper::get_int)
    .addFunction("set_int", &EntityWrapper::set_int)
 .endClass()
 ; 
}

int main() {
 lua::State state;

 luabridge_bind(state.getState());

 try {
     static const char *test = R"(
local e = Entity()
e:set_int("bla",42)
print(e:get_int("bla"))
)";
  state.doString(test);
 }
 catch (std::exception &e) {
  std::cerr << e.what() << std::endl;
 }
}
