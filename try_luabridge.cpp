#include <lua.hpp>
#include <LuaBridge.h>
#include <RefCountedPtr.h>
#include <LuaState.h>
#include <iostream>
#include <memory>


class MyObject {
public:
 void RegisterEvent(const std::string & eventID) {
  std::cout << __FUNCTION__ << " " << eventID << std::endl;
 }

 ~MyObject() {
  std::cout << __FUNCTION__ << std::endl;
 }
};

void luabridge_bind(lua_State *L) {
 luabridge::getGlobalNamespace(L)
  .beginClass<MyObject>("MyObject")
  .addConstructor<void(*)(), RefCountedPtr<MyObject> /* creation policy */ >()
  .addFunction("RegisterEvent", &MyObject::RegisterEvent)
 .endClass()
 ;
}

template <typename T>
void SetGlobal(lua_State* L, const char *name, T value) {
 luabridge::push(L, value);
 lua_setglobal(L, name);
}

int main() {
 lua::State state;

 luabridge_bind(state.getState());

 try {
  static const char *script =
   "function Object_OnLoad(object)\n"
   " object:RegisterEvent('EVENT_CURRENT_HEALTH_CHANGED')\n"
   "end"
  ;
  state.doString(script);

  // shared and automatic lifetime
  auto my_obj = RefCountedPtr<MyObject>(new MyObject);

  // temporary global
  SetGlobal(state.getState(), "my_obj", my_obj);
  state.doString("Object_OnLoad(my_obj); my_obj = nil");
 }
 catch (std::exception &e) {
  std::cerr << e.what() << std::endl;
 }
}
