/*
 *  Game.cpp
 *  BBE
 *
 *  Created by James Stine on 5/4/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "Game.h"

Game::Game()
{
	gameScreen = NULL;
	StillBreathing = true;
}

int Game::OnExecute(char* argv[])
{
	if (argv[RUNTIME_MAPFILE] != NULL)
		mapName = argv[RUNTIME_MAPFILE];
	else
	{
		mapName = (char*) malloc(27);
		sprintf(mapName, "../resources/maps/mymap.map");
	}

	if (OnInit() == false)
		return -1;

	printf("Go Engine Go!\n\n");

	SDL_Event event;

	while (StillBreathing)
	{
		while (SDL_PollEvent(&event))
			OnEvent(&event);

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

bool Game::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL_Init > SDL_INIT_EVERYTHING failed.\n");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if ((gameScreen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_OPENGL))	== NULL)
	{
		printf("Setting gameScreen failed.\n");
		return false;
	}

	// enable texture 2d
	glEnable(GL_TEXTURE_2D);

	// set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// set our viewport
	glViewport(0, 0, SCREEN_W, SCREEN_H);

	// enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// clear screen
	glClear(GL_COLOR_BUFFER_BIT);

	// set the matrix for projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// set the ortho to the screen
	glOrtho(0.0f, SCREEN_W, SCREEN_H, 0.0f, -1.0f, 1.0f);

	// switch to model view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// load lua
	if ((LuaController::Controller.OnInit("../resources/lua/main.lua")) == false)
	{
		printf("Loading main lua failed.\n");
		return false;
	}

	// Load map
	if (map1.OnLoad(mapName) == false)
	{
		printf("Loading map '%s' failed.\n", mapName);
		return false;
	}

	map1.SetTileset(map1.mapHeader.tileset);

	Map::MapStack.push_back(&map1);

	Camera::CameraControl.targetMode = TARGET_MODE_CENTER;

	SDL_WM_SetCaption("Blade Brothers Engine", "../resources/icons/icon.png");

	return true;
}

void Game::OnLoop()
{
	// lua loop
	//LuaController::Controller.OnLoop();

	// LuaController::Controller.callFunction("main.lua", "loop", ...);

	// sort the entities based on Y position
	Entity::EntityControl.SortEntities();

	// call entitie's loops
	for (uint i = 0; i < Entity::EntityStack.size(); i++)
	{
		if (!Entity::EntityStack[i])
			continue;
		Entity::EntityStack[i]->OnLoop();
	}

	// lock camera onto the player
	Camera::CameraControl.SetTarget(&Entity::EntityStack[0]->position.x, &Entity::EntityStack[0]->position.y);

	// load the FPS control
	FPS::FPSControl.OnLoad();
}

void Game::OnEvent(SDL_Event* event)
{
	Event::OnEvent(event);
}

void Game::OnResize(int w, int h) {}

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Player *player = (Player*)Entity::EntityStack[0];

	if (sym == SDLK_ESCAPE)
		StillBreathing = false;
	else if (sym == SDLK_UP)
		player->OnMove(ENTITY_FACE_UP, true);
	else if (sym == SDLK_DOWN)
		player->OnMove(ENTITY_FACE_DOWN, true);
	else if (sym == SDLK_LEFT)
		player->OnMove(ENTITY_FACE_LEFT, true);
	else if (sym == SDLK_RIGHT)
		player->OnMove(ENTITY_FACE_RIGHT, true);
	else if (sym == SDLK_LSHIFT || sym == SDLK_RSHIFT)
		player->sprinting = true;
	else if (sym == SDLK_TAB)
	{
		/*
		luaL_dofile(L, "../resources/lua/create_npc.lua"); // create entity
		lua_getglobal(L, "npc");
		Entity *npc = static_cast<Entity*>(tolua_tousertype(L, -1, 0));
		npc->SetPosition(player.tilePosition.x, player.tilePosition.y);
		Entity::EntityStack.push_back(npc);
		*/
	}
	else if (sym == SDLK_RETURN)
	{
		//Entity *npc = player.FacingEntity();
		//if (npc != NULL)
			//npc->OnTalk(L);
	}

	/*
	// call the key_press function
	luaL_dofile(L, "../resources/lua/main.lua");
	// get the init function
	lua_getglobal(L, "key_press");
	// make sure its a function
	if (!lua_isfunction(L, lua_gettop(L)))
		return;
	// push our key
	lua_pushinteger(L, sym);
	// call our init function
	lua_call(L, 1, 0);
	*/
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Player *player = (Player*)Entity::EntityStack[0];

	if (sym == SDLK_UP)
		player->OnMove(ENTITY_FACE_UP, false);
	else if (sym == SDLK_DOWN)
		player->OnMove(ENTITY_FACE_DOWN, false);
	else if (sym == SDLK_LEFT)
		player->OnMove(ENTITY_FACE_LEFT, false);
	else if (sym == SDLK_RIGHT)
		player->OnMove(ENTITY_FACE_RIGHT, false);
	else if (sym == SDLK_LSHIFT || sym == SDLK_RSHIFT)
		player->sprinting = false;
}

void Game::OnExit()
{
	StillBreathing = false;
}

void Game::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int mapX = -Camera::CameraControl.GetX();
	int mapY = -Camera::CameraControl.GetY();

	map1.OnRender(MAP_LAYER_GROUND, mapX, mapY);
	map1.OnRender(MAP_LAYER_MIDDLE, mapX, mapY);

	for (uint i = 0; i < Entity::EntityStack.size(); i++)
	{
		if (!Entity::EntityStack[i])
			continue;
		Entity::EntityStack[i]->OnRender();
	}

	map1.OnRender(MAP_LAYER_TOP, mapX, mapY);

	for (uint i = 0; i < Window::WindowStack.size(); i++)
	{
		if (!Window::WindowStack[i])
			continue;
		Window::WindowStack[i]->OnRender();
	}

	SDL_GL_SwapBuffers();
}

void Game::OnCleanup()
{
	SDL_FreeSurface(gameScreen);

	for (uint i = 0; i < Entity::EntityStack.size(); i++)
	{
		if (!Entity::EntityStack[i])
			continue;

		Entity::EntityStack[i]->OnCleanup();
	}

	Entity::EntityStack.clear();

	for (uint i = 0; i < Window::WindowStack.size(); i++)
	{
		if (!Window::WindowStack[i])
			continue;

		Window::WindowStack[i]->OnCleanup();
	}

	Window::WindowStack.clear();

	SDL_Quit();
}
