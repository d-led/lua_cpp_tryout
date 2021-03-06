#include <lua.hpp>
#include <LuaBridge.h>
#include <RefCountedPtr.h>
#include <LuaState.h>
#include <iostream>


class Player {
 int x;

public:
 Player() : x(0) { std::cout << __FUNCTION__ << std::endl; }

 ~Player() { std::cout << __FUNCTION__ << std::endl; }

 int get_x() const {
  std::cout << __FUNCTION__ << std::endl;
  return x;
 }

 void set_x(int x_) {
  std::cout << __FUNCTION__ << " " << x_ << std::endl;
  x = x_;
 }

 void jump() { std::cout << __FUNCTION__ << std::endl; }
};

void luabridge_bind(lua_State *L) {
 luabridge::getGlobalNamespace(L)
 .beginClass<Player>("Player")
 .addConstructor<void (*)(), RefCountedPtr<Player> /* creation policy */ >()
 .addProperty("x", &Player::get_x, &Player::set_x)
 .addFunction("jump", &Player::jump)
 .endClass()
 ; 
}

int main() {
 lua::State state;

 luabridge_bind(state.getState());

 try {
  static const char *test =
  "player = Player() \n"
  "player:jump() \n"
  "player.x = player.x + 3"
  ;
  state.doString(test);
 }
 catch (std::exception &e) {
  std::cerr << e.what() << std::endl;
 }
}
