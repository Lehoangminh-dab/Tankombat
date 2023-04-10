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
	MovingGameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, double startingSpeed, int startingRotationAngle);
	~MovingGameObject();
	void render();
	void setRotationAngle(int angle);
	std::string getID();
	SDL_Rect getHitBox();
	int getRotationAngle();
	double getSpeed();
	void move(double speed, int rotationAngle);
	void setSpeed(double speedValue);
private:
	GameObject gameObject;
	double speed;
	double xVelocity;
	double yVelocity;
	bool collidedWithHorizontalWall();
	bool collidedWithVerticalWall();
};