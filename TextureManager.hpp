#pragma once

#include "Game.hpp"


class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* textureFilePath);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle);
};