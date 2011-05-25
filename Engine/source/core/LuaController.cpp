#include "core/LuaController.h"

LuaController LuaController::Controller;

LuaController::LuaController()
{
}

bool LuaController::OnInit()
{
	// opening lua
	L = lua_open();
	if (L == NULL)
		return false;

	// initialize standard library for lua
	luaL_openlibs(L);

	// initialize tolua
	tolua_open(L);

	// make entity class accessible from lua
	// tolua_EngineLua_open(L);

	return true;
}
/*
 void LuaController::OnLoop()
 {
 luaL_dofile(L, main_file);
 // get the init function
 lua_getglobal(L, "loop");
 // make sure its a function
 if (!lua_isfunction(L, lua_gettop(L)))
 return;
 // call our init function
 lua_call(L, 0, 0);
 }
 */
