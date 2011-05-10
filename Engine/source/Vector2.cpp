/*
 *  Vector2.cpp
 *  BBE
 *
 *  Created by James Stine on 5/1/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;

	ZERO = Vector2(0,0);
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

// Adding vectors
Vector2 Vector2::Add(float _x, float _y)
{
	Vector2 temp;
	temp.x = x + _x;
	temp.y = y + _y;
	
	return temp;
}
Vector2 Vector2::Add(Vector2 vector)
{
	Vector2 temp;
	temp.x = x + vector.x;
	temp.y = y + vector.y;
	
	return temp;
}

Vector2::~Vector2() {}
