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
#include <gl.h>
#include <glu.h>
#include <glut.h>
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include "core/Core.h"
#include "entities/Entities.h"
#include "graphics/Graphics.h"

class Game : public Event
{
	
private:
	bool StillBreathing;
	SDL_Surface *gameScreen;
	Player player;
	Map map;
	Window debugWindow;

public:	
	Game();	
	int OnExecute(char *argv[]);
	
public:
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnLoop();
	void OnRender();
	void OnCleanup();
	void OnExit();
};

#endif
