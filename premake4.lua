_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'lua_cpp_tryout'

includedirs { 
	'./LuaBridge-1.0.2',
	'./LuaState/include'
}

local OS = os.get()
local settings = {
	includedirs = {
		linux = {'/usr/include/lua5.1'},
		windows = { [[C:\\luarocks\\2.1\\include]] },
		macosx = {}
	},
	libdirs = {
		linux = {},
		windows = { [[C:\\luarocks\\2.1]] },
		macosx = {}	
	},
	links = {
		linux = { 'lua5.1' },
		windows = { 'lua5.1' },
		macosx = { 'lua' }
	}
}

includedirs { settings.includedirs[OS] }
libdirs { settings.libdirs[OS] }

make_console_app('try_luabridge', { 'try_luabridge.cpp' })

links { settings.links[OS] }

make_cpp11()

run_target_after_build()
