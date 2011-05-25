/*
 *  Vector2.h
 *  BBE
 *
 *  Created by James Stine on 5/1/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2(void);
	Vector2(float _x, float _y);
	
	virtual ~Vector2(void);
	
	Vector2 Add(float _x, float _y);
	Vector2 Add(Vector2 vector);

	float x, y;
};

#endif
