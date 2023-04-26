#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Button.hpp"
#include "SoundManager.hpp"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, bool fullscreen);
	void clean(); 

	void initGameplay();
	void handleEvents();
	void update();
	void render();

	void handleMenuEvents();
	void updateMenu();
	void renderMenu();

	void renderLoadingScreen();

	bool isRunning();
	bool isInMenu();
	bool isPaused();

	static SDL_Renderer* renderer;
private:
	SoundManager soundManager;
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

	// General menu functions
	void renderBackground(std::string backgroundFilePath);

	// Pause menu functions
	void renderPauseMenu();
	void handlePauseMenuEvents(SDL_Event event);
	void resumeGameplay();
	void restartGameplay();
	void quitToMainMenu();
};