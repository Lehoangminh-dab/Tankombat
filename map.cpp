#include "Map.hpp"
#include "TextureManager.hpp"

const int TYPE_BUILDING = 0;
const int TYPE_GLASS = 1;
const int TYPE_CRATE = 2;
const int TYPE_PLATFORM = 3;

Map::Map()
{
	for (int tileRow = 0; tileRow < MAP_HEIGHT; tileRow++)
	{
		for (int tileColumn = 0; tileColumn < MAP_WIDTH; tileColumn++)
		{
			tileMap[tileRow][tileColumn] = 0;
		}
	}

	glass = TextureManager::renderTexture("Assets/Map - Rooftop/glass.png");
}

void Map::LoadMap(int tileMap[MAP_HEIGHT][MAP_WIDTH])
{

}

void Map::DrawMap()
{
	type = 0;
	
	for ()
	{
		switch (type)
		{
		case TYPE_BUILDING:
			TextureManager::Draw();
			break;
		W

		}
	}
}