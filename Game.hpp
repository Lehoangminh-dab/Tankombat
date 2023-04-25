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

	void init(const char* title, bool fullscreen);
	void initGamePlay();
	bool isRunning();
	bool isInMenu();
	bool isPaused();
	void handleMenuEvents();
	void renderMenu();
	void handleEvents();
	void update();
	void render();
	void clean(); 
	static SDL_Renderer* renderer;
private:
	Button playButton;
	bool gameRunning;
	bool gameInMenu;
	bool gamePaused;
	bool gameplayInitialized;
	SDL_Window* window;
};