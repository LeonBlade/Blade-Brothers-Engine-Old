/*
 *  Player.h
 *  BBE
 *
 *  Created by James Stine on 5/6/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	
	bool OnLoad(const char *filename, int maxFrames, bool oscillate = false);
	void OnLoop();
	void OnRender();
	void OnCleanup();
	void OnAnimate();
	void OnCollision(Entity *entity);
	void handleKeyboard(SDLKey key, bool down);
};

#endif
