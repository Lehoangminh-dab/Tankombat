#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Game
{
public:
	Game();
	~Game();
	static int PLAYER_KEYS[4];
	bool KEY_PRESSED[4]; // Flags array to keep track of which players' keys have been pressed
	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 928;
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