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

#include "graphics/Graphics.h"
#include "Vector2.h"

class Map
{
public:
	static std::vector<Map*> MapStack;
	static Map MapControl;

	enum TileType
	{
		Normal = 0,
		Wall = 1,
		AutoTile = 2,
		Object = 3
	};

	enum Layer
	{
		Ground = 0,
		Middle = 1,
		Top = 2,
		Collision = 3
	};

	struct MapHeader
	{
	    unsigned short tilesX;
	    unsigned short tilesY;
	    unsigned short mapNameSize;
	    char *mapName;
	    unsigned short tilesetNameSize;
	    char *tileset;
	    unsigned int startX;
	    unsigned int startY;
	};

	struct MapTile
	{
		TileType type;
		unsigned char data;
	};

	struct MapData
	{
	    MapTile tile[4];
	};

public:
	Map();
	void OnCreate(int width, int height);	
	bool OnLoad(const char* filename);
	void OnRender(Layer layer, int mapX, int mapY);
	bool OnSave(const char* filename);
	void Resize(int w, int h);

	// getters and setters so we can quit being non-OOP
	Map::MapTile getTile(int xTile, int yTile, Layer layer);
	void setTile(int xTile, int yTile, Layer layer, TileType type, int tileValue);
	int getTilesX();
	int getTilesY();
	int getStartX();
	int getStartY();
	void setStartX(int value);
	void setStartY(int value);
	char* getMapName();
	char* getTileset();
	void setMapName(const char *name);
	void setTileset(const char *tileset);

private:
	SpriteTexture groundTexture, wallTexture, autoTexture, objectTexture;
	MapData* mapData;
	MapHeader mapHeader;
	unsigned int magic;

};
	
#endif
