#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 1120;
	void init(const char* title, bool fullscreen);
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