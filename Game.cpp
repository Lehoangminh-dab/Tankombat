#include <vector>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "TileMap.hpp"
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Obstacle.hpp"

const int NUM_OF_PLAYERS = 4;
// Projctile constants
const double PROJECTILE_SPEED = 10.0;
const int PROJECTILE_WIDTH = 32;
const int PROJECTILE_HEIGHT = 32;

// Object storers
std::vector<Projectile*> activeProjectiles;
std::vector<IndestructibleObstacle*> activeIndestructibleObstacles;
std::vector<Tank*>activeTanks;

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

void executeKeyPressed(Tank* tank);
void executeKeyLifted(Tank* tank);

void updateCollision();


Game::Game()
{
	PLAYER_KEYS[0] = SDLK_x;
	PLAYER_KEYS[1] = SDLK_m;
	PLAYER_KEYS[2] = SDLK_RIGHT;
	PLAYER_KEYS[3] = SDLK_q;
	for (int i = 0; i < 4; i++)
	{
		KEY_PRESSED[i] = false;
	}
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

	activeTanks.push_back(new Tank("Assets/Objects/TankOne.png", "PLAYER_ONE", 0, 0));
	activeTanks.push_back(new Tank("Assets/Objects/TankTwo.png", "PLAYER_TWO", 300, 300));
	activeTanks.push_back(new Tank("Assets/Objects/TankThree.png", "PLAYER_THREE", 400, 400));
	activeTanks.push_back(new Tank("Assets/Objects/TankFour.png", "PLAYER_FOUR", 600, 600));
	activeIndestructibleObstacles.push_back(new IndestructibleObstacle("Assets/Obstacle.png", 900, 800, 32, 32, 0));
	map = new Map();
}


bool Game::isRunning()
{
	return gameRunning;
}

void Game::handleEvents()
{
	if (activeTanks.size() < 4)
	{
		std::cout << "WARNING: The number of tanks is currently lower than 4. Some controls will attempt to access a null memory location." << std::endl;
	}
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	case SDL_KEYDOWN: // These controls are assuming that there are 4 players, will need to change dynamically.
		for (int playerCnt = 0; playerCnt < NUM_OF_PLAYERS; playerCnt++)
		{
			if (event.key.keysym.sym == PLAYER_KEYS[playerCnt] && !KEY_PRESSED[playerCnt])
			{
				executeKeyPressed(activeTanks[playerCnt]);
				KEY_PRESSED[playerCnt] = true;
			}
		}
		break;
	case SDL_KEYUP:
		for (int playerCnt = 0; playerCnt < NUM_OF_PLAYERS; playerCnt++)
		{
			if (event.key.keysym.sym == PLAYER_KEYS[playerCnt] && KEY_PRESSED[playerCnt])
			{
				executeKeyLifted(activeTanks[playerCnt]);
				KEY_PRESSED[playerCnt] = false;
			}
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	// Update all tanks
	for (auto tankIt = activeTanks.begin(); tankIt != activeTanks.end(); )
	{
		(*tankIt)->updateMovement();
	}

	// Update all projectiles
	for (auto projectileIt = activeProjectiles.begin(); projectileIt != activeProjectiles.end(); ) 
	{
		if ((*projectileIt)->getDetonationStatus() == true) 
		{
			delete* projectileIt;
			projectileIt = activeProjectiles.erase(projectileIt);
		}
		else 
		{
			(*projectileIt)->update();
			++projectileIt;
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
	if (!activeTanks.empty())
	{
		for (auto tank : activeTanks)
		{
			tank->render();
		}
	}

	// Render all indestructible obstacles
	if (!activeIndestructibleObstacles.empty()) 
	{
		for (auto indestructibleObstacle : activeIndestructibleObstacles) 
		{
			indestructibleObstacle->render();
		}
	}

	// Render all projectiles
	if (!activeProjectiles.empty()) 
	{
		for (auto projectile : activeProjectiles) 
		{
			projectile->render();
		}
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
	if (!activeTanks.size() > 1)
	{
		for (auto firstTank = activeProjectiles.begin(); firstTank != activeProjectiles.end() - 1; ++firstTank)
		{
			for (auto secondTank = firstTank + 1; secondTank != activeProjectiles.end(); ++secondTank)
			{
				handleObjectsCollision(*firstTank, *secondTank);
			}
		}
	}

	// Handle all collisions between tanks and projectiles
	if (!activeProjectiles.empty() && !activeTanks.empty())
	{
		for (auto& tank : activeTanks)
		{
			for (auto& projectile : activeProjectiles)
			{
				handleObjectsCollision(tank, projectile);
			}
		}
	}

	// Handle all collisions between tanks and indestructible objects
	if (!activeTanks.empty() && !activeIndestructibleObstacles.empty())
	{
		for (auto& tank : activeTanks)
		{
			for (auto& indestructibleObstacle : activeIndestructibleObstacles)
			{
				handleObjectsCollision(tank, indestructibleObstacle);
			}
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
	
	// NOTE: This may not work as two tanks remain forever collided
	a->setSpeed(0);
	b->setSpeed(0);
}

void handleObjectsCollision(Tank* tank, Projectile* projectile)
{
	SDL_Rect tankHitBox = tank->getHitBox();
	SDL_Rect projectileHitBox = projectile->getHitBox();
	bool objectsCollided = checkCollision(tankHitBox, projectileHitBox);
	if (!objectsCollided)
	{
		return;
	}
	// Note: This may backfire as the projectile is spawned right on top of the tank
	tank->setDestroyedState(true);
	projectile->setCollisionStatus(true);
}

void handleObjectsCollision(Tank* tank, IndestructibleObstacle* obstacle)
{
	SDL_Rect tankHitbox = tank->getHitBox();
	SDL_Rect obstacleHitbox = obstacle->getHitBox();
	if (!checkCollision(tankHitbox, obstacleHitbox))
	{
		return;
	}
	
	// Note: This may not work as tank remains forever collided
	tank->setSpeed(0);
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

void executeKeyPressed(Tank* tank) // The moment the key is pressed, execute this ONCE
{
	tank->shoot(activeProjectiles);
	tank->setBulletShotState(true);
	tank->setMovementState(true);
}

void executeKeyLifted(Tank* tank)
{
	tank->setMovementState(false);
}
