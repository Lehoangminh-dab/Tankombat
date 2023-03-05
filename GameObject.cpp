#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int xStartingPosition, int yStartingPosition)
{
	objectTexture = TextureManager::renderTexture(textureSheet);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;
}

void GameObject::update()
{
	xPosition++;
	yPosition++;

	sourceRectangle.h = 255; // Magic numbers
	sourceRectangle.w = 255;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xPosition;
	destinationRectangle.y = yPosition;
	destinationRectangle.h = sourceRectangle.h;
	destinationRectangle.w = sourceRectangle.w;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}

