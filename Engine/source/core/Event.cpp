/*
 *  Event.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "core/Event.h"

Event::Event()
{
}
Event::~Event()
{
}

void Event::OnEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_ACTIVEEVENT:
		switch (event->active.state)
		{
		case SDL_APPMOUSEFOCUS:
			if (event->active.gain)
				OnMouseFocus();
			else
				OnMouseBlur();
			break;

		case SDL_APPINPUTFOCUS:
			if (event->active.gain)
				OnInputFocus();
			else
				OnInputBlur();
			break;

		case SDL_APPACTIVE:
			if (event->active.gain)
				OnRestore();
			else
				OnMinimize();
			break;

		}
		break;

	case SDL_KEYDOWN:
		OnKeyDown(event->key.keysym.sym, event->key.keysym.mod,
				event->key.keysym.unicode);
		break;

	case SDL_KEYUP:
		OnKeyUp(event->key.keysym.sym, event->key.keysym.mod,
				event->key.keysym.unicode);
		break;

	case SDL_MOUSEMOTION:
		OnMouseMove(Vector2(event->motion.x, event->motion.y),
				Vector2(event->motion.xrel, event->motion.yrel),
				(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
				(event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
				(event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			OnLButtonDown(Vector2(event->button.x, event->button.y));
			break;
		case SDL_BUTTON_RIGHT:
			OnRButtonDown(Vector2(event->button.x, event->button.y));
			break;
		case SDL_BUTTON_MIDDLE:
			OnMButtonDown(Vector2(event->button.x, event->button.y));
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			OnLButtonUp(Vector2(event->button.x, event->button.y));
			break;
		case SDL_BUTTON_RIGHT:
			OnRButtonUp(Vector2(event->button.x, event->button.y));
			break;
		case SDL_BUTTON_MIDDLE:
			OnMButtonUp(Vector2(event->button.x, event->button.y));
			break;
		}
		break;

	case SDL_JOYAXISMOTION:
		OnJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
		break;

	case SDL_JOYBALLMOTION:
		OnJoyBall(event->jball.which, event->jball.ball, event->jball.xrel,
				event->jball.yrel);
		break;

	case SDL_JOYHATMOTION:
		OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
		break;

	case SDL_JOYBUTTONDOWN:
		OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
		break;

	case SDL_JOYBUTTONUP:
		OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
		break;

	case SDL_QUIT:
		OnExit();
		break;

	case SDL_SYSWMEVENT:
		// Ignore lol
		break;

	case SDL_VIDEORESIZE:
		OnResize(event->resize.w, event->resize.h);
		break;

	case SDL_VIDEOEXPOSE:
		OnExpose();
		break;

	default:
		OnUser(event->user.type, event->user.code, event->user.data1,
				event->user.data2);
		break;

	}
}

void Event::OnInputFocus()
{
	//Pure virtual, do nothing
}

void Event::OnInputBlur()
{
	//Pure virtual, do nothing
}

void Event::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//Pure virtual, do nothing
}

void Event::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//Pure virtual, do nothing
}

void Event::OnMouseFocus()
{
	//Pure virtual, do nothing
}

void Event::OnMouseBlur()
{
	//Pure virtual, do nothing
}

void Event::OnMouseMove(Vector2 m, Vector2 r, bool left, bool right,
		bool middle)
{
	//Pure virtual, do nothing
}

void Event::OnMouseWheel(bool up, bool down)
{
	//Pure virtual, do nothing
}

void Event::OnLButtonDown(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnLButtonUp(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnRButtonDown(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnRButtonUp(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnMButtonDown(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnMButtonUp(Vector2 m)
{
	//Pure virtual, do nothing
}

void Event::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	//Pure virtual, do nothing
}

void Event::OnJoyButtonDown(Uint8 which, Uint8 button)
{
	//Pure virtual, do nothing
}

void Event::OnJoyButtonUp(Uint8 which, Uint8 button)
{
	//Pure virtual, do nothing
}

void Event::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
	//Pure virtual, do nothing
}

void Event::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
	//Pure virtual, do nothing
}

void Event::OnMinimize()
{
	//Pure virtual, do nothing
}

void Event::OnRestore()
{
	//Pure virtual, do nothing
}

void Event::OnResize(int w, int h)
{
	//Pure virtual, do nothing
}

void Event::OnExpose()
{
	//Pure virtual, do nothing
}

void Event::OnExit()
{
	//Pure virtual, do nothing
}

void Event::OnUser(Uint8 type, int code, void* data1, void* data2)
{
	//Pure virtual, do nothing
}

