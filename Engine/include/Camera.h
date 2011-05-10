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

#include "Define.h"
#include "Vector2.h"
#include "FrameRect.h"

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
};

#endif
