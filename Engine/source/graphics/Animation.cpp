/*
 *  Animation.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "graphics/Animation.h"

Animation::Animation()
{
	currentFrame	= 0;
	maxFrames	    = 0;
	frameIncrease	= 1;
	frameRate	    = 100;
	oscillate	    = false;
	oldTime			= 0;
}

void Animation::OnAnimate()
{	
	if(oldTime + frameRate > SDL_GetTicks())
		return;

    oldTime = SDL_GetTicks();
    currentFrame += frameIncrease;
    
    // if you want to oscillate back (used in player animations)
    if (oscillate)
    {
		if (frameIncrease > 0) 
		{
			if (currentFrame >= maxFrames - 1)
				frameIncrease = -frameIncrease;
		}
		else
		{
			if (currentFrame <= 0)
				frameIncrease = -frameIncrease;
		}
    }
    else 
    {
		if (currentFrame >= maxFrames - 1)
			currentFrame = 0;
    }
}

void Animation::SetFrameRate(int rate)
{
    frameRate = rate;
}

void Animation::SetCurrentFrame(int frame)
{
    currentFrame = frame;
}

int Animation::GetCurrentFrame()
{
    return currentFrame;
}
