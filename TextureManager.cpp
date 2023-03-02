#include "TextureManager.hpp"

SDL_Texture* TextureManager::renderTexture(const char* textureFilePath, SDL_Renderer* renderer)
{
	SDL_Surface* temporaryTextureSurface = IMG_Load(textureFilePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporaryTextureSurface);
	SDL_FreeSurface(temporaryTextureSurface);
	return texture;
}