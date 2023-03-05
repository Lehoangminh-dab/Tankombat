#include "map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

class Map
{
public:
	Map();
	~Map();

	void LoadMap();
	void DrawMap();
private:
	SDL_Rect sourceRectangle, destinationRectangle;
	SDL_Texture* building;
	SDL_Texture* glass;
	SDL_Texture* crate;
	SDL_Texture* platform;
};
