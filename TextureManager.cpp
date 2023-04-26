#include "TextureManager.hpp"
#include "Constants.hpp"

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

void TextureManager::DrawText(TTF_Font* font, std::string textureText, SDL_Color textColor, int x, int y, bool centered)
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    SDL_Texture* textTexture = NULL;
    SDL_Rect sourceRectangle;
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
        if (textTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        else
        {
            //Get image dimensions
            sourceRectangle.w = textSurface->w;
            sourceRectangle.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    SDL_Rect destinationRectangle;
    if (centered)
    {
        destinationRectangle.x = (SCREEN_WIDTH - sourceRectangle.w) / 2;
    }
    else
    {
        destinationRectangle.x = x;
    }

    destinationRectangle.y = y;
    destinationRectangle.w = sourceRectangle.w;
    destinationRectangle.h = sourceRectangle.h;

    Draw(textTexture, sourceRectangle, destinationRectangle);
    SDL_DestroyTexture(textTexture);
}
