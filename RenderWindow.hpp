#pragma once // This ensures there are no headers that are copied twice
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_width, int p_height);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
