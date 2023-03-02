#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	void initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	bool isRunning();
	void handleEvents();
	void update();
	void render();
	void clean(); 

private:
	void initializeWindow(SDL_Window* window, const char* title, int xPos, int yPos, int width, int height, int flags);
	void initializeRenderer(SDL_Renderer* renderer);
	bool gameRunning = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
};