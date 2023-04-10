#pragma once
#include "Game.hpp"

class Tile
{
public:
    //Initializes position and type
    Tile(int x, int y, int tileType);

    //Shows the tile
    void render();

    //Get the tile type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

private:
    //The attributes of the tile
    SDL_Rect mBox{ 0,0,0,0 };

    //The tile type
    int mType;
};

class Map
{
public:
    Map();
    ~Map();
    void LoadTiles(const char* tileSheetFilePath);
    bool LoadMap();
    void DrawMap();
private:
    SDL_Rect destinationRect;
    SDL_Texture* tileSheet;
};