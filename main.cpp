#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.hpp"

int main(int argc, char* args[])
{
	// Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	// Initializing SDL_image
	if (IMG_Init(IMG_INIT_PNG) == 0) // Returns the flags sucessfully initiated, or 0 on failure
	{
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
	}

	// Initializing a render window
	RenderWindow window("Bing and Chill v1.0", 1280, 720);
	
	bool gameRunning = true;
	
	SDL_Event event;
	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}
	}
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}