/*
 *  Animation.h
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <time.h>
#include <SDL/SDL.h>

class Animation
{

private:
	int currentFrame;
	int frameIncrease;
	
private:
	int frameRate;
	long oldTime;
	
public:
	int maxFrames;
	bool oscillate;
	
public:
	Animation();
	void OnAnimate();
	
public:
	void SetFrameRate(int rate);
	void SetCurrentFrame(int frame);
	
	int GetCurrentFrame();
	
};

#endif
