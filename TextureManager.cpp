#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* textureFilePath)
{
	SDL_Surface* temporaryTextureSurface = IMG_Load(textureFilePath);
	if (!temporaryTextureSurface)
	{
		std::cout << "Error: Cannot load image at " << textureFilePath << "! " << IMG_GetError() << std::endl;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporaryTextureSurface);
	SDL_FreeSurface(temporaryTextureSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle)
{
	SDL_RenderCopy(Game::renderer, texture, &sourceRectangle, &destinationRectangle);
}