#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition)
{
	objectTexture = TextureManager::loadTexture(textureSheet);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;
}

void GameObject::update()
{
	xPosition++;
	yPosition++;

	sourceRectangle.h = 32; // Magic numbers
	sourceRectangle.w = 32;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xPosition;
	destinationRectangle.y = yPosition;
	destinationRectangle.h = sourceRectangle.h * 2;
	destinationRectangle.w = sourceRectangle.w * 2;
}

void GameObject::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle, 45, NULL, SDL_FLIP_NONE);
}

