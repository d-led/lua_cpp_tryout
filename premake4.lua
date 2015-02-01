include 'premake'

lua = assert(dofile 'premake/recipes/lua.lua')
boost = assert(dofile 'premake/recipes/boost.lua')

make_solution 'lua_cpp_tryout'

platforms 'native'

includedirs { 
	'./LuaBridge-1.0.2',
	'./LuaState/include',
	'./luabind'
}

local function platform_specifics()
	use_standard 'c++0x'
	configuration 'linux'
		buildoptions '-fPIC'
	configuration '*'
end

lua:set_includedirs()
lua:set_libdirs()
boost:set_includedirs()
boost:set_libdirs()
boost:set_defines()
defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

make_static_lib('luabind',{'./luabind/src/*.cpp'})
platform_specifics()

make_console_app('try_luabridge', { 'try_luabridge.cpp' })

lua:set_links()
boost:set_links()

links 'luabind'

platform_specifics()

run_target_after_build()
