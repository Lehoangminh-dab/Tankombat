#pragma once
#include "Game.hpp"

class Map
{
public:
	Map();
	~Map();
	static const int MAP_WIDTH = 55;
	static const int MAP_HEIGHT = 27;
	void LoadMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	void DrawMap();
private:
	int map[MAP_HEIGHT][MAP_WIDTH];
	SDL_Rect sourceRectangle, destinationRectangle;
	SDL_Texture* brick;
};
