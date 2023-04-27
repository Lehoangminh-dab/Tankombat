#pragma once
#include "GameObject.hpp"


class IndestructibleObstacle
{
public:
	IndestructibleObstacle(const char* objectTextureSheet, int xStartingPosition, int yStartingPosition, int width, int height, int startingRotationAngle);
	~IndestructibleObstacle();
	void render();
	void setRotationAngle(int angle);
	void setHitBox(int x, int y, int w, int h);
	std::string getID();
	SDL_Rect getHitBox();
	int getRotationAngle();
private:
	GameObject gameObject;
};
