#pragma once

#include "Game.hpp"

class TextureManager
{
public:
	static SDL_Texture* renderTexture(const char* textureFilePath, SDL_Renderer* renderer);
};