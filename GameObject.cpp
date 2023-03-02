#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int xPosition, int yPosition)
{
	objectTexture = TextureManager::renderTexture(textureSheet, renderer);
	xStartingPosition = xPosition;
	yStartingPosition = yPosition;
}

void GameObject::update()
{
	sourceRectangle->h = 32; // Magic numbers
	sourceRectangle->w = 32;

	destinationRectangle->x = xStartingPosition;
	destinationRectangle->y = yStartingPosition;
}

void GameObject::render()
{

}

