#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int xStartingPosition, int yStartingPosition)
{
	objectTexture = TextureManager::renderTexture(textureSheet, renderer);
	xPosition = xStartingPosition;
	yPosition = yStartingPosition;
}

void GameObject::update()
{
	sourceRectangle->h = 32; // Magic numbers
	sourceRectangle->w = 32;

	destinationRectangle->x = xPosition;
	destinationRectangle->y = yPosition;
}

void GameObject::render()
{

}

