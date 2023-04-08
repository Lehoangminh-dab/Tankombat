#pragma once
#include "Game.hpp"

class GameObject
{
public:
	std::string ID;
	GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition, int startingVelocityX, int startingVelocityY);
	~GameObject();
	void update();
	void render();
	void setVelocity(int veloX, int veloY);
	SDL_Rect getHitBox();
private:
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	SDL_Rect hitBox;
	
	int xVelocity;
	int yVelocity;

	int xPosition;
	int yPosition;
};