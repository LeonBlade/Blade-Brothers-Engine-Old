/*
 *  Window.h
 *  BBE
 *
 *  Created by James Stine on 10/9/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _WINDOW_H_
#define _WINDOW_H_

#define WINDOW_TILE_SIZE 8

#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <vector>

#include "core/Vector2.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class Window
{	
public:
	static std::vector<Window*> WindowStack;
	SpriteTexture windowTexture;
	Vector2 position, size;
	char *text;
	float alpha;
	Font font;

public:
	Window();
	~Window();
	
	bool OnLoad(const char *filename);
	void OnRender();
	void OnCleanup();

	void setPosition(int x, int y);
	void setSize(int w, int h);

	void setMessage(const char * message);
};

#endif
