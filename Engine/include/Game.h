/*
 *  Game.h
 *  BBE
 *
 *  Created by James Stine on 5/4/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
//#include <SDL_image/SDL_image.h>
#include <OpenGL/OpenGL.h>
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include "Define.h"

#include "Event.h"
#include "Sprite.h"
#include "Animation.h"
#include "Map.h"
#include "Entity.h"
#include "Player.h"
#include "Camera.h"
#include "FPS.h"
#include "Font.h"
#include "Window.h"
#include "LuaController.h"

#include "tolua_EngineLua.h"

class Game : public Event
{
	
private:
	bool StillBreathing;
	SDL_Surface *gameScreen;
	char *mapName;
	Map map1;

public:	
	Game();	
	int OnExecute(char *argv[]);
	
public:
	bool OnInit();

	void OnEvent(SDL_Event* event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnResize(int w, int h);
	void OnExit();

	void OnLoop();

	void OnRender();

	void OnCleanup();
	
};

#endif
