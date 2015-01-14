#include <lua.hpp>
#include <LuaState.h>
#include <iostream>
#include <map>
#include <string>


int main() {
 lua::State state;

 try {
     static const char *test = R"(
print'test'
)";
  state.doString(test);
 }
 catch (std::exception &e) {
  std::cerr << e.what() << std::endl;
 }
}
