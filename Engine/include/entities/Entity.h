/*
 *  Entity.h
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <unistd.h>

#include <SDL/SDL.h>

#ifdef TOOLKIT
    #include <OpenGL/OpenGL.h>
    #include <qgl.h>
#elif ENGINE
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "core/Core.h"
#include "graphics/Graphics.h"

enum Facing
{
	Left = 2,
	Up = 0,
	Right = 1,
	Down = 3
};

enum Step
{
	StepLeft = 0,
	StepMiddle = 1,
	StepBottom = 2
};

class Entity
{

public:
	static std::vector<Entity*> EntityStack;
	
	Entity();
	virtual ~Entity();

	virtual bool OnLoad(const char *filename, int maxFrames, bool oscillate = false);
	virtual void OnLoop();
	virtual void OnAnimate();
	virtual void OnRender();
	virtual void OnCleanup();

	Entity *facingEntity();
	void faceEntity(Entity *e);
	Vector2 getPosition();
	Vector2 getTilePosition();
	Vector2 *getTarget();
	void setPosition(Vector2 p);
	void setPosition(int x, int y);
	void setMovePosition(Vector2 p);
	void setMovePosition(int x, int y);
	void setFacing(Facing f);

protected:
	Animation animationControl;
	SDL_Rect frameRect;
	SpriteTexture entityTexture;
	Vector2 position;
	Vector2 tilePosition;
	Vector2 size;
	Facing facing;
	int speed;
	bool moving;
	bool movingDown, movingUp, movingRight, movingLeft;

	bool positionValid(Vector2 newPosition);
};

#endif
