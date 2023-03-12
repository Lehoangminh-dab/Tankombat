#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void initialize(const char* title, int xWindowPos, int yWindowPos, int width, int height, bool fullscreen);
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