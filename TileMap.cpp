#include <vector>
#include <fstream>
#include <sstream>
#include "TileMap.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Constants.hpp"

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

	// Set the sides' coordinates
	leftSide.x = x;
	leftSide.y = y;
	leftSide.w = 1;
	leftSide.h = TILE_HEIGHT;

	rightSide.x = x + TILE_WIDTH;
	rightSide.y = y;
	rightSide.w = 1;
	rightSide.h = TILE_HEIGHT;

	topSide.x = x;
	topSide.y = y;
	topSide.w = TILE_WIDTH;
	topSide.h = 1;

	bottomSide.x = x;
	bottomSide.y = y + TILE_HEIGHT;
	bottomSide.w = TILE_WIDTH;
	bottomSide.h = 1;
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

SDL_Rect Tile::getLeftSide()
{
	return leftSide;
}

SDL_Rect Tile::getTopSide()
{
	return topSide;
}

SDL_Rect Tile::getRightSide()
{
	return rightSide;
}

SDL_Rect Tile::getBottomSide()
{
	return bottomSide;
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
	std::fstream map (TILE_MAP_PATH, std::ios::in);
	// Extracting the contents of the map
	std::vector<std::string> mapContent;
	std::string line, word;

	if (map.is_open())
	{
		while (std::getline(map, line))
		{
			std::stringstream stream(line);

			while (std::getline(stream, word, ','))
			{
				mapContent.push_back(word);
			}
		}
	}
	else
	{
		std::cout << "Unable to load map file!" << std::endl;
	}

	//Initialize the tiles
	for (int tileCnt = 0; tileCnt < mapContent.size(); ++tileCnt)
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		//Read tile from map file
		tileType = std::stoi(mapContent[tileCnt]);

		//If the number is a valid tile number
		if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
		{
			tiles[tileCnt] = new Tile(x, y, tileType);
		}
		//If we don't recognize the tile type
		else
		{
			//Stop loading map
			printf("Error loading map: Invalid tile type at %d!\n", tileCnt);
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

