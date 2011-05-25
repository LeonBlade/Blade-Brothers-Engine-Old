/*
 *  Event.h
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#include <SDL/SDL.h>

#include "Vector2.h"

class Event
{

public:
	Event();
	virtual ~Event();
	
	virtual void OnEvent(SDL_Event* event);
	
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	
	virtual void OnMouseMove(Vector2 m, Vector2 r, bool left, bool right, bool middle);
	
	virtual void OnMouseWheel(bool up, bool down);
	
	virtual void OnLButtonDown(Vector2 m);
	virtual void OnLButtonUp(Vector2 m);
	
	virtual void OnRButtonDown(Vector2 m);
	virtual void OnRButtonUp(Vector2 m);
	
	virtual void OnMButtonDown(Vector2 m);
	virtual void OnMButtonUp(Vector2 m);
	
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
	
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
	
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 x, Sint16 y);
	
	virtual void OnMinimize();
	virtual void OnRestore();
	virtual void OnResize(int w, int h);
	virtual void OnExpose();
	virtual void OnExit();
	
	virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
	
};

#endif
