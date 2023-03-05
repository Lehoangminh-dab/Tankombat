#pragma once

#include "Game.hpp"


class TextureManager
{
public:
	static SDL_Texture* renderTexture(const char* textureFilePath);
	SDL_Texture* Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle)
};