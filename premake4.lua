_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'lua_cpp_tryout'

includedirs { 
	'./LuaBridge-1.0.2',
	'./luabind'
}

local OS = os.get()
local settings = {
	includedirs = {
		linux = {'/usr/include/lua5.1'},
		windows = {},
		macosx = {}
	},
	links = {
		linux = { 'lua5.1' },
		windows = { 'lua5.1' },
		macosx = { 'lua' }
	}
}

includedirs { settings.includedirs[OS] }

make_static_lib('luabind',{'./luabind/src/*.cpp'})

make_console_app('try_luabridge', { 'try_luabridge.cpp' })

links { settings.links[OS] }

make_cpp11()
