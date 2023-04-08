#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition);
	~GameObject();
	void update();
	void render();
	SDL_Rect getHitBox();
private:
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	SDL_Rect hitBox;
	int xPosition;
	int yPosition;
};