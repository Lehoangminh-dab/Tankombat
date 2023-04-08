#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition, int startingVelocityX, int startingVelocityY)
{
	ID = "TANK";
	objectTexture = TextureManager::loadTexture(textureSheet);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;

	sourceRectangle.h = 32; // Magic numbers
	sourceRectangle.w = 32;
	destinationRectangle.h = sourceRectangle.h * 2;
	destinationRectangle.w = sourceRectangle.w * 2;

	hitBox.h = destinationRectangle.h;
	hitBox.w = destinationRectangle.w;

	xVelocity = startingVelocityX;
	yVelocity = startingVelocityY;
}

void GameObject::update()
{
	xPosition += xVelocity;
	yPosition += yVelocity;

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xPosition;
	destinationRectangle.y = yPosition;

	hitBox.x = destinationRectangle.x;
	hitBox.y = destinationRectangle.y;

	handleWallCollision();
}

void GameObject::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle, 0, NULL, SDL_FLIP_NONE);
}

void GameObject::setVelocity(int veloX, int veloY)
{
	xVelocity = veloX;
	yVelocity = veloY;
}

SDL_Rect GameObject::getHitBox()
{
	return hitBox;
}

void GameObject::handleWallCollision()
{
	int width = hitBox.w;
	int height = hitBox.h;
	if (xPosition < 0 || (xPosition + width) > Game::SCREEN_WIDTH)
	{
		xPosition -= xVelocity;
	}
	if (yPosition < 0 || (yPosition + height) > Game::SCREEN_HEIGHT)
	{
		yPosition -= yVelocity;
	}
}

std::string GameObject::getID()
{
	return ID;
}

void MovingGameObject::updatePosition()
{
}

void MovingGameObject::setVelocity(int veloX, int veloY)
{
}

void MovingGameObject::handleWallCollision()
{
}
