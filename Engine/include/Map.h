/*
 *  Map.h
 *  
 *
 *  Created by James Stine on 2/1/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */
#ifndef _MAP_H_
#define _MAP_H_

#ifdef TOOLKIT
    #include <qgl.h>
#elif ENGINE
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Define.h"

#include "Sprite.h"
#include "FrameRect.h"
#include "Vector2.h"

struct MapHeader
{
    unsigned int		fileLength;
    unsigned short		tilesX;
    unsigned short		tilesY;
    char mapName[32];
	char tileset[32];
};

struct MapData
{
    unsigned char		tileData[4];
};

struct MapTile
{
    unsigned int		groundTile;
    unsigned int		middleTile;
    unsigned int		topTile;
    unsigned short		collisionTile;
};

class Map
{
	
public:
	static std::vector<Map*> MapStack;
	static Map MapControl;
	
public:
	SpriteTexture mapTexture, collisionTexture;
	MapData* mapData;
	MapHeader mapHeader;
	unsigned int magic;
	bool savedRecently;
	
public:
	Map();
	
public:
	void OnCreate(int width, int height);	
	void EditTile(int xTile, int yTile, int layer, int tileValue);
	bool OnLoad(const char* filename);
	void OnRender(int layer, int mapX, int mapY);
	bool OnSave(const char* filename);
	void Resize(int w, int h);
	int GetTile(int xTile, int yTile, int layer);
	void SetMapName(const char *name);
	void SetTileset(const char *tileset);
	
};

	
#endif
