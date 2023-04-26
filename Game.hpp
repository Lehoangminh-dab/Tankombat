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
	void initGameplay();
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
	// Main menu buttons
	Button playButton;

	// Pause menu buttons
	Button resumeButton;
	Button restartButton;
	Button quitButton;

	// Game state flags
	bool gameRunning;
	bool gameInMenu;
	bool gamePaused;
	bool gameWon;
	bool gameplayInitialized;

	SDL_Window* window;

	// Pause menu functions
	void renderPauseMenu();
	void handlePauseMenuEvents(SDL_Event event);
	void resumeGameplay();
	void restartGameplay();
	void quitToMainMenu();
};