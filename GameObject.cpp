#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition)
{
	objectTexture = TextureManager::loadTexture(textureSheet);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;
	sourceRectangle.h = 32; // Magic numbers
	sourceRectangle.w = 32;
	destinationRectangle.h = sourceRectangle.h * 2;
	destinationRectangle.w = sourceRectangle.w * 2;
	hitBox.h = destinationRectangle.h;
	hitBox.w = destinationRectangle.w;
}

void GameObject::update()
{
	xPosition++;
	yPosition++;

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xPosition;
	destinationRectangle.y = yPosition;

	hitBox.x = destinationRectangle.x;
	hitBox.y = destinationRectangle.y;
}

void GameObject::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle, 45, NULL, SDL_FLIP_NONE);
}

SDL_Rect GameObject::getHitBox()
{
	return hitBox;
}
