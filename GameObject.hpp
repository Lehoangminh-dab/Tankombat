#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int xPosition, int yPosition);
	~GameObject();
private:
	SDL_Texture* objectTexture;
	SDL_Rect* sourceRectangle;
	SDL_Rect* destinationRectangle;
	int xStartingPosition;
	int yStartingPosition;
	void update();
	void render();
};