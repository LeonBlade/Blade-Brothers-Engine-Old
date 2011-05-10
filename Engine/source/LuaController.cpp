#include "LuaController.h"

LuaController LuaController::Controller;

LuaController::LuaController() {}
LuaController::~LuaController() {}

bool LuaController::OnInit(const  char *_main_file)
{
	// opening lua
	L = lua_open();
	if (L == NULL)
		return false;

	// seeding the _random_ number generator
	luaL_dostring(L, "math.randomseed(os.time())");

	// initialize standard library for lua
	luaL_openlibs(L);

	// initialize tolua
	tolua_open(L);

	// make entity class accessible from lua
	tolua_EngineLua_open(L);

	// get the start lua script and call init function
	luaL_dofile(L, _main_file);

	// get the init function
	lua_getglobal(L, "init");

	// make sure its a function
	if (!lua_isfunction(L, lua_gettop(L)))
		return false;

	// call our init function
	lua_call(L, 0, 0);

	// copy our main string into our main_lua variable
	bzero(main_file, 256);
	strcpy(main_file, _main_file);

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
