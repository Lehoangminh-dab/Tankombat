#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int xStartingPosition, int yStartingPosition);
	~GameObject();
private:
	SDL_Texture* objectTexture;
	SDL_Rect* sourceRectangle;
	SDL_Rect* destinationRectangle;
	int xPosition;
	int yPosition;
	void update();
	void render();
};