#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* args[])
{
	// Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	// Initializing SDL_image
	if (IMG_Init(IMG_INIT_PNG) == 0) // Returns the flags sucessfully initiated, or 0 on failure
	{
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;

	}
	return 0;
}