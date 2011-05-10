/*
 *  FPS.h
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL/SDL.h>
#include <time.h>

class FPS
{
	
public:
	static FPS FPSControl;
	
private:
	int oldTime;
	int lastTime;
	float speedFactor;
	int numFrames;
	int frames;
	
public:
	FPS();
	
	void OnLoad();
	
public:
	int GetFPS();
	float GetSpeedFactor();
	
};

#endif
