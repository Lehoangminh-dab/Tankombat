#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int xStartingPosition, int yStartingPosition);
	~GameObject();
	void update();
	void render();
private:
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	SDL_Renderer* ren; 	// This prevents passing in "renderer" parameter everytime we call GameObject functions
	int xPosition;
	int yPosition;
};