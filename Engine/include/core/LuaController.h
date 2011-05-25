#ifndef _LUACONTROLLER_H_
#define _LUACONTROLLER_H_

#include <tolua++.h>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <string>

#include <SDL/SDL.h>

class LuaController
{
private:
	lua_State *L;

public:
	static LuaController Controller;

	LuaController();
	bool OnInit();
	void CallFunction(const char *script, ...);
	lua_State *getLuaState();
};

#endif
