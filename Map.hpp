#pragma once
#include "Game.hpp"

class Map
{
public:
	Map();
	~Map();
	void LoadTiles(const char* tileSheetFilePath);
	void LoadMap(int arr[20][25]);
	void DrawMap();
private:
	SDL_Rect destinationRect;
	SDL_Texture* tileSheet;
	int map[20][25];
};