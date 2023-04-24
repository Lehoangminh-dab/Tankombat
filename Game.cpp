#include <vector>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "TileMap.hpp"
#include "Obstacle.hpp"
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Constants.hpp"

bool KEY_PRESSED[4] = { false, false, false, false }; // Array to keep track of which keys have been 

// Object storers
std::vector<Tank*> activeTanks;
std::vector<Projectile*> activeProjectiles;
std::vector<IndestructibleObstacle*> activeIndestructibleObstacles;

void executeKeyPressed(Tank* tank);
void executeKeyLifted(Tank* tank);

Map* map;
SDL_Renderer* Game::renderer = nullptr;

bool checkCollision(SDL_Rect a, SDL_Rect b);

void handleObjectsCollision(Tank* a, Tank* b);
void handleObjectsCollision(Tank* object, Projectile* projectile);
void handleObjectsCollision(Tank* object, IndestructibleObstacle* obstacle);
void handleObjectsCollision(Projectile* a, Projectile* b);
void handleObjectsCollision(Projectile* projectile, IndestructibleObstacle* obstacle);
void handleProjectileWallCollision(Projectile* projectile);

bool keyPressed = false;
void updateCollision();

// Button IDs
Game::Game()
	: playButton((SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT)
{
	//const int LEVEL_ONE_OBSTACLE_CNT = 3;
	//IndestructibleObstacle levelOneObstacles[LEVEL_ONE_OBSTACLE_CNT] = {
	//	IndestructibleObstacle("Assets/Obstacle.png", 900, 800, 32, 32, 0),
	//	IndestructibleObstacle("Assets/Obstacle.png", 300, 400, 32, 32, 0),
	//	IndestructibleObstacle("Assets/Obstacle.png", 500, 600, 32, 32, 0)
	//};
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
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		}
		gameRunning = true;
	}
	else
	{
		gameRunning = false;
	}

	gameInMenu = true;
	isPaused = false;
	gameplayInitialized = false;
	//activeTanks.push_back(new Tank(BLUE_TANK_TEXTURE_PATH, "PLAYER_ONE", 100, 300));
	//activeTanks.push_back(new Tank(RED_TANK_TEXTURE_PATH, "PLAYER_TWO", 200, 400));
	//activeTanks.push_back(new Tank(GREEN_TANK_TEXTURE_PATH, "PLAYER_THREE", 300, 500));
	//activeTanks.push_back(new Tank(BEIGE_TANK_TEXTURE_PATH, "PLAYER_FOUR", 600, 500));
	//for (int i = 0; i < LEVEL_ONE_OBSTACLE_CNT; i++)
	//{
	//	activeIndestructibleObstacles.push_back(&levelOneObstacles[i]);
	//}
	//activeIndestructibleObstacles.push_back(new IndestructibleObstacle("Assets/Obstacle.png", 900, 800, 32, 32, 0));
	//map = new Map(activeIndestructibleObstacles);
}

void Game::initGamePlay()
{
	if (gameplayInitialized)
	{
		return;
	}
	activeTanks.push_back(new Tank(BLUE_TANK_TEXTURE_PATH, "PLAYER_ONE", 100, 300));
	activeTanks.push_back(new Tank(RED_TANK_TEXTURE_PATH, "PLAYER_TWO", 200, 400));
	activeTanks.push_back(new Tank(GREEN_TANK_TEXTURE_PATH, "PLAYER_THREE", 300, 500));
	activeTanks.push_back(new Tank(BEIGE_TANK_TEXTURE_PATH, "PLAYER_FOUR", 600, 500));
	gameplayInitialized = true;
	std::cout << "Gameplay Initialized!" << std::endl;
}


bool Game::isRunning()
{
	return gameRunning;
}

bool Game::isInMenu()
{
	return gameInMenu;
}

void Game::handleMenuEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	playButton.handle_events(event);
	if (playButton.isClicked())
	{
		gameInMenu = false;
	}
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
		break;
	}
}

void Game::renderMenu()
{
	SDL_RenderClear(renderer);
	// Render Menu Background
	SDL_Texture* menuBackground = TextureManager::loadTexture("Assets/Maps/sMap.png");
	SDL_Rect menuSourceRect;
	SDL_Rect menuDestinationRect;
	menuSourceRect.x = 0;
	menuSourceRect.y = 0;
	menuSourceRect.w = 320;
	menuSourceRect.h = 320;

	menuDestinationRect.x = 0;
	menuDestinationRect.y = 0;
	menuDestinationRect.w = SCREEN_WIDTH;
	menuDestinationRect.h = SCREEN_HEIGHT;

	TextureManager::Draw(menuBackground, menuSourceRect, menuDestinationRect);
	std::cout << "Menu is being rendered" << std::endl;
	// Render buttons
	playButton.show();
	SDL_RenderPresent(renderer);
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
	case SDL_KEYDOWN:
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
	if (!isPaused)
	{
		// Update all tanks
		for (int tankCnt = 0; tankCnt < activeTanks.size(); tankCnt++)
		{
			activeTanks[tankCnt]->updateMovement();
		}
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
}

void Game::render()
{
	SDL_RenderClear(renderer); // Clear what's in the renderer's buffer
	// Render the map
	SDL_Texture* mapTexture = TextureManager::loadTexture(DESERT_BACKGROUND_PATH);
	SDL_Rect mapSrc, mapDest;
	mapSrc.x = 0;
	mapSrc.y = 0;
	mapSrc.w = 320;
	mapSrc.h = 320;

	mapDest.x = 0;
	mapDest.y = 0;
	mapDest.w = SCREEN_WIDTH;
	mapDest.h = SCREEN_HEIGHT;
	TextureManager::Draw(mapTexture, mapSrc , mapDest);
	// Render all tanks
	for (int tankCnt = 0; tankCnt < activeTanks.size(); tankCnt++)
	{
		activeTanks[tankCnt]->render();
	}
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
	if (activeTanks.size() > 1)
	{
		for (auto firstTank = activeTanks.begin(); firstTank != activeTanks.end() - 1; ++firstTank)
		{
			for (auto secondTank = firstTank + 1; secondTank != activeTanks.end(); ++secondTank)
			{
				handleObjectsCollision(*firstTank, *secondTank);
			}
		}
	}

	// Handle all collisions between tanks and projectiles
	if (!activeProjectiles.empty() && !activeTanks.empty())
	{
		for (auto& projectile : activeProjectiles)
		{
			for (auto& tank : activeTanks)
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
	if (object->getID() != projectile->getID())
	{
		object->setDestroyedState(true);
		projectile->setCollisionStatus(true);
	}
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
	if (a->getID() != b->getID() && checkCollision(a->getHitBox(), b->getHitBox()))
	{
		a->setCollisionStatus(true);
		b->setCollisionStatus(true);
	}
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
		projectileHitBox.y + projectileHitBox.h > Game::SCREEN_HEIGHT)
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