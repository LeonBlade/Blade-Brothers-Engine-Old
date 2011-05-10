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

#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <vector>

#include "Sprite.h"
#include "Vector2.h"
#include "Font.h"

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

	void setMessage(const char * message, ...);

	// void FadeIn(int ms);
	// void FadeOut(int ms);

	//  these functions are for lua
	int addWindow();
	void setMessage(int index, const char *message);
	void setSize(int index, int x, int y);
	void setPosition(int index, int w, int h);
	void removeWindow(int index);
};

#endif
