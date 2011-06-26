/*
 *  Entity.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "entities/Entity.h"

std::vector<Entity*> Entity::EntityStack;

Entity::Entity()
{
	position = Vector2(0, 0);
	tilePosition = Vector2(0, 0);
	size = Vector2(0, 0);
	facing = Down;
	speed = 5;
	moving = false;

	frameRect.x = 0;
	frameRect.y = 0;
	frameRect.w = TILE_SIZE;
	frameRect.h = TILE_SIZE;
}

/*
 * loads in sprites and sets other things up
 */
bool Entity::OnLoad(const char *filename, int maxFrames, bool oscillate)
{
	if (!Sprite::OnLoad(filename, entityTexture))
		return false;

	this->size = size;
	this->animationControl.oscillate = oscillate;
	animationControl.maxFrames = maxFrames;

	return true;
}

/*
 * called each game loop handles movement between tiles
 */
void Entity::OnLoop()
{
	if (this->moving)
	{
		if (facing == Left)
		{
			this->position.x -= this->speed * FPS::FPSControl.GetSpeedFactor();
			if (this->getPosition().x / TILE_SIZE <= this->getTilePosition().x)
			{
				this->position.x = this->getTilePosition().x * TILE_SIZE;
				this->moving = false;
			}
		}
		else if (facing == Up)
		{
			this->position.y -= this->speed * FPS::FPSControl.GetSpeedFactor();
			if (this->getPosition().y / TILE_SIZE <= this->getTilePosition().y)
			{
				this->position.y = this->getTilePosition().y * TILE_SIZE;
				this->moving = false;
			}
		}
		else if (facing == Right)
		{
			this->position.x += this->speed * FPS::FPSControl.GetSpeedFactor();
			if (this->getPosition().x / TILE_SIZE >= this->getTilePosition().x)
			{
				this->position.x = this->getTilePosition().x * TILE_SIZE;
				this->moving = false;
			}
		}
		else if (facing == Down)
		{
			this->position.y += this->speed * FPS::FPSControl.GetSpeedFactor();
			if (this->getPosition().y / TILE_SIZE >= this->getTilePosition().y)
			{
				this->position.y = this->getTilePosition().y * TILE_SIZE;
				this->moving = false;
			}
		}
	}

	this->OnAnimate();
}

#include <math.h>

/*
 * calls render handles animation control for proper frame
 */
void Entity::OnRender()
{
	frameRect.x = this->animationControl.GetCurrentFrame() * TILE_SIZE;
	frameRect.y = facing * TILE_SIZE;
	frameRect.w = TILE_SIZE;
	frameRect.h = TILE_SIZE;

	Vector2 newPosition;
	newPosition.x = position.x - Camera::CameraControl.GetX();
	newPosition.y = position.y - Camera::CameraControl.GetY();

	Sprite::OnDraw(entityTexture, newPosition, frameRect);

	// shadow test
	Vector2 s_pos = newPosition;
	s_pos.y += 32;

	glBindTexture(GL_TEXTURE_2D, entityTexture.texture);

	glColor4f(0.0f, 0.0f, 0.0f, 0.3f);

	glBegin(GL_QUADS);
	{
		float min_x = (float) (frameRect.x) / entityTexture.width;
		float min_y = (float) (frameRect.y) / entityTexture.height;
		float max_x = (float) (frameRect.x + frameRect.w) / entityTexture.width;
		float max_y = (float) (frameRect.y + frameRect.h) / entityTexture.height;

		glTexCoord2f(min_x, max_y);
		glVertex3i(s_pos.x + 16, 				s_pos.y + frameRect.h - 8, 1);
		glTexCoord2f(max_x, max_y);
		glVertex3i(s_pos.x + 16 + frameRect.w, 	s_pos.y + frameRect.h - 8, 1);
		glTexCoord2f(max_x, min_y);
		glVertex3i(s_pos.x + frameRect.w, 	s_pos.y, 1);
		glTexCoord2f(min_x, min_y);
		glVertex3i(s_pos.x, 				s_pos.y, 1);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

/*
 * called when looping through to animate only animates when moving default step is middle
 */
void Entity::OnAnimate()
{
	if (moving)
		this->animationControl.OnAnimate();
	else
		this->animationControl.SetCurrentFrame(StepMiddle);
}

/*
 * determines the location of an entity and faces it
 */
void Entity::faceEntity(Entity *e)
{
	// get the distance from each position
	int distX = e->tilePosition.x - this->position.x;
	int distY = e->tilePosition.y - this->position.y;

	// determine which is closer
	if (abs(distX) <= abs(distY)) // X is closer
	{
		// determine if it's to the left or right
		if (distX < 0) // it's to the left
			this->setFacing(Left);
		else if (distX > 0) // it's to the right
			this->setFacing(Right);
		else
			this->setFacing(Down); // down is default
	}
	else if (abs(distY) <= abs(distX)) // Y is closer
	{
		// determine if it's up or down
		if (distX < 0) // it's up
			this->setFacing(Up);
		else
			// it's down
			this->setFacing(Down); // down is default (also down in this instance)
	}
	else
		this->setFacing(Down); // down is default
}

/*
 * sets the tile position of the entity
 */
void Entity::setPosition(Vector2 p)
{
	this->position.x = p.x * TILE_SIZE;
	this->position.y = p.y * TILE_SIZE;
	this->tilePosition.x = p.x;
	this->tilePosition.y = p.y;
}

void Entity::setPosition(int x, int y)
{
	Vector2 p = Vector2(x, y);
	this->setPosition(p);
}

/*
 * sets the tile position of the entity
 */
void Entity::setMovePosition(Vector2 p)
{
	this->tilePosition.x = p.x;
	this->tilePosition.y = p.y;
}

void Entity::setMovePosition(int x, int y)
{
	Vector2 p = Vector2(x, y);
	this->setMovePosition(p);
}

/*
 * returns the entity pointer the player is facing
 */
Entity* Entity::facingEntity()
{
	Vector2 np = this->tilePosition;

	switch (this->facing)
	{
	case Down:
		np.y++;
		break;
	case Up:
		np.y--;
		break;
	case Left:
		np.x--;
		break;
	case Right:
		np.x++;
		break;
	}

	for (uint i = 0; i < EntityStack.size(); i++)
	{
		if (EntityStack[i]->tilePosition.x == np.x && EntityStack[i]->tilePosition.y == np.y)
			return EntityStack[i];
	}

	return NULL;
}

/*
 * sets the face of the entity to the proper frame
 */
void Entity::setFacing(Facing f)
{
	this->facing = f;
}

/*
 * returns the position of the entity
 */
Vector2 Entity::getPosition()
{
	return this->position;
}

Vector2 Entity::getTilePosition()
{
	return this->tilePosition;
}

/*
 * returns a vector pointer to the position used in camera control
 */
Vector2* Entity::getTarget()
{
	return &this->position;
}

/*
 * returns boolean value based on if you can walk to this position
 */

bool Entity::positionValid(Vector2 newPosition)
{
	bool Return = true;

	Map *map = Map::MapStack[0];
	if (map->getCollision(newPosition.x, newPosition.y) == 1)
		Return = false;

	for (uint i = 0; i < EntityStack.size(); i++)
	{
		if (EntityStack[i]->tilePosition.x == newPosition.x && EntityStack[i]->tilePosition.y == newPosition.y)
			Return = false;
	}

	return Return;
}

/*
 * called when the cleanup proccess is called
 */
void Entity::OnCleanup()
{
	glDeleteTextures(1, &entityTexture.texture);
}

Entity::~Entity()
{
}
