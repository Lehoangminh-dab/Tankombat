#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int xStartingPosition, int yStartingPosition)
{
	objectTexture = TextureManager::renderTexture(textureSheet, renderer);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;

	ren = renderer;
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
	SDL_RenderCopy(ren, objectTexture, &sourceRectangle, &destinationRectangle);
}

