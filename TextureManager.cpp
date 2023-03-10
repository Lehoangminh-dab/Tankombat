#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* textureFilePath)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* temporaryTextureSurface = IMG_Load(textureFilePath);
	if (temporaryTextureSurface == NULL)
	{
		std::cout << "Unable to load image " << textureFilePath << "! SDL_Image Error: " << IMG_GetError();
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(Game::renderer, temporaryTextureSurface);
		if (texture == NULL)
		{
			std::cout << "Unable to create texture from surface" << textureFilePath << "! SDL_Image Error: " << SDL_GetError();
		}
		SDL_FreeSurface(temporaryTextureSurface);
	}
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle)
{
	SDL_RenderCopy(Game::renderer, texture, &sourceRectangle, &destinationRectangle);
}