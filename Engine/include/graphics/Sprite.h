/*
 *  Sprite.h
 *  BBE
 *
 *  Created by James Stine on 5/4/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _SPRITE_H_
#define _SPRITE_H_

#define TILE_SIZE 32
#define TILESET_SIZE 256

#ifdef TOOLKIT
    #include <qgl.h>
#else
    //#include <GL/gl.h>
    //#include <GL/glu.h>
    #include <OpenGL/OpenGL.h>
#endif

#include <SDL/SDL.h>
#include <libpng/png.h>
#include <stdio.h>

#include "core/Vector2.h"

struct SpriteTexture 
{
	GLuint texture;
	int width, height;
};

class Sprite
{
	
public:
	Sprite();
	
public:
	static bool OnLoad(const char * filename, SpriteTexture &texture_ptr);
	static bool OnDraw(SpriteTexture texture, Vector2 position, SDL_Rect tile, Vector2 size = Vector2(0, 0));
	
};

#endif
