#include <vector>
#include <fstream>
#include "TileMap.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Constants.hpp"

// Texture file paths
const std::string TILE_SHEET_PATH = "Assets/Maps/TileSheet.png";

//The dimensions of the level
const int LEVEL_WIDTH = SCREEN_WIDTH;
const int LEVEL_HEIGHT = SCREEN_HEIGHT;

SDL_Rect tileSheetClips[TOTAL_TILE_SPRITES];

Tile::Tile(int x, int y, int tileType)
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render()
{
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

Map::Map(Tile* tiles[])
{
	LoadMap(tiles);
	LoadTiles(TILE_SHEET_PATH.c_str());
	destinationRect.w = 32;
	destinationRect.h = 32;
	destinationRect.x = 0;
	destinationRect.y = 0;
}

Map::~Map()
{
}


void Map::LoadTiles(const char* tileSheetFilePath)
{
	tileSheet = TextureManager::loadTexture(tileSheetFilePath);

	for (int tileType = 0; tileType < TOTAL_TILE_SPRITES; tileType++) // Because the tiles are distributed exclusively horizontally on the tilesheet
	{
		tileSheetClips[tileType].x = tileType * SOURCE_TILE_SIZE;
		tileSheetClips[tileType].y = 0;
		tileSheetClips[tileType].w = SOURCE_TILE_SIZE;
		tileSheetClips[tileType].h = SOURCE_TILE_SIZE;
	}
}

bool Map::LoadMap(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("Assets/Maps/Desert.map");

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				std::cout << tileType << " "; //test
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}
			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
	}

	map.close();
	return tilesLoaded;
}

void Map::DrawMap(Tile* tiles[])
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		TextureManager::Draw(tileSheet, tileSheetClips[tiles[i]->getType()], tiles[i]->getBox());
	}
}

