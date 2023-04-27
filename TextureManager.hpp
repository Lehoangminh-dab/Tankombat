#pragma once

#include "Game.hpp"
#include <SDL_ttf.h>

class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* textureFilePath);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle);
	static void DrawText(TTF_Font* font, std::string textureText, SDL_Color textColor, int x, int y, bool centered);
};