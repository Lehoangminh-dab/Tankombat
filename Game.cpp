#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "TileMap.hpp"
GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

bool checkCollision(SDL_Rect a, SDL_Rect b);
void handleCollision(GameObject* a, GameObject* b);
void updateCollision();

Game::Game()
{

}

Game::~Game()
{
	
}


void Game::init(const char* title, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{	
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
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

	player = new GameObject("Assets/Kratos.png", 0, 30, 1, 0);
	enemy = new GameObject("Assets/Enemy.png", 400, 30, -1, 0);
	map = new Map();
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
	enemy->update();
	updateCollision();
}

void Game::render()
{
	SDL_RenderClear(renderer); // Clear what's in the renderer's buffer
	// Stuff to render
	map->DrawMap();
	player->render();
	enemy->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void handleCollision(GameObject* a, GameObject* b)
{
	SDL_Rect hitBoxA = a->getHitBox();
	SDL_Rect hitBoxB = b->getHitBox();
	if (!checkCollision(hitBoxA, hitBoxB))
	{
		return;
	}
	if (a->ID == "TANK" && b->ID == "TANK")
	{
		a->setVelocity(0, 0);
		b->setVelocity(0, 0);
	}
}

void updateCollision()
{
	handleCollision(player, enemy);
}
