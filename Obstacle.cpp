#include "Obstacle.hpp"

IndestructibleObstacle::IndestructibleObstacle(const char* objectTextureSheet, int xStartingPosition, int yStartingPosition, int width, int height, int startingRotationAngle)
	: gameObject(objectTextureSheet, "INDESTRUCTIBLE_OBSTACLE", xStartingPosition, yStartingPosition, width, height, startingRotationAngle)
{
}

IndestructibleObstacle::~IndestructibleObstacle()
{
	gameObject.~GameObject();
}

void IndestructibleObstacle::render()
{
	gameObject.render();
}

void IndestructibleObstacle::setRotationAngle(int angle)
{
	gameObject.setRotationAngle(angle);
}

void IndestructibleObstacle::setHitBox(int x, int y, int w, int h)
{
	gameObject.setHitBox(x, y, w, h);
}

std::string IndestructibleObstacle::getID()
{
	return gameObject.getID();
}

SDL_Rect IndestructibleObstacle::getHitBox()
{
	return gameObject.getHitBox();
}

int IndestructibleObstacle::getRotationAngle()
{
	return gameObject.getRotationAngle();
}
