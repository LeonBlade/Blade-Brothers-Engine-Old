/*
 *  main.cpp
 *  BBE
 *
 *  Created by James Stine on 5/1/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include <SDL/SDL.h>
#include "Game.h"

int main(int argc, char *argv[])
{
	Game theGame;
	return theGame.OnExecute(argv);
}
