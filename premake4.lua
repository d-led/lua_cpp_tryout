_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'lua_cpp_tryout'

make_console_app('lua_cpp_tryout', { 'lua_cpp_tryout.cpp' })

make_cpp11()

