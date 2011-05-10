/*
 *  Player.cpp
 *  BBE
 *
 *  Created by James Stine on 5/6/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "Player.h"

Player::Player() {}

bool Player::OnLoad(const char *filename, int maxFrames, bool oscillate)
{
	if (Entity::OnLoad(filename, maxFrames, oscillate) == false)
		return false;
	
	return true;
}

void Player::OnLoop()
{
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

void Player::OnCollision(Entity* entity)
{
	//entity->canMove = false;
}

int Player::addPlayer(const char *sprite_name)
{
	Player *player = new Player();
	char s_path[256];
	bzero(s_path, 256);
	sprintf(s_path, "../resources/sprites/%s.png", sprite_name);
	if ((player->OnLoad(s_path, 3, true)) == false)
		return -1;
	Entity::EntityStack.push_back(player);
	return Entity::EntityStack.size();
}
