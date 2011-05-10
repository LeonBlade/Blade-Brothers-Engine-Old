#ifndef _LUACONTROLLER_H_
#define _LUACONTROLLER_H_

#include <tolua++.h>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <string>

#include <SDL/SDL.h>

#include "Define.h"
#include "tolua_EngineLua.h"

class LuaController
{
private:
	lua_State *L;
	char main_file[256];

public:
	static LuaController Controller;

	LuaController();
	~LuaController();

	bool OnInit(const char *_main_file);
	void callFunction();

	lua_State* getLuaState();
};

#endif
