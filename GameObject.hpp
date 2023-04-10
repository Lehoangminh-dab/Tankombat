#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, int startingRotationAngle);
	~GameObject();
	void render();
	void setRotationAngle(int angle);
	void setHitBox(int x, int y, int w, int h);
	std::string getID();
	SDL_Rect getHitBox();
	int getRotationAngle();
private:
	std::string ID;
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	int rotationAngle;
	SDL_Rect hitBox;
};

class MovingGameObject
{
public:
	MovingGameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, int startingSpeed, int startingRotationAngle);
	~MovingGameObject();
	void render();
	void setRotationAngle(int angle);
	std::string getID();
	SDL_Rect getHitBox();
	void move();
	void setSpeed(int speed);
private:
	GameObject gameObject;
	int speed;
	double xVelocity;
	double yVelocity;
	bool collidedWithHorizontalWall();
	bool collidedWithVerticalWall();
};