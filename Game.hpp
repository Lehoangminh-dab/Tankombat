#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Menu.hpp"


class Game
{
public:
	Game();
	~Game();

	static const int SCREEN_WIDTH = 1600;
	static const int SCREEN_HEIGHT = 928;
	void init(const char* title, bool fullscreen);
	bool isInMenu();
	bool isRunning();
	void handleMenuEvents();
	void drawMenu();
	void handleEvents();
	void update();
	void render();
	void clean(); 
	void setMenuState(bool inMenu);
	static SDL_Renderer* renderer;
private:
	GameMenu gameMenu; // Test: Will switch to menu
	bool inMenu;
	bool gameRunning;
	SDL_Window* window;
};