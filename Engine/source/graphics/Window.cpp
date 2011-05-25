/*
 *  Window.cpp
 *  BBE
 *
 *  Created by James Stine on 10/9/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "graphics/Window.h"

std::vector<Window*> Window::WindowStack;

Window::Window()
{
	position = Vector2(0, 0);
	size = Vector2(100, 100);
	alpha = 1;
}

Window::~Window()
{
}

bool Window::OnLoad(const char * filename)
{
	if (!Sprite::OnLoad(filename, windowTexture))
		return false;

	font.OnLoad("../resources/sprites/font.png");

	font.setPosition(Vector2(position.x, position.y + 5));

	return true;
}

void Window::OnRender()
{
	glBindTexture(GL_TEXTURE_2D, NULL);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin( GL_QUADS);
	{
		// top left
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		glVertex3i(position.x + 3, position.y + 3, 1);

		// top right
		glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
		glVertex3i(position.x + size.x - 3, position.y + 3, 1);

		// bottom right
		glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
		glVertex3i(position.x + size.x - 3, position.y + size.y - 3, 1);

		// bottom left
		glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
		glVertex3i(position.x + 3, position.y + size.y - 3, 1);
	}
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);

	// top left
	Sprite::OnDraw(windowTexture, position, (SDL_Rect)
	{	0,windowTexture.height-WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE});
	// top
	Sprite::OnDraw(windowTexture, Vector2(position.x + WINDOW_TILE_SIZE, position.y), (SDL_Rect)
	{	WINDOW_TILE_SIZE,windowTexture.height-WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE}, Vector2(size.x - (WINDOW_TILE_SIZE * 3), 0));
	// top right
	Sprite::OnDraw(windowTexture, Vector2(position.x + size.x - WINDOW_TILE_SIZE, position.y), (SDL_Rect)
	{	windowTexture.width-WINDOW_TILE_SIZE,windowTexture.height-WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE});
	// left
	Sprite::OnDraw(windowTexture, Vector2(position.x, position.y + WINDOW_TILE_SIZE), (SDL_Rect)
	{	0,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE}, Vector2(0, size.y - (WINDOW_TILE_SIZE * 3)));
	// right
	Sprite::OnDraw(windowTexture, Vector2(position.x + size.x - WINDOW_TILE_SIZE, position.y + WINDOW_TILE_SIZE), (SDL_Rect)
	{	windowTexture.width-WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE}, Vector2(0, size.y - (WINDOW_TILE_SIZE * 3)));
	// bottom left
	Sprite::OnDraw(windowTexture, Vector2(position.x, position.y + size.y - WINDOW_TILE_SIZE), (SDL_Rect)
	{	0,0,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE});
	// top
	Sprite::OnDraw(windowTexture, Vector2(position.x + WINDOW_TILE_SIZE, position.y + size.y - WINDOW_TILE_SIZE), (SDL_Rect)
	{	WINDOW_TILE_SIZE,0,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE}, Vector2(size.x - (WINDOW_TILE_SIZE * 3), 0));
	// bottom right
	Sprite::OnDraw(windowTexture, Vector2(position.x + size.x - WINDOW_TILE_SIZE, position.y + size.y - WINDOW_TILE_SIZE), (SDL_Rect)
	{	windowTexture.width-WINDOW_TILE_SIZE,0,WINDOW_TILE_SIZE,WINDOW_TILE_SIZE});

	// font stuff here
	font.OnRender();
}

void Window::OnCleanup()
{
	glDeleteTextures(1, &windowTexture.texture);
	font.OnCleanup();
}

void Window::setMessage(const char * message)
{
	font.setText(message);
}

void Window::setPosition(int x, int y)
{
	position = Vector2(x, y);
	font.setPosition(Vector2(position.x, position.y + 5));
}

void Window::setSize(int w, int h)
{
	size = Vector2(w, h);
}
