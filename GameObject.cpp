#include "GameObject.hpp"
#include "TextureManager.hpp"
#include <cmath>

const int SOURCE_TEXTURE_SIZE = 32;
GameObject::GameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, int startingRotationAngle)
{
	ID = id;
	objectTexture = TextureManager::loadTexture(objectTextureSheet);

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	sourceRectangle.h = SOURCE_TEXTURE_SIZE; // Magic numbers
	sourceRectangle.w = SOURCE_TEXTURE_SIZE;

	hitBox.x = xStartingPosition;
	hitBox.y = yStartingPosition;
	hitBox.h = height;
	hitBox.w = width;

	rotationAngle = startingRotationAngle;
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &sourceRectangle, &hitBox, rotationAngle, NULL, SDL_FLIP_NONE);
}

void GameObject::setRotationAngle(int angle)
{
	rotationAngle = angle;
}

void GameObject::setSourceRectangle(SDL_Rect srcRect)
{
	sourceRectangle = srcRect;
}

std::string GameObject::getID()
{
	return ID;
}

void GameObject::setHitBox(int x, int y, int w, int h)
{
	hitBox.x = x;
	hitBox.y = y;
	hitBox.w = w;
	hitBox.h = h;
}

SDL_Rect GameObject::getHitBox()
{
	return hitBox;
}

int GameObject::getRotationAngle()
{
	return rotationAngle;
}

MovingGameObject::MovingGameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height, double startingSpeed, int startingRotationAngle)
	: gameObject(objectTextureSheet, id, xStartingPosition, yStartingPosition, width, height, startingRotationAngle)
{
	speed = startingSpeed;
	double startingRotationAngleInRadians = (double)startingRotationAngle * (M_PI / 180);
	xVelocity = speed * cos(startingRotationAngleInRadians);
	yVelocity = speed * sin(startingRotationAngleInRadians);
	// test
}

MovingGameObject::~MovingGameObject()
{
	gameObject.~GameObject();
}

void MovingGameObject::render()
{
	gameObject.render();
}

void MovingGameObject::setRotationAngle(int angle)
{
	gameObject.setRotationAngle(angle);
}

void MovingGameObject::setSourceRectangle(SDL_Rect srcRect)
{
	gameObject.setSourceRectangle(srcRect);
}

std::string MovingGameObject::getID()
{
	return gameObject.getID();
}

SDL_Rect MovingGameObject::getHitBox()
{
	return gameObject.getHitBox();
}

int MovingGameObject::getRotationAngle()
{
	return gameObject.getRotationAngle();
}

double MovingGameObject::getSpeed()
{
	return speed;
}

void MovingGameObject::move()
{
	int rotationAngleInDegrees = gameObject.getRotationAngle();
	double rotationAngleInRadians = rotationAngleInDegrees * (M_PI / 180);
	xVelocity = speed * cos(rotationAngleInRadians);
	yVelocity = speed * sin(rotationAngleInRadians);
	SDL_Rect newHitBox = gameObject.getHitBox();

	int newPositionX = (double)newHitBox.x + xVelocity;
	int newPositionY = (double)newHitBox.y + yVelocity;

	newHitBox.x = newPositionX;
	newHitBox.y = newPositionY;
	gameObject.setHitBox(newHitBox.x, newHitBox.y, newHitBox.w, newHitBox.h);
}

void MovingGameObject::setSpeed(double speedValue)
{
	speed = speedValue;
}

bool MovingGameObject::collidedWithHorizontalWall()
{
	SDL_Rect hitBox = gameObject.getHitBox();
	if (hitBox.y < 0 || hitBox.y > Game::SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

bool MovingGameObject::collidedWithVerticalWall()
{
	SDL_Rect hitBox = gameObject.getHitBox();
	if (hitBox.x < 0 || hitBox.x > Game::SCREEN_WIDTH)
	{
		return true;
	}
	return false;
}
