#pragma once
#include "Game.hpp"

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int tileMap[MAP_HEIGHT][MAP_WIDTH]);
	void DrawMap();
private:

	SDL_Rect sourceRectangle, destinationRectangle;
	SDL_Texture* building;
	SDL_Texture* glass;
	SDL_Texture* crate;
	SDL_Texture* platform;
};
