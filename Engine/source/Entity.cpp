/*
 *  Entity.cpp
 *  BBE
 *
 *  Created by James Stine on 5/5/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "Entity.h"

std::vector<Entity*> Entity::EntityStack;
std::vector<EntityCollision> EntityCollision::EntityCollisionStack;

Entity Entity::EntityControl;

struct EntitySort
{
	bool operator()(Entity *entity1, Entity *entity2)
	{
		return (entity1->position.y < entity2->position.y);
	}
} SortY;

EntityCollision::EntityCollision()
{
	EntityA = NULL;
	EntityB = NULL;
}

Entity::Entity()
{
	position = Vector2(0, 0);
	tilePosition = Vector2(0, 0);
	size = Vector2(0, 0);

	entityType = ENTITY_TYPE_NORMAL;

	speed = Vector2(5, 5);
	accel = Vector2(0, 0);

	moving = 0;
	runSpeed = 3;
	sprinting = false;

	frameRect.x = 0;
	frameRect.y = 0;
	frameRect.w = TILE_SIZE;
	frameRect.h = TILE_SIZE;

	facing = ENTITY_FACE_DOWN;
	nextFacing = ENTITY_FACE_DOWN;

	state = Idle;
	movingUp = false;
	movingDown = false;
	movingLeft = false;
	movingRight = false;
	arivedX = false;
	arivedY = false;
	time = 0;

	bzero(scriptPath, 256);
}

Entity::~Entity() {}

bool Entity::OnLoad(const char *filename, int maxFrames, bool oscillate)
{
	if (!Sprite::OnLoad(filename, entityTexture))
		return false;

	this->size = size;
	this->animationControl.oscillate = oscillate;
	animationControl.maxFrames = maxFrames;

	return true;
}

void Entity::setScript(const char *path)
{
	bzero(scriptPath, 256);
	strcpy(scriptPath, path);
}

void Entity::OnLoop()
{
	if (state == Idle)
	{
		Vector2 t = tilePosition;

		if (movingDown)
		{
			state = Moving;
			t.y++;
		}
		if (movingUp)
		{
			state = Moving;
			t.y--;
		}
		if (movingLeft)
		{
			state = Moving;
			t.x--;
		}
		if (movingRight)
		{
			state = Moving;
			t.x++;
		}

		if (this->PositionValid(t))
			tilePosition = t;
	}

	if (state == Moving)
	{
		bool arivedX = false;
		bool arivedY = false;

		if (this->position.x < this->tilePosition.x * TILE_SIZE)
		{
			this->facing = ENTITY_FACE_RIGHT;
			this->position.x += this->speed.x * FPS::FPSControl.GetSpeedFactor();
			if (this->position.x >= this->tilePosition.x * TILE_SIZE)
				arivedX = true;
		}
		else if (this->position.x > this->tilePosition.x * TILE_SIZE)
		{
			this->facing = ENTITY_FACE_LEFT;
			this->position.x -= this->speed.x * FPS::FPSControl.GetSpeedFactor();
			if (this->position.x <= this->tilePosition.x * TILE_SIZE)
				arivedX = true;
		}
		else
			arivedX = true;

		if (this->position.y < this->tilePosition.y * TILE_SIZE)
		{
			this->facing = ENTITY_FACE_DOWN;
			this->position.y += this->speed.y * FPS::FPSControl.GetSpeedFactor();
			if (this->position.y >= this->tilePosition.y * TILE_SIZE)
				arivedY = true;
		}
		else if (this->position.y > this->tilePosition.y * TILE_SIZE)
		{
			this->facing = ENTITY_FACE_UP;
			this->position.y -= this->speed.y * FPS::FPSControl.GetSpeedFactor();
			if (this->position.y <= this->tilePosition.y * TILE_SIZE)
				arivedY = true;
		}
		else
			arivedY = true;

		if (arivedX && arivedY)
		{
			state = Idle;

			this->position.x = this->tilePosition.x * TILE_SIZE;
			this->position.y = this->tilePosition.y * TILE_SIZE;
		}
	}

	this->OnAnimate();
}

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
}

void Entity::OnAnimate()
{
	if (state == Moving)
		this->animationControl.OnAnimate();
	else
		this->animationControl.SetCurrentFrame(ENTITY_STEP_MIDDLE);
}

void Entity::OnMove(int move, bool _state)
{
	movingLeft = false;
	movingUp = false;
	movingDown = false;
	movingRight = false;

	switch (move)
	{
	case ENTITY_FACE_DOWN:
		movingDown = _state;
		break;
	case ENTITY_FACE_UP:
		movingUp = _state;
		break;
	case ENTITY_FACE_LEFT:
		movingLeft = _state;
		break;
	case ENTITY_FACE_RIGHT:
		movingRight = _state;
		break;
	}

	facing = move;
}

void Entity::onTalk()
{
	/*
	// call the file
	luaL_dofile(L, this->scriptPath);
	// get the talk function
	lua_getglobal(L, "talk");
	// make sure its a function
	if (!lua_isfunction(L, lua_gettop(L)))
		return;

	// call our talk function
	lua_call(L, 0, 0);
	*/
}

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
			this->setFacing(ENTITY_FACE_LEFT);
		else if (distX > 0) // it's to the right
			this->setFacing(ENTITY_FACE_RIGHT);
		else
			this->setFacing(ENTITY_FACE_DOWN); // down is default
	}
	else if (abs(distY) <= abs(distX)) // Y is closer
	{
		// determine if it's up or down
		if (distX < 0) // it's up
			this->setFacing(ENTITY_FACE_UP);
		else // it's down
			this->setFacing(ENTITY_FACE_DOWN); // down is default (also down in this instance)
	}
	else
		this->setFacing(ENTITY_FACE_DOWN); // down is default
}

void Entity::moveTo(int index, int x, int y)
{
	Vector2 mtp = this->tilePosition;
	mtp.x += x;
	mtp.y += y;

	Vector2 cp = this->tilePosition;

	int dx, dy;

	if (cp.x < mtp.x)
		dx = 1;
	else
		dx = -1;
	if (cp.y < mtp.y)
		dy = 1;
	else
		dy = -1;

	while (mtp.x != cp.x)
	{
		cp.x += dx;
		if (!this->PositionValid(cp))
		{
			cp.x -= dx;
			break;
		}
	}
	while (mtp.y != cp.y)
	{
		cp.y += dy;
		if (!this->PositionValid(cp))
		{
			cp.y -= dy;
			break;
		}
	}

	this->tilePosition = cp;

	state = Moving;
}

void Entity::setPosition(int x, int y)
{
	this->position.x = x * TILE_SIZE;
	this->position.y = y * TILE_SIZE;
	this->tilePosition.x = x;
	this->tilePosition.y = y;
}

void Entity::OnCollision(Entity* entity) {}

void Entity::setFacing(int direction)
{
	this->facing = direction;
}

Entity* Entity::facingEntity()
{
	Vector2 np = this->tilePosition;

	switch (this->facing)
	{
	case ENTITY_FACE_DOWN:
		np.y++;
		break;
	case ENTITY_FACE_UP:
		np.y--;
		break;
	case ENTITY_FACE_LEFT:
		np.x--;
		break;
	case ENTITY_FACE_RIGHT:
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

bool Entity::PositionValid(Vector2 newPosition)
{
	bool Return = true;

	Map *map = Map::MapStack[0];
	int tile = map->GetTile(newPosition.x, newPosition.y, MAP_LAYER_COLLISION);
	if (tile == MAP_TILE_SOLID)
		Return = false;

	for (uint i = 0; i < EntityStack.size(); i++)
	{
		if (EntityStack[i]->tilePosition.x == newPosition.x	&& EntityStack[i]->tilePosition.y == newPosition.y)
			Return = false;
	}

	return Return;
}

bool Entity::Collides(Vector2 spot)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = position.x + 2;
	left2 = spot.x + 4;

	right1 = left1 + size.x - 1 - 4;
	right2 = spot.x + TILE_SIZE - 1 - 2;

	top1 = position.y + 4;
	top2 = spot.y + 4;

	bottom1 = top1 + size.y - 1 - 10;
	bottom2 = spot.y + TILE_SIZE - 1 - 2;

	if (bottom1 < top2)
		return false;
	if (top1 > bottom2)
		return false;

	if (right1 < left2)
		return false;
	if (left1 > right2)
		return false;

	return true;
}

bool Entity::PositionValidEntity(Entity* entity, Vector2 newPosition)
{
	if (this != entity && entity != NULL && entity->Collides(Vector2(newPosition.x, newPosition.y)) == true)
	{
		EntityCollision entityCollision;

		entityCollision.EntityA = this;
		entityCollision.EntityB = entity;

		EntityCollision::EntityCollisionStack.push_back(entityCollision);

		OnCollision(entity);

		return false;
	}

	return true;
}

void Entity::SortEntities()
{
	std::sort(Entity::EntityStack.begin(), Entity::EntityStack.end(), SortY);
}

void Entity::OnCleanup()
{
	glDeleteTextures(1, &entityTexture.texture);
}

// lua function
int Entity::addEntity(const char *sprite_name)
{
	Entity *entity = new Entity();
	char s_path[256];
	bzero(s_path, 256);
	sprintf(s_path, "../resources/sprites/%s.png", sprite_name);
	if ((entity->OnLoad(s_path, 3, true)) == false)
		return -1;
	EntityStack.push_back(entity);
	return EntityStack.size();
}

// lua overload
void Entity::faceEntity(int index, int index_to)
{
	Entity::EntityStack[index]->faceEntity(Entity::EntityStack[index_to]);
}

// lua overload
void Entity::setPosition(int index, int x, int y)
{
	Entity::EntityStack[index]->setPosition(x, y);
}

// lua overload
void Entity::setFacing(int index, int direction)
{
	Entity::EntityStack[index]->setFacing(direction);
}

