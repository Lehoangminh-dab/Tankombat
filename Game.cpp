#include <vector>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "TileMap.hpp"
#include "Obstacle.hpp"
#include "Projectile.hpp"
#include "Tank.hpp"

// Projctile constants
const double PROJECTILE_SPEED = 10.0;
const int PROJECTILE_WIDTH = 32;
const int PROJECTILE_HEIGHT = 32;

// Object storers
std::vector<Projectile*> activeProjectiles;
std::vector<IndestructibleObstacle*> activeIndestructibleObstacles;

Tank* player;
Tank* enemy;

IndestructibleObstacle* obstacle;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

bool checkCollision(SDL_Rect a, SDL_Rect b);

void handleObjectsCollision(Tank* a, Tank* b);
void handleObjectsCollision(Tank* object, Projectile* projectile);
void handleObjectsCollision(Tank* object, IndestructibleObstacle* obstacle);
void handleObjectsCollision(Projectile* a, Projectile* b);
void handleObjectsCollision(Projectile* projectile, IndestructibleObstacle* obstacle);
void handleProjectileWallCollision(Projectile* projectile);

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
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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


	player = new Tank("Assets/Objects/Tank.png", "PLAYER_ONE", 100, 300);
	// test: Let a tank move
	player->setMovementState(true);
	enemy = new Tank("Assets/Objects/Tank.png", "PLAYER_TWO", 200, 400);
	activeProjectiles.push_back(new Projectile("Assets/Objects/Projectile.png", 0, 0, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, PROJECTILE_SPEED, 60));
	activeIndestructibleObstacles.push_back(new IndestructibleObstacle("Assets/Obstacle.png", 900, 800, 32, 32, 0));
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
	// Update all tanks
	player->updateMovement();
	enemy->updateMovement();
	// Update all projectiles
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		if (activeProjectiles[projectileCnt]->getDetonationStatus() == true)
		{
			//activeProjectiles[projectileCnt]->~Projectile();
			activeProjectiles.erase(activeProjectiles.begin() + projectileCnt);
		}
		else
		{
			activeProjectiles[projectileCnt]->update();
		}
	}
	updateCollision();
}

void Game::render()
{
	SDL_RenderClear(renderer); // Clear what's in the renderer's buffer
	// Render the map
	map->DrawMap();
	// Render all tanks
	player->render();
	enemy->render();
	// Render all indestructible obstacles
	for (int indestructibleObstacleCnt = 0; indestructibleObstacleCnt < activeIndestructibleObstacles.size(); indestructibleObstacleCnt++)
	{
		activeIndestructibleObstacles[indestructibleObstacleCnt]->render();
	}
	// Render all projectiles
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		activeProjectiles[projectileCnt]->render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void updateCollision()
{
	// Handle all collisions between tanks and tanks
	handleObjectsCollision(player, enemy);

	// Handle all collisions between tanks and projectiles
	if (!activeProjectiles.empty())
	{
		for (auto& projectile : activeProjectiles)
		{
			handleObjectsCollision(player, projectile);
			handleObjectsCollision(enemy, projectile);
		}
	}

	// Handle all collisions between tanks and indestructible objects
	if (!activeIndestructibleObstacles.empty())
	{
		for (auto& indestructibleObstacle : activeIndestructibleObstacles)
		{
			handleObjectsCollision(player, indestructibleObstacle);
			handleObjectsCollision(enemy, indestructibleObstacle);
		}
	}

	// Handle all collisions between projectiles and projectiles
	if (activeProjectiles.size() > 1)
	{
		for (auto firstProjectile = activeProjectiles.begin(); firstProjectile != activeProjectiles.end() - 1; ++firstProjectile)
		{
			for (auto secondProjectile = firstProjectile + 1; secondProjectile != activeProjectiles.end(); ++secondProjectile)
			{
				handleObjectsCollision(*firstProjectile, *secondProjectile);
			}
		}
	}

	// Handle all collisions between projectiles and indestructible objects
	if (!activeProjectiles.empty() && !activeIndestructibleObstacles.empty())
	{
		for (auto& projectile : activeProjectiles)
		{
			for (auto& indestructibleObstacle : activeIndestructibleObstacles)
			{
				handleObjectsCollision(projectile, indestructibleObstacle);
			}
		}
	}

	// Handle all collisions between projectiles and walls
	if (!activeProjectiles.empty())
	{
		for (auto& projectile : activeProjectiles)
		{
			handleProjectileWallCollision(projectile);
		}
	}
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



void handleObjectsCollision(Tank* a, Tank* b)
{
	SDL_Rect hitBoxA = a->getHitBox();
	SDL_Rect hitBoxB = b->getHitBox();
	if (!checkCollision(hitBoxA, hitBoxB))
	{
		return;
	}
	a->setSpeed(0);
	b->setSpeed(0);
}

void handleObjectsCollision(Tank* object, Projectile* projectile)
{
	SDL_Rect objectHitBox = object->getHitBox();
	SDL_Rect projectileHitBox = projectile->getHitBox();
	bool objectsCollided = checkCollision(objectHitBox, projectileHitBox);
	if (!objectsCollided)
	{
		return;
	}
	object->setDestroyedState(true);
	projectile->setCollisionStatus(true);
}

void handleObjectsCollision(Tank* object, IndestructibleObstacle* obstacle)
{
	SDL_Rect movingObjectHitbox = object->getHitBox();
	SDL_Rect obstacleHitbox = obstacle->getHitBox();
	if (!checkCollision(movingObjectHitbox, obstacleHitbox))
	{
		return;
	}
	double oppositeObjectSpeed = (object->getSpeed()) * -1;
	int objectRotation = object->getRotationAngle();
	object->setSpeed(0);
}


void handleObjectsCollision(Projectile* a, Projectile* b)
{
	SDL_Rect hitBoxA = a->getHitBox();
	SDL_Rect hitBoxB = b->getHitBox();
	if (!checkCollision(hitBoxA, hitBoxB))
	{
		return;
	}
	a->setCollisionStatus(true);
	b->setCollisionStatus(true);
}

void handleObjectsCollision(Projectile* projectile, IndestructibleObstacle* obstacle)
{
	SDL_Rect projectileHitBox = projectile->getHitBox();
	SDL_Rect obstacleHitBox = obstacle->getHitBox();
	if (!checkCollision(projectileHitBox, obstacleHitBox))
	{
		return;
	}
	projectile->setCollisionStatus(true);
}

void handleProjectileWallCollision(Projectile* projectile)
{
	SDL_Rect projectileHitBox = projectile->getHitBox();
	if (projectileHitBox.x < 0 || 
		projectileHitBox.x + projectileHitBox.w > Game::SCREEN_WIDTH || 
		projectileHitBox.y < 0 || 
		projectileHitBox.y > Game::SCREEN_HEIGHT)
	{
		projectile->setCollisionStatus(true);
	}
}
