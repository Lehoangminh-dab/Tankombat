#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, int startingRotationAngle);
	~GameObject();
	void render();
	void setRotationAngle(int angle);
	void setSourceRectangle(SDL_Rect srcRect);
	void setHitBox(int x, int y, int w, int h);
	std::string getID();
	SDL_Rect getHitBox();
	int getRotationAngle();
private:
	std::string ID;
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect hitBox;
	int rotationAngle;
};

class MovingGameObject
{
public:
	MovingGameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, double startingSpeed, int startingRotationAngle);
	~MovingGameObject();
	void render();
	void setRotationAngle(int angle);
	void setSourceRectangle(SDL_Rect srcRect);
	void move();
	std::string getID();
	SDL_Rect getHitBox();
	int getRotationAngle();
	double getSpeed();
	double getVelocityX();
	double getVelocityY();
	void setHitBox(int x, int y, int w, int h);
	void setSpeed(double speedValue);
	bool collidedWithHorizontalWall();
	bool collidedWithVerticalWall();
private:
	GameObject gameObject;
	double speed;
	double xVelocity;
	double yVelocity;
};