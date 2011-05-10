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

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include "Define.h"

#include "Animation.h"
#include "Sprite.h"
#include "FPS.h"
#include "Camera.h"
#include "Map.h"
#include "FrameRect.h"

enum
{
	ENTITY_TYPE_PLAYER = 0,
	ENTITY_TYPE_NORMAL
};

enum PlayerStates
{
	Idle,
	Moving
};

class Entity
{

public:
	static std::vector<Entity*> EntityStack;
	static Entity EntityControl;
	
protected:
	Animation animationControl;
	FrameRect frameRect;
	int facing, nextFacing;
	SpriteTexture entityTexture;
	
public:
	bool movingUp, movingDown, movingLeft, movingRight;
	bool arivedX, arivedY;
	bool sprinting;	
	int runSpeed;
	bool moving;
	PlayerStates state;
	char scriptPath[256];
	unsigned int time;

public:
	Vector2 position;
	Vector2 tilePosition;
	Vector2 size;
	int entityType;
	
protected:
	Vector2 speed;
	Vector2 accel;
	
public:
	Entity();
	virtual ~Entity();
	
public:
	void SortEntities();
	
public:
	virtual bool OnLoad(const char *filename, int maxFrames, bool oscillate = false);
	virtual void OnLoop();
	virtual void OnRender();
	virtual void OnCleanup();
	virtual void OnAnimate();
	virtual void OnCollision(Entity *entity);

	void setScript(const char *path);
	void OnMove(int move, bool _state);

	void onTalk();

	void setFacing(int direction);
	void setPosition(int x, int y);
	Entity* facingEntity();
	void faceEntity(Entity *e);

	// lua functions
	int addEntity(const char *sprite_name);
	void setPosition(int index, int x, int y);
	void setFacing(int index, int direction);
	void moveTo(int index, int x, int y);
	void faceEntity(int index, int index_to);

private:
	bool Collides(Vector2 spot);
	bool PositionValid(Vector2 newPosition);
	bool PositionValidTile(MapTile *tile);
	bool PositionValidEntity(Entity *entity, Vector2 newPosition);
};

class EntityCollision
{

public:
	static std::vector<EntityCollision> EntityCollisionStack;

public:
	Entity *EntityA;
	Entity *EntityB;

public:
	EntityCollision();

};

#endif
