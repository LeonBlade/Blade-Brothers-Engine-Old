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

#ifdef TOOLKIT
    #include <qgl.h>
#else
    //#include <GL/gl.h>
    //#include <GL/glu.h>
    #include <OpenGL/OpenGL.h>
#endif

#include <libpng/png.h>
#include <stdio.h>

#include "Define.h"
#include "Vector2.h"
#include "FrameRect.h"

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
	static bool OnDraw(SpriteTexture texture, Vector2 position, FrameRect tile, Vector2 size = Vector2(0,0));
	
};

#endif
