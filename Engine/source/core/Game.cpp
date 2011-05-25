/*
 *  Game.cpp
 *  BBE
 *
 *  Created by James Stine on 5/4/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "core/Game.h"

Game::Game()
{
	gameScreen = NULL;
	StillBreathing = true;
}

int Game::OnExecute(char* argv[])
{
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

	if ((gameScreen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_OPENGL)) == NULL)
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
	if ((LuaController::Controller.OnInit()) == false)
	{
		printf("Lua initialization failed.\n");
		return false;
	}

	// load player
	if (player.OnLoad("../resources/sprites/player.png", 3, true) == false)
	{
		printf("Loading player failed.\n");
		return false;
	}
	Entity::EntityStack.push_back(&player);

	// Load map
	if (map.OnLoad("../resources/maps/testmap.map") == false)
	{
		printf("Loading map failed.\n");
		return false;
	}
	Map::MapStack.push_back(&map);

	player.setPosition(map.getStartX(), map.getStartY());

	if (debugWindow.OnLoad("../resources/sprites/window.png") == false)
	{
		printf("Loading window failed.\n");
		return false;
	}

	debugWindow.setSize(160, 32);
	debugWindow.setPosition(8, 8);
	Window::WindowStack.push_back(&debugWindow);

	Camera::CameraControl.targetMode = TARGET_MODE_CENTER;
	Camera::CameraControl.SetBounds((SDL_Rect){0, 0, map.getTilesX() * TILE_SIZE, map.getTilesY() * TILE_SIZE});

	SDL_WM_SetCaption("Blade Brothers Engine", "../resources/icons/icon.png");

	return true;
}

void Game::OnLoop()
{
	// call entitie's loops
	for (uint i = 0; i < Entity::EntityStack.size(); i++)
	{
		if (!Entity::EntityStack[i])
			continue;
		Entity::EntityStack[i]->OnLoop();
	}

	// lock camera onto the player
	Camera::CameraControl.SetTarget(&player.getTarget()->x, &player.getTarget()->y);

	// load the FPS control
	FPS::FPSControl.OnLoad();
}

void Game::OnEvent(SDL_Event* event)
{
	Event::OnEvent(event);
}

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_ESCAPE)
		StillBreathing = false;

	player.handleKeyboard(sym, true);
}

void Game::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	player.handleKeyboard(sym, false);
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

	map.OnRender(Map::Ground, mapX, mapY);
	map.OnRender(Map::Middle, mapX, mapY);

	for (uint i = 0; i < Entity::EntityStack.size(); i++)
	{
		if (!Entity::EntityStack[i])
			continue;
		Entity::EntityStack[i]->OnRender();
	}

	map.OnRender(Map::Top, mapX, mapY);

	char dw_msg[1024];
	sprintf(dw_msg, "^c3Blade Brothers Engine^c0^n^c8Map:^c0 %s", map.getMapName());

	debugWindow.setMessage(dw_msg);

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
