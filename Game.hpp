#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Button.hpp"


class Game
{
public:
	Game();
	~Game();

	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 928;
	void init(const char* title, bool fullscreen);
	bool isRunning();
	bool isInMenu();
	void handleMenuEvents();
	void renderMenu();
	void handleEvents();
	void update();
	void render();
	void clean(); 
	static SDL_Renderer* renderer;
private:
	Button testButton;
	bool gameRunning;
	bool gameInMenu;
	bool isPaused;
	SDL_Window* window;
};