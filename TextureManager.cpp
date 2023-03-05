#include "TextureManager.hpp"

SDL_Texture* TextureManager::renderTexture(const char* textureFilePath)
{
	SDL_Surface* temporaryTextureSurface = IMG_Load(textureFilePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporaryTextureSurface);
	SDL_FreeSurface(temporaryTextureSurface);
	return texture;
}

SDL_Texture* TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle)
{
	SDL_RenderCopy(Game::renderer, texture, &sourceRectangle, &destinationRectangle);
}