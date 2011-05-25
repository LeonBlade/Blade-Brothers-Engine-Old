/*
 *  Camera.h
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#define SCREEN_W 640
#define SCREEN_H 480

#include "core/Vector2.h"
#include "entities/Entity.h"

enum 
{
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class Camera
{
	
public:
	static Camera CameraControl;
	
private:
	Vector2 position;
	float *targetX;
	float *targetY;
	SDL_Rect bounds;
	
public:
	int targetMode;
	
public:
	Camera();
	
public:
	void OnMove(Vector2 move);
	
public:
	Vector2 GetPosition();
	float GetX();
	float GetY();
	
public:
	void SetPosition(Vector2 position);
	void SetTarget(float *x, float *y);
	void SetBounds(SDL_Rect bounds);
};

#endif
