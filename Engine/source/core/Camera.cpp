/*
 *  Camera.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "core/Camera.h"

Camera Camera::CameraControl;

Camera::Camera()
{
	position = Vector2(0, 0);
	targetX = 0;
	targetY = 0;
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = 0;
	bounds.h = 0;

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
		{
			if (*targetX - (SCREEN_W / 2) >= bounds.x && *targetX <= bounds.w - (SCREEN_W / 2))
				return *targetX - (SCREEN_W / 2);
			else if (*targetX - (SCREEN_W / 2) < bounds.x)
				return bounds.x;
			else if (*targetX > bounds.w - (SCREEN_W / 2))
				return bounds.w - SCREEN_W;
		}

		return *targetX;
	}

	return position.x;
}

float Camera::GetY()
{
	if (targetY != 0)
	{
		if (targetMode == TARGET_MODE_CENTER)
		{
			if (*targetY - (SCREEN_H / 2) >= bounds.y && *targetY <= bounds.h - (SCREEN_H / 2))
				return *targetY - (SCREEN_H / 2);
			else if (*targetY - (SCREEN_H / 2) < bounds.y)
				return bounds.y;
			else if (*targetY > bounds.h - (SCREEN_H / 2))
				return bounds.h - SCREEN_H;
		}

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

void Camera::SetBounds(SDL_Rect bounds)
{
	this->bounds = bounds;
}
