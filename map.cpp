#include "Map.hpp"
#include "TextureManager.hpp"

const int TILE_SIZE = 25;

const int TYPE_BRICK = 0;
const int TYPE_GLASS = 1;
const int TYPE_CRATE = 2;
const int TYPE_PLATFORM = 3;

int rooftop[Map::MAP_HEIGHT][Map::MAP_WIDTH] = {
};


Map::Map()
{
	brick = TextureManager::loadTexture("Assets/Maps/Rooftop/brick.png");
	LoadMap(rooftop);

		


	sourceRectangle.x = sourceRectangle.y = 0;
	sourceRectangle.w = sourceRectangle.h = TILE_SIZE;
	destinationRectangle.x = destinationRectangle.y = 0;
}

void Map::LoadMap(int level[MAP_HEIGHT][MAP_WIDTH])
{
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			map[row][column] = rooftop[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			type = map[row][column];


			destinationRectangle.x = column * TILE_SIZE;
			destinationRectangle.y = row * TILE_SIZE;

			switch (type)
			{
			case TYPE_BRICK:
				TextureManager::Draw(brick, sourceRectangle, destinationRectangle);
				break;
			default:
				break;
			}
		}
	}
}