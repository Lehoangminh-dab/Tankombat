#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"

GameObject* player;
GameObject* enemy;
const char* PLAYER_TEXTURE_PATH = "Assets/Kratos.png";
const char* ENEMY_TEXTURE_PATH = "Assets/Kratos.png";

SDL_Renderer* Game::renderer = nullptr;


Game::Game()
{

}

Game::~Game()
{
	
}


void Game::initialize(const char* title, int xWindowPos, int yWindowPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{	
		window = SDL_CreateWindow(title, xWindowPos, yWindowPos, width, height, flags);
		if (window == NULL)
		{
			std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		}

		gameRunning = true;
	}
	else
	{
		gameRunning = false;
	}

	player = new GameObject(PLAYER_TEXTURE_PATH, 0, 0);
	enemy = new GameObject(ENEMY_TEXTURE_PATH, 100, 100);
}



bool Game::isRunning()
{
	return gameRunning;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
		break;
	}

}

void Game::update()
{
	player->update();
}

void Game::render()
{
	SDL_RenderClear(renderer); // Clear what's in the renderer's buffer
	// Stuff to render
	player->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}