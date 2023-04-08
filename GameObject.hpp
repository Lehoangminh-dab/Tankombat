#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition, int startingVelocityX, int startingVelocityY);
	~GameObject();
	void update();
	void render();
	void setVelocity(int veloX, int veloY);
	std::string getID();
	SDL_Rect getHitBox();
private:
	std::string ID;
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	SDL_Rect hitBox;
	
	int xVelocity;
	int yVelocity;

	int xPosition;
	int yPosition;

	void handleWallCollision();
};

class MovingGameObject : public GameObject
{
public:
	MovingGameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition, int startingVelocityX, int startingVelocityY);
	void updatePosition();
	void setVelocity(int veloX, int veloY);
private:
	int xVelocity;
	int yVelocity;
	void handleWallCollision();
};