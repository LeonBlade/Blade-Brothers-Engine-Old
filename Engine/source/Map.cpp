/*
 *  Map.cpp
 *  
 *
 *  Created by James Stine on 2/1/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "Map.h"

std::vector<Map*> Map::MapStack;
Map Map::MapControl;

Map::Map() 
{
    magic = 0;
    mapHeader = MapHeader();
    mapData = new MapData();
	savedRecently = false;
}

void Map::SetMapName(const char *name)
{	
	memcpy(mapHeader.mapName, name, 32);
}

void Map::SetTileset(const char *tileset)
{
	memcpy(mapHeader.tileset, tileset, 32);
	
	char path[256] = "../resources/tilesets/";
	strcat(path, tileset);
	
	Sprite::OnLoad(path, mapTexture);
}

void Map::OnCreate(int width, int height)
{
    magic = 1179468354;

    mapHeader.tilesX = width;
    mapHeader.tilesY = height;
    
    SetMapName("New map");
	//SetTileset("tileset.png");

    unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
    unsigned int tileBufferSize = tileCount * sizeof(MapData);
    
    mapHeader.fileLength = (unsigned int)(sizeof(magic) + sizeof(MapHeader) + tileBufferSize);
    
    mapData = (MapData*)malloc(tileBufferSize);
    
    for (int y=0; y<mapHeader.tilesY; y++)
    {
		for (int x=0; x<mapHeader.tilesX; x++)
		{
			mapData[x + (mapHeader.tilesX * y)].tileData[MAP_LAYER_GROUND]	    = 1;
			mapData[x + (mapHeader.tilesX * y)].tileData[MAP_LAYER_MIDDLE]	    = 0;
			mapData[x + (mapHeader.tilesX * y)].tileData[MAP_LAYER_TOP]	        = 0;
			mapData[x + (mapHeader.tilesX * y)].tileData[MAP_LAYER_COLLISION]	= 0;
		}
    }
}

void Map::EditTile(int xTile, int yTile, int layer, int tileValue)
{
    mapData[(int)(xTile + (mapHeader.tilesX * yTile))].tileData[layer] = tileValue;
    savedRecently = false;
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

    // read the header
    memset(&mapHeader, 0, sizeof(MapHeader));
    fread(&mapHeader, sizeof(MapHeader), 1, fileHandle);
    
    unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
    unsigned int tileBufSize = tileCount * sizeof(MapData);
    mapData = (MapData*)malloc(tileBufSize);
    
    // read in map data
    fread(mapData, tileBufSize, 1, fileHandle);
    
    fclose(fileHandle);
	
	savedRecently = true;
	
	SetTileset(mapHeader.tileset);

    return true;
}

void Map::OnRender(int layer, int mapX, int mapY)
{    
    for (int y = 0; y < mapHeader.tilesY; y++)
    {
        for (int x = 0; x < mapHeader.tilesX; x++)
        {
            int tileID = (mapData[x + (mapHeader.tilesX * y)].tileData[layer]);
            if (tileID != 0 && mapTexture.width > 0 && mapTexture.height > 0)
            {
                Vector2 position;
                position.x = mapX + (x * TILE_SIZE);
                position.y = mapY + (y * TILE_SIZE);

                FrameRect frameRect;
                frameRect.x = (tileID % (mapTexture.width / TILE_SIZE)) * TILE_SIZE;
                frameRect.y = mapTexture.height - ((tileID / (mapTexture.width / TILE_SIZE)) * TILE_SIZE) - TILE_SIZE;
                frameRect.w = TILE_SIZE;
                frameRect.h = TILE_SIZE;

                if (layer != MAP_LAYER_COLLISION)
                    Sprite::OnDraw(mapTexture, position, frameRect);
				else
					Sprite::OnDraw(collisionTexture, position, frameRect);
            }
        }
    }
}

int Map::GetTile(int xTile, int yTile, int layer)
{
    return mapData[xTile + (mapHeader.tilesX * yTile)].tileData[layer];
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
            tm.EditTile(x, y, MAP_LAYER_GROUND,    GetTile(x, y, MAP_LAYER_GROUND));
            tm.EditTile(x, y, MAP_LAYER_MIDDLE,    GetTile(x, y, MAP_LAYER_MIDDLE));
            tm.EditTile(x, y, MAP_LAYER_TOP,       GetTile(x, y, MAP_LAYER_TOP));
            tm.EditTile(x, y, MAP_LAYER_COLLISION, GetTile(x, y, MAP_LAYER_COLLISION));
        }
    }	
    
    this->OnCreate(w, h);
    this->mapData = tm.mapData;

    savedRecently = false;
}

bool Map::OnSave(const char* filename)
{
    FILE* fileHandler = NULL;
    if ((fileHandler = fopen(filename, "w+")) == NULL)
	return false;
    
    unsigned int tileCount = mapHeader.tilesX * mapHeader.tilesY;
    unsigned int tileBufferSize = tileCount * sizeof(MapData); 
    
    fwrite(&magic, 4, 1, fileHandler);
    fwrite(&mapHeader, sizeof(MapHeader), 1, fileHandler);
    fwrite(mapData, tileBufferSize, 1, fileHandler);
    
    fclose(fileHandler);

    savedRecently = true;
    
    return true;
}
