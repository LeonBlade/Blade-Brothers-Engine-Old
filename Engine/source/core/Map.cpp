/*
 *  Map.cpp
 *  
 *
 *  Created by James Stine on 2/1/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "core/Map.h"

std::vector<Map*> Map::MapStack;
Map Map::MapControl;

Map::Map()
{
	magic = 0;
	mapHeader = MapHeader();
	mapData = new MapData();
}

void Map::setMapName(const char *name)
{
	mapHeader.mapNameSize = sizeof(name);
	mapHeader.mapName = (char*)malloc(mapHeader.mapNameSize);
	memcpy(mapHeader.mapName, name, mapHeader.mapNameSize);
	mapHeader.mapName[mapHeader.mapNameSize] = '\0';
}

void Map::setTileset(const char *tileset)
{
	if (tileset != NULL)
	{
		mapHeader.tilesetNameSize = sizeof(tileset);
		mapHeader.tileset = (char*)malloc(mapHeader.tilesetNameSize);
		memcpy(mapHeader.tileset, tileset, mapHeader.tilesetNameSize);
		mapHeader.tileset[mapHeader.tilesetNameSize] = '\0';
	}

	char path[256];
	sprintf(path, "../resources/tilesets/%s/ground.png", mapHeader.tileset);
	Sprite::OnLoad(path, groundTexture);
	sprintf(path, "../resources/tilesets/%s/walls.png", mapHeader.tileset);
	Sprite::OnLoad(path, wallTexture);
	sprintf(path, "../resources/tilesets/%s/autotiles.png", mapHeader.tileset);
	Sprite::OnLoad(path, autoTexture);
	sprintf(path, "../resources/tilesets/%s/objects.png", mapHeader.tileset);
	Sprite::OnLoad(path, objectTexture);
}

void Map::OnCreate(int width, int height)
{
	magic = 1179468354;

	mapHeader.tilesX = width;
	mapHeader.tilesY = height;

	mapHeader.startX = 0;
	mapHeader.startY = 0;

	setMapName("New map");
	setTileset("interior");

	unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
	unsigned int tileBufferSize = tileCount * sizeof(MapData);

	mapData = (MapData*) malloc(tileBufferSize);

	for (int y = 0; y < mapHeader.tilesY; y++)
	{
		for (int x = 0; x < mapHeader.tilesX; x++)
		{
			mapData[x + (mapHeader.tilesX * y)].tile[Ground] 	= (MapTile){Normal, 1};
			mapData[x + (mapHeader.tilesX * y)].tile[Middle] 	= (MapTile){Normal, 0};
			mapData[x + (mapHeader.tilesX * y)].tile[Top] 		= (MapTile){Normal, 0};
			mapData[x + (mapHeader.tilesX * y)].tile[Collision] = (MapTile){Normal, 0};
		}
	}
}

bool Map::OnLoad(const char* filename)
{
	FILE* fileHandle = fopen(filename, "r");
	if (fileHandle == NULL)
		return false;

	// read in the magic
	fread(&magic, 4, 1, fileHandle);

	if (magic != 1179468354)
		return false;

	fread(&mapHeader.tilesX, sizeof(unsigned short), 1, fileHandle);
	fread(&mapHeader.tilesY, sizeof(unsigned short), 1, fileHandle);
	fread(&mapHeader.mapNameSize, sizeof(unsigned short), 1, fileHandle);
	mapHeader.mapName = (char*)malloc(mapHeader.mapNameSize);
    fread(mapHeader.mapName, mapHeader.mapNameSize, 1, fileHandle);
    mapHeader.mapName[mapHeader.mapNameSize] = '\0';
    fread(&mapHeader.tilesetNameSize, sizeof(unsigned short), 1, fileHandle);
    mapHeader.tileset = (char*)malloc(mapHeader.tilesetNameSize);
    fread(mapHeader.tileset, mapHeader.tilesetNameSize, 1, fileHandle);
    mapHeader.tileset[mapHeader.tilesetNameSize] = '\0';
    fread(&mapHeader.startX, sizeof(unsigned short), 1, fileHandle);
    fread(&mapHeader.startY, sizeof(unsigned short), 1, fileHandle);

	unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
	unsigned int tileBufSize = tileCount * sizeof(MapData);
	mapData = (MapData*) malloc(tileBufSize);

	// read in map data
	fread(mapData, tileBufSize, 1, fileHandle);

	fclose(fileHandle);

	// by passing NULL we tell the function we don't want to re-assign the tileset name itself
	setTileset(NULL);

	return true;
}

void Map::OnRender(Layer layer, int mapX, int mapY)
{
	for (int y = 0; y < mapHeader.tilesY; y++)
	{
		for (int x = 0; x < mapHeader.tilesX; x++)
		{
			SpriteTexture *mapTexture;
			switch (mapData[x + (mapHeader.tilesX * y)].tile[layer].type)
			{
			case Normal:
				mapTexture = &groundTexture;
				break;
			case Wall:
				mapTexture = &wallTexture;
				break;
			case Object:
				mapTexture = &objectTexture;
				break;
			case AutoTile:
				mapTexture = &autoTexture;
				break;
			}

			int tileID = (mapData[x + (mapHeader.tilesX * y)].tile[layer].data);
			if (tileID > 0 && mapTexture->width > 0 && mapTexture->height > 0)
			{
				tileID -= 1;

				Vector2 position;
				position.x = mapX + (x * TILE_SIZE);
				position.y = mapY + (y * TILE_SIZE);

				SDL_Rect frameRect;
				frameRect.x = (tileID % (mapTexture->width / TILE_SIZE)) * TILE_SIZE;
				frameRect.y = mapTexture->height - ((tileID / (mapTexture->width / TILE_SIZE)) * TILE_SIZE) - TILE_SIZE;
				frameRect.w = TILE_SIZE;
				frameRect.h = TILE_SIZE;

				if (layer != Collision)
					Sprite::OnDraw(*mapTexture, position, frameRect);
			}
		}
	}
}

Map::MapTile Map::getTile(int xTile, int yTile, Layer layer)
{
	return mapData[xTile + (mapHeader.tilesX * yTile)].tile[layer];
}

void Map::setTile(int xTile, int yTile, Layer layer, TileType type, int tileValue)
{
	mapData[(int) (xTile + (mapHeader.tilesX * yTile))].tile[layer].type = type;
	mapData[(int) (xTile + (mapHeader.tilesX * yTile))].tile[layer].data = tileValue;
}

void Map::Resize(int w, int h)
{
	Map tm;
	tm.OnCreate(w, h);

	// loop through all the tiles of the current map's tiles and distribute them to the new one
	for (int y = 0; y < this->mapHeader.tilesY; y++)
	{
		for (int x = 0; x < this->mapHeader.tilesX; x++)
		{
			tm.setTile(x, y, Ground, 	getTile(x, y, Ground).type, 	getTile(x, y, Ground).data);
			tm.setTile(x, y, Middle, 	getTile(x, y, Middle).type, 	getTile(x, y, Middle).data);
			tm.setTile(x, y, Top, 		getTile(x, y, Top).type, 		getTile(x, y, Top).data);
			tm.setTile(x, y, Collision, Normal, 						getTile(x, y, Collision).data);
		}
	}

	this->OnCreate(w, h);
	this->mapData = tm.mapData;
}

bool Map::OnSave(const char* filename)
{
	FILE* fileHandler = NULL;
	if ((fileHandler = fopen(filename, "w+")) == NULL)
		return false;

	unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
	unsigned int tileBufferSize = tileCount * sizeof(MapData);

	fwrite(&magic, 4, 1, fileHandler);
	fwrite(&mapHeader.tilesX, sizeof(unsigned short), 1, fileHandler);
	fwrite(&mapHeader.tilesY, sizeof(unsigned short), 1, fileHandler);
	fwrite(&mapHeader.mapNameSize, sizeof(unsigned short), 1, fileHandler);
	fwrite(mapHeader.mapName, mapHeader.mapNameSize, 1, fileHandler);
	fwrite(&mapHeader.tilesetNameSize, sizeof(unsigned short), 1, fileHandler);
	fwrite(mapHeader.tileset, mapHeader.tilesetNameSize, 1, fileHandler);
	fwrite(&mapHeader.startX, sizeof(unsigned short), 1, fileHandler);
	fwrite(&mapHeader.startY, sizeof(unsigned short), 1, fileHandler);
	fwrite(mapData, tileBufferSize, 1, fileHandler);

	fclose(fileHandler);

	return true;
}

int Map::getTilesX()
{
	return this->mapHeader.tilesX;
}
int Map::getTilesY()
{
	return this->mapHeader.tilesY;
}
int Map::getStartX()
{
	return this->mapHeader.startX;
}
int Map::getStartY()
{
	return this->mapHeader.startY;
}
void Map::setStartX(int value)
{
	this->mapHeader.startX = value;
}
void Map::setStartY(int value)
{
	this->mapHeader.startY = value;
}
char* Map::getMapName()
{
	return this->mapHeader.mapName;
}
char* Map::getTileset()
{
	return this->mapHeader.tileset;
}
