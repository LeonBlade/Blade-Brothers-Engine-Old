/*
** Lua binding: EngineLua
** Generated automatically by tolua++-1.0.92 on Mon May  9 18:05:40 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_EngineLua_open (lua_State* tolua_S);

#include "Entity.h"
#include "Player.h"
#include "Window.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Entity (lua_State* tolua_S)
{
 Entity* self = (Entity*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Player (lua_State* tolua_S)
{
 Player* self = (Player*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Window (lua_State* tolua_S)
{
 Window* self = (Window*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Entity");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"Window");
}

/* method: new of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_new00
static int tolua_EngineLua_Entity_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Entity* tolua_ret = (Entity*)  Mtolua_new((Entity)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Entity");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_new00_local
static int tolua_EngineLua_Entity_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Entity* tolua_ret = (Entity*)  Mtolua_new((Entity)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Entity");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_delete00
static int tolua_EngineLua_Entity_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEntity of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_addEntity00
static int tolua_EngineLua_Entity_addEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* sprite_name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEntity'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addEntity(sprite_name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_setPosition00
static int tolua_EngineLua_Entity_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(index,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFacing of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_setFacing00
static int tolua_EngineLua_Entity_setFacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int direction = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFacing'", NULL);
#endif
  {
   self->setFacing(index,direction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveTo of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_moveTo00
static int tolua_EngineLua_Entity_moveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveTo'", NULL);
#endif
  {
   self->moveTo(index,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: faceEntity of class  Entity */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Entity_faceEntity00
static int tolua_EngineLua_Entity_faceEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int index_to = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'faceEntity'", NULL);
#endif
  {
   self->faceEntity(index,index_to);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'faceEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Player */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Player_new00
static int tolua_EngineLua_Player_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Player* tolua_ret = (Player*)  Mtolua_new((Player)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Player */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Player_new00_local
static int tolua_EngineLua_Player_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Player* tolua_ret = (Player*)  Mtolua_new((Player)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Player */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Player_delete00
static int tolua_EngineLua_Player_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPlayer of class  Player */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Player_addPlayer00
static int tolua_EngineLua_Player_addPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  const char* sprite_name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPlayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addPlayer(sprite_name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_new00
static int tolua_EngineLua_Window_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Window* tolua_ret = (Window*)  Mtolua_new((Window)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Window");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_new00_local
static int tolua_EngineLua_Window_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Window* tolua_ret = (Window*)  Mtolua_new((Window)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Window");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_delete00
static int tolua_EngineLua_Window_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addWindow of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_addWindow00
static int tolua_EngineLua_Window_addWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addWindow'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addWindow();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMessage of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_setMessage00
static int tolua_EngineLua_Window_setMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMessage'", NULL);
#endif
  {
   self->setMessage(index,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_setSize00
static int tolua_EngineLua_Window_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'", NULL);
#endif
  {
   self->setSize(index,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_setPosition00
static int tolua_EngineLua_Window_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int w = ((int)  tolua_tonumber(tolua_S,3,0));
  int h = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(index,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeWindow of class  Window */
#ifndef TOLUA_DISABLE_tolua_EngineLua_Window_removeWindow00
static int tolua_EngineLua_Window_removeWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeWindow'", NULL);
#endif
  {
   self->removeWindow(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_EngineLua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Entity","Entity","",tolua_collect_Entity);
  #else
  tolua_cclass(tolua_S,"Entity","Entity","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Entity");
   tolua_function(tolua_S,"new",tolua_EngineLua_Entity_new00);
   tolua_function(tolua_S,"new_local",tolua_EngineLua_Entity_new00_local);
   tolua_function(tolua_S,".call",tolua_EngineLua_Entity_new00_local);
   tolua_function(tolua_S,"delete",tolua_EngineLua_Entity_delete00);
   tolua_function(tolua_S,"addEntity",tolua_EngineLua_Entity_addEntity00);
   tolua_function(tolua_S,"setPosition",tolua_EngineLua_Entity_setPosition00);
   tolua_function(tolua_S,"setFacing",tolua_EngineLua_Entity_setFacing00);
   tolua_function(tolua_S,"moveTo",tolua_EngineLua_Entity_moveTo00);
   tolua_function(tolua_S,"faceEntity",tolua_EngineLua_Entity_faceEntity00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Player","Player","",tolua_collect_Player);
  #else
  tolua_cclass(tolua_S,"Player","Player","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"new",tolua_EngineLua_Player_new00);
   tolua_function(tolua_S,"new_local",tolua_EngineLua_Player_new00_local);
   tolua_function(tolua_S,".call",tolua_EngineLua_Player_new00_local);
   tolua_function(tolua_S,"delete",tolua_EngineLua_Player_delete00);
   tolua_function(tolua_S,"addPlayer",tolua_EngineLua_Player_addPlayer00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Window","Window","",tolua_collect_Window);
  #else
  tolua_cclass(tolua_S,"Window","Window","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Window");
   tolua_function(tolua_S,"new",tolua_EngineLua_Window_new00);
   tolua_function(tolua_S,"new_local",tolua_EngineLua_Window_new00_local);
   tolua_function(tolua_S,".call",tolua_EngineLua_Window_new00_local);
   tolua_function(tolua_S,"delete",tolua_EngineLua_Window_delete00);
   tolua_function(tolua_S,"addWindow",tolua_EngineLua_Window_addWindow00);
   tolua_function(tolua_S,"setMessage",tolua_EngineLua_Window_setMessage00);
   tolua_function(tolua_S,"setSize",tolua_EngineLua_Window_setSize00);
   tolua_function(tolua_S,"setPosition",tolua_EngineLua_Window_setPosition00);
   tolua_function(tolua_S,"removeWindow",tolua_EngineLua_Window_removeWindow00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_EngineLua (lua_State* tolua_S) {
 return tolua_EngineLua_open(tolua_S);
};
#endif

