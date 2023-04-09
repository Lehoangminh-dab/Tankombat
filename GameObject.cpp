#include "GameObject.hpp"
#include "TextureManager.hpp"

const int SOURCE_TEXTURE_SIZE = 32;
GameObject::GameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height)
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
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	SDL_RenderCopyEx(Game::renderer, objectTexture, &sourceRectangle, &hitBox, 0, NULL, SDL_FLIP_NONE);
}

std::string GameObject::getID()
{
	return ID;
}

SDL_Rect GameObject::getHitBox()
{
	return hitBox;
}


