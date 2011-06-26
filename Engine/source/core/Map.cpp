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

	sprintf(path, "../resources/tilesets/%s/normal.png", mapHeader.tileset);
	Sprite::OnLoad(path, normalTexture);

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
	setTileset("field");

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
			mapData[x + (mapHeader.tilesX * y)].collision = 0;
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
			Map::MapTile currentTile = mapData[x + (mapHeader.tilesX * y)].tile[layer];

			SpriteTexture *mapTexture;
			if (currentTile.type == Map::Normal) mapTexture = &normalTexture;
			else mapTexture = &objectTexture;

			int tileID = currentTile.data;
			if (tileID > 0)
			{
				tileID -= 1;

				// here is where we handle multiple tile types
				// first we're going to check to see which tiles we're dealing with
				// we can also check with OR if we're just doing object tiles as they will be rendered the same
				//if (currentTile.type == Map::Object /*|| (currentTile.type == Map::Normal && tileID >= 0 && tileID <= 31)*/)
				//{
					Vector2 position;
					position.x = mapX + (x * TILE_SIZE);
					position.y = mapY + (y * TILE_SIZE);

					SDL_Rect frameRect;
					frameRect.x = (tileID % 16) * TILE_SIZE;
					frameRect.y = 256 - ((tileID / 16) * TILE_SIZE) - TILE_SIZE;
					frameRect.w = TILE_SIZE;
					frameRect.h = TILE_SIZE;

					Sprite::OnDraw(*mapTexture, position, frameRect);
				//}
				/* autotiles
				// so now we check for the specific ranges for other tiles
				// our first set is is the standard auto-tiles, we can also check for the roofs of the walls here too
				// NOTE: these IDs DON'T map normally like regular tiles do, only the single tile preview in the top left of each
				// auto-tile is counted as the ID, the range otherwise would be to 80 but because we don't count those it's just 48
				else if (currentTile.type == Map::Normal && tileID >= 32 && tileID <= 47)
				{
					// get our position and frame defined so we can use it
					Vector2 position, thisPosition;
					SDL_Rect frameRect, thisRect;

					// set defaults this will put us in the position on the map it needs to go but will be altered for certain tiles
					position.x = mapX + (x * TILE_SIZE);
					position.y = mapY + (y * TILE_SIZE);

					// this will get us to our ID tile on the tile-sheet we leave out W and H to ensure those are defined
					frameRect.x = ((tileID % 16) * TILE_SIZE) * 2;
					frameRect.y = (512 - ((tileID / 16) * TILE_SIZE) - TILE_SIZE);

					// first step of any auto-tile is to determine which tiles are around it
					// this will let us know what kind of tile it is
					// so first we get the IDs of each tile surrounding this tile in 8 directions
					// we don't actually store the IDs we just store a 1 or 0 through a boolean return

					// edges
					int _t = (getTile(x, 		y - 1, 	layer).data - 1 == tileID);
					int _l = (getTile(x - 1, 	y, 		layer).data - 1 == tileID);
					int _r = (getTile(x + 1, 	y,		layer).data - 1 == tileID);
					int _b = (getTile(x, 		y + 1, 	layer).data - 1 == tileID);
					// corners
					int _tl = (getTile(x - 1, y - 1, layer).data - 1 == tileID);
					int _tr = (getTile(x + 1, y - 1, layer).data - 1 == tileID);
					int _bl = (getTile(x - 1, y + 1, layer).data - 1 == tileID);
					int _br = (getTile(x + 1, y + 1, layer).data - 1 == tileID);

					// now with all the pieces we can determine which tile it is
					// we start with middle pieces as those require the most to be true
					// NOTE: all Y positions must be SUBTRACTED instead of ADDED because of the way the coordinates work
					if (_t && _l && _r && _b)
					{
						thisRect = frameRect;
						thisRect.x += 16;
						thisRect.y -= 32 + 16;
						thisRect.w = TILE_SIZE;
						thisRect.h = TILE_SIZE;

						Sprite::OnDraw(*mapTexture, position, thisRect);
					}
					// now we move on to the corners
					// there are also times where we need to draw sides and centers with certain corners
					if (!_l && !_t) // top left corner
					{
						thisRect = frameRect;
						thisRect.y -= 32 - 16;
						thisRect.w = 16;
						thisRect.h = 16;

						Sprite::OnDraw(*mapTexture, position, thisRect);

						if (_b)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.y -= 32 + 16;

							thisPosition = position;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_r)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 16;
							thisRect.y -= 32 - 16;

							thisPosition = position;
							thisPosition.x += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}

						if (_b && _r && _br)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32;
							thisRect.w = 16;
							thisRect.h = 16;

							thisPosition = position;
							thisPosition.x += 16;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (!_t && !_r) // top right corner
					{
						thisRect = frameRect;
						thisRect.x += 32 + 16;
						thisRect.y -= 32 - 16;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						if (_b)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 32 + 16;
							thisRect.y -= 32 + 16;

							thisPosition = position;
							thisPosition.x += 16;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_l)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 32;
							thisRect.y -= 32 - 16;

							thisPosition = position;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_b && _l && _bl)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32;
							thisRect.w = 16;
							thisRect.h = 16;

							thisPosition = position;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (!_l && !_b) // bottom left corner
					{
						thisRect = frameRect;
						thisRect.y -= 64;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						if (_t)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.y -= 32 + 16;

							thisPosition = position;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_r)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 16;
							thisRect.y -= 64;

							thisPosition = position;
							thisPosition.x += 16;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_t && _r && _tr)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = 16;
							thisRect.h = 16;

							thisPosition = position;
							thisPosition.x += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (!_b && !_r) // bottom right corner
					{
						thisRect = frameRect;
						thisRect.x += 32 + 16;
						thisRect.y -= 64;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						if (_t)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 32 + 16;
							thisRect.y -= 32 + 16;

							thisPosition = position;
							thisPosition.x += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_l)
						{
							thisRect = frameRect;
							thisRect.w = 16;
							thisRect.h = 16;
							thisRect.x += 16;
							thisRect.y -= 64;

							thisPosition = position;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
						if (_t && _l && _tl)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = 16;
							thisRect.h = 16;

							thisPosition = position;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					// now we check for edges!
					if (_l && _r && !_t) // top edge
					{
						thisRect = frameRect;
						thisRect.x += 32;
						thisRect.y -= 32 - 16;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						thisRect = frameRect;
						thisRect.x += 16;
						thisRect.y -= 32 - 16;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						if (_b)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = TILE_SIZE;
							thisRect.h = 16;

							thisPosition = position;
							thisPosition.y += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (_l && _r && !_b) // bottom edge
					{
						thisRect = frameRect;
						thisRect.x += 32;
						thisRect.y -= 64;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						thisRect = frameRect;
						thisRect.x += 16;
						thisRect.y -= 64;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);

						if (_t)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = TILE_SIZE;
							thisRect.h = 16;

							thisPosition = position;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (_t && _b && !_l) // left edge
					{
						thisRect = frameRect;
						thisRect.y -= 32 + 16;
						thisRect.w = 16;
						thisRect.h = TILE_SIZE;

						Sprite::OnDraw(*mapTexture, position, thisRect);

						if (_r)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = TILE_SIZE;
							thisRect.h = TILE_SIZE;

							thisPosition = position;
							thisPosition.x += 16;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					if (!_r && _t && _b) // right edge
					{
						thisRect = frameRect;
						thisRect.x += 32 + 16;
						thisRect.y -= 32 + 16;
						thisRect.w = 16;
						thisRect.h = TILE_SIZE;

						position.x += 16;

						Sprite::OnDraw(*mapTexture, position, thisRect);

						if (_l)
						{
							thisRect = frameRect;
							thisRect.x += 16;
							thisRect.y -= 32 + 16;
							thisRect.w = TILE_SIZE;
							thisRect.h = TILE_SIZE;

							thisPosition = position;
							thisPosition.x -= 32;

							Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
						}
					}
					// check for inside corners
					if (!_tl && _t && _l)
					{
						SDL_Rect thisRect = frameRect;
						thisRect = frameRect;
						thisRect.x += 32;
						thisRect.y += 16;
						thisRect.w = 16;
						thisRect.h = 16;

						Sprite::OnDraw(*mapTexture, position, thisRect);
					}
					if (!_tr && _t && _r)
					{
						thisRect = frameRect;
						thisRect = frameRect;
						thisRect.x += 32 + 16;
						thisRect.y += 16;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
					}
					if (!_bl && _b && _l)
					{
						thisRect = frameRect;
						thisRect = frameRect;
						thisRect.x += 32;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
					}
					if (!_br && _b && _r)
					{
						thisRect = frameRect;
						thisRect.x += 32 + 16;
						thisRect.w = 16;
						thisRect.h = 16;

						thisPosition = position;
						thisPosition.x += 16;
						thisPosition.y += 16;

						Sprite::OnDraw(*mapTexture, thisPosition, thisRect);
					}
				}
				*/
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

int Map::getCollision(int xTile, int yTile)
{
	return mapData[(int) (xTile + (mapHeader.tilesX * yTile))].collision;
}

void Map::setCollision(int xTile, int yTile, int value)
{
	mapData[(int) (xTile + (mapHeader.tilesX * yTile))].collision = value;
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
			tm.setCollision(x, y, 0);
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
char *Map::getMapName()
{
	return this->mapHeader.mapName;
}
char *Map::getTileset()
{
	return this->mapHeader.tileset;
}
