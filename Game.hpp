#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	bool isRunning();
	void handleEvents();
	void update();
	void render();
	void clean(); 
	static SDL_Renderer* renderer;
private:
	bool gameRunning;
	SDL_Window* window;
};