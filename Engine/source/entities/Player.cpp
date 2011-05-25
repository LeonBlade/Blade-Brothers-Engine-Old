/*
 *  Player.cpp
 *  BBE
 *
 *  Created by James Stine on 5/6/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "entities/Player.h"

Player::Player()
{
	movingLeft = false;
	movingRight = false;
	movingUp = false;
	movingDown = false;
}

bool Player::OnLoad(const char *filename, int maxFrames, bool oscillate)
{
	if (Entity::OnLoad(filename, maxFrames, oscillate) == false)
		return false;
	
	return true;
}

void Player::OnLoop()
{
	if (!this->moving)
	{
		Vector2 p = this->getTilePosition();

		if (movingLeft)
		{
			this->setFacing(Left);
			p.x--;
		}
		else if (movingUp)
		{
			this->setFacing(Up);
			p.y--;
		}
		else if (movingRight)
		{
			this->setFacing(Right);
			p.x++;
		}
		else if (movingDown)
		{
			this->setFacing(Down);
			p.y++;
		}

		if (this->positionValid(p))
		{
			this->setMovePosition(p);
			this->moving = true;
		}
	}

	Entity::OnLoop();
}

void Player::OnRender()
{
	Entity::OnRender();
}

void Player::OnCleanup()
{
	Entity::OnCleanup();
}

void Player::OnAnimate()
{
	Entity::OnAnimate();
}

void Player::OnCollision(Entity *entity)
{
	//entity->canMove = false;
}

void Player::handleKeyboard(SDLKey key, bool down)
{
	if (key == SDLK_LEFT)
		movingLeft = down;
	else if (key == SDLK_UP)
		movingUp = down;
	else if (key == SDLK_RIGHT)
		movingRight = down;
	else if (key == SDLK_DOWN)
		movingDown = down;
}

Player::~Player() {}
