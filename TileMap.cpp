#include <vector>
#include <fstream>
#include "TileMap.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"

//The dimensions of the level
const int LEVEL_WIDTH = Game::SCREEN_WIDTH;
const int LEVEL_HEIGHT = Game::SCREEN_HEIGHT;

//Tile constants
const int SOURCE_TILE_SIZE = 32;
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int TOTAL_TILES = (LEVEL_WIDTH / TILE_WIDTH) * (LEVEL_HEIGHT / TILE_HEIGHT);
const int TOTAL_TILE_SPRITES = 3;

//The different tile sprites
const int TILE_DIRT = 0;
const int TILE_GRASS = 1;
const int TILE_WATER = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

SDL_Rect tileSheetClips[TOTAL_TILE_SPRITES];
Tile* tiles[TOTAL_TILES];

// Level 1 - Desert: Obstacle list
//const int LEVEL_ONE_OBSTACLE_CNT = 3;
//IndestructibleObstacle levelOneObstacles[LEVEL_ONE_OBSTACLE_CNT] = {
//	IndestructibleObstacle("Assets/Obstacle.png", 800, 700, 32, 32, 0),
//	IndestructibleObstacle("Assets/Obstacle.png", 300, 400, 32, 32, 0),
//	IndestructibleObstacle("Assets/Obstacle.png", 500, 600, 32, 32, 0)
//};

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

Map::Map(std::vector<IndestructibleObstacle*>& activeIndestructibleObstacles)
{
	LoadMap();
	//LoadObstacles(levelOneObstacles, LEVEL_ONE_OBSTACLE_CNT, activeIndestructibleObstacles);
	LoadTiles("Assets/TileSheet.png");
	destinationRect.w = 32;
	destinationRect.h = 32;
	destinationRect.x = 0;
	destinationRect.y = 0;
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

bool Map::LoadMap()
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

void Map::DrawMap()
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		TextureManager::Draw(tileSheet, tileSheetClips[tiles[i]->getType()], tiles[i]->getBox());
	}
}

void Map::LoadObstacles(IndestructibleObstacle obstacleList[], int obstacleCnt, std::vector<IndestructibleObstacle*>& activeIndestructibleObstacles)
{
	for (int i = 0; i < obstacleCnt; i++) {
		activeIndestructibleObstacles.push_back(&obstacleList[i]);
	}
}
