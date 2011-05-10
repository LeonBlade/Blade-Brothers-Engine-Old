/*
 *  Font.h
 *  BBE
 *
 *  Created by James Stine on 9/14/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _FONT_H_
#define _FONT_H_

#include <stdarg.h>

#include "Define.h"
#include "Sprite.h"
#include "FrameRect.h"

class Font
{
private:
	SpriteTexture font;
	Vector2 position;
	char text[1024];
	//char letters[94];
	
public:
	Font();
	~Font();
	
	void OnLoad(const char * filename);
	void SetText(const char * t, ...);
	void SetPosition(Vector2 p);
	void OnRender(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void OnCleanup();
};

#endif
