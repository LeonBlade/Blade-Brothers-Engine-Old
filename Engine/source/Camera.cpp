/*
 *  Camera.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "Camera.h"

Camera Camera::CameraControl;

Camera::Camera()
{
	position = Vector2(0,0);
	targetX = 0;
	targetY = 0;
	
	targetMode = TARGET_MODE_NORMAL;
}

void Camera::OnMove(Vector2 move)
{
	position = position.Add(move);
}

float Camera::GetX()
{
	if (targetX != 0)
	{
		if (targetMode == TARGET_MODE_CENTER)
			return *targetX - (SCREEN_W / 2);
		
		return *targetX;
	}
	
	return position.x;
}

float Camera::GetY()
{
	if (targetY != 0)
	{
		if (targetMode == TARGET_MODE_CENTER)
			return *targetY - (SCREEN_H / 2);
		
		return *targetY;
	}
	
	return position.y;
}

void Camera::SetPosition(Vector2 position)
{
	this->position = position;
}

void Camera::SetTarget(float *x, float *y)
{
	this->targetX = x;
	this->targetY = y;
}
