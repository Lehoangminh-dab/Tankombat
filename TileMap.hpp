#pragma once
#include "Game.hpp"
#include "Obstacle.hpp"

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
    Map(Tile* tiles[]);
    ~Map();
    void LoadTiles(const char* tileSheetFilePath);
    bool LoadMap(Tile* tiles[]);
    void DrawMap(Tile* tiles[]);
private:
    SDL_Rect destinationRect;
    SDL_Texture* tileSheet;
};