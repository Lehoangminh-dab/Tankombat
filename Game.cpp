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

// Texture File Paths
const std::string MENU_BACKGROUND_PATH = "Assets/Maps/sMap.png";
const std::string GLOBAL_FONT_PATH = "Assets/Fonts/TestFont.ttf";
const std::string MENU_TEXTBOX_PATH = "Assets/Menu/TextBox.png";
const int MENU_TEXTBOX_WIDTH = 600;
const int MENU_TEXTBOX_HEIGHT = 600;
// Fonts
TTF_Font* gFont = NULL;

// Object storers
std::vector<Tank*> activeTanks;
std::vector<Projectile*> activeProjectiles;
std::vector<IndestructibleObstacle*> activeIndestructibleObstacles;
Tile* tiles[TOTAL_TILES];

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
void handleObjectsCollision(Tank* tank, Tile* tiles[]);
void handleObjectsCollision(Projectile* projectile, Tile* tiles[]);
void handleProjectileWallCollision(Projectile* projectile);

void renderPauseMenu();

bool keyPressed = false;
void updateCollision();

// Button IDs
Game::Game()
	: playButton((SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT),
	resumeButton(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT)
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
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		}

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			gameRunning = false;
		}

		gameRunning = true;
	}
	else
	{
		gameRunning = false;
	}

	// Initialize game flags
	gameInMenu = true;
	gamePaused = false;
	gameplayInitialized = false;
	// Initialize fonts
	gFont = TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), 28);
}

void Game::initGamePlay()
{
	if (gameplayInitialized)
	{
		return;
	}
	map = new Map(tiles);
	activeTanks.push_back(new Tank(BLUE_TANK_TEXTURE_PATH, PLAYER_ONE_ID, 100, 300));
	activeTanks.push_back(new Tank(RED_TANK_TEXTURE_PATH, PLAYER_TWO_ID, 200, 400));
	activeTanks.push_back(new Tank(GREEN_TANK_TEXTURE_PATH, PLAYER_THREE_ID, 300, 500));
	activeTanks.push_back(new Tank(BEIGE_TANK_TEXTURE_PATH, PLAYER_FOUR_ID, 600, 500));
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

bool Game::isPaused()
{
	return gamePaused;
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
	SDL_Texture* menuBackground = TextureManager::loadTexture(MENU_BACKGROUND_PATH.c_str());
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

	// Render buttons
	playButton.show();

	// Render game title
	SDL_Rect fontDestRectangle;
	fontDestRectangle.x = 0;
	fontDestRectangle.y = 0;
	fontDestRectangle.w = 600;
	fontDestRectangle.h = 200;
	SDL_Color titleTextColor = { 247, 227, 5 };
	TextureManager::DrawText(gFont, "TankKombat", titleTextColor, fontDestRectangle);

	// Presenting all the textures
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
		if (gameWon)
		{
			executeKeyLifted(activeTanks[0]);
		}
		else if (!gamePaused)
		{
			for (int playerCnt = 0; playerCnt < NUM_OF_PLAYERS; playerCnt++)
			{
				if (event.key.keysym.sym == PLAYER_KEYS[playerCnt] && !KEY_PRESSED[playerCnt])
				{
					executeKeyPressed(activeTanks[playerCnt]);
					KEY_PRESSED[playerCnt] = true;
				}
			}
		}

		// Pausing tests
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			gamePaused = true;
		}
		
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			gamePaused = false;
		}
		break;
	case SDL_KEYUP:
		if (!gamePaused)
		{
			for (int playerCnt = 0; playerCnt < NUM_OF_PLAYERS; playerCnt++)
			{
				if (event.key.keysym.sym == PLAYER_KEYS[playerCnt] && KEY_PRESSED[playerCnt])
				{
					executeKeyLifted(activeTanks[playerCnt]);
					KEY_PRESSED[playerCnt] = false;
				}
			}
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	int destroyedTanks = 0;
	// Update all tanks
	for (int tankCnt = 0; tankCnt < activeTanks.size(); tankCnt++)
	{
		activeTanks[tankCnt]->updateMovement();
		if (activeTanks[tankCnt]->getDestroyedState())
		{
			destroyedTanks++;
		}
	}

	// Update all projectiles
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		if (activeProjectiles[projectileCnt]->getDetonationStatus() == true)
		{
			activeProjectiles[projectileCnt]->~Projectile();
			activeProjectiles.erase(activeProjectiles.begin() + projectileCnt);
		}
		else
		{
			activeProjectiles[projectileCnt]->update();
		}
	}
	updateCollision();
	// Check if any player(s) has won
	if (destroyedTanks == activeTanks.size() - 1)
	{
		gameWon = true;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer); // Clear what's in the renderer's buffer
	// Render the map
	map->DrawMap(tiles);

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

	// Render pause menu if game is paused
	if (gamePaused)
	{
		renderPauseMenu();
	}
	// Presenting the textures
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

	// Handle all collisions between tanks and obstacles
	if (!activeTanks.empty())
	{
		for (auto& tank : activeTanks)
		{
			handleObjectsCollision(tank, tiles);
		}
	}

	// Handle all collisions between projectiles and obstacles
	if (!activeProjectiles.empty())
	{
		for (auto& projectile : activeProjectiles)
		{
			handleObjectsCollision(projectile, tiles);
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

void handleObjectsCollision(Tank* tank, Tile* tiles[])
{
	SDL_Rect tankHitBox = tank->getHitBox();
	SDL_Rect tileHitBox;
	for (int tileCnt = 0; tileCnt < TOTAL_TILES; tileCnt++)
	{
		int tileType = tiles[tileCnt]->getType();
		if (tileType == TILE_OBSTACLE_WALL)
		{
			tileHitBox = tiles[tileCnt]->getBox();
			if (checkCollision(tankHitBox, tileHitBox))
			{
				tank->handleTileCollision();
			}
		}
	}
}

void handleObjectsCollision(Projectile* projectile, Tile* tiles[])
{
	SDL_Rect projectileHitBox = projectile->getHitBox();
	SDL_Rect tileHitBox;
	for (int tileCnt = 0; tileCnt < TOTAL_TILES; tileCnt++)
	{
		int tileType = tiles[tileCnt]->getType();
		if (tileType == TILE_OBSTACLE_WALL)
		{
			tileHitBox = tiles[tileCnt]->getBox();	
			if (checkCollision(projectileHitBox, tileHitBox))
			{
				projectile->setCollisionStatus(true);
			}
		}
	}
}

void handleProjectileWallCollision(Projectile* projectile)
{
	SDL_Rect projectileHitBox = projectile->getHitBox();
	if (projectileHitBox.x < 0 || 
		projectileHitBox.x + projectileHitBox.w > SCREEN_WIDTH || 
		projectileHitBox.y < 0 || 
		projectileHitBox.y + projectileHitBox.h > SCREEN_HEIGHT)
	{
		projectile->setCollisionStatus(true);
	}
}

void renderPauseMenu()
{
	// Render the menu background
	SDL_Texture* menuTextbox = TextureManager::loadTexture(MENU_TEXTBOX_PATH.c_str());

	SDL_Rect menuSrcRect;
	menuSrcRect.x = 0;
	menuSrcRect.y = 0;
	menuSrcRect.w = MENU_TEXTBOX_WIDTH;
	menuSrcRect.h = MENU_TEXTBOX_HEIGHT;

	SDL_Rect menuDestRect;
	// Pause Menu size
	menuDestRect.w = 600;
	menuDestRect.h = 600;
	menuDestRect.x = (SCREEN_WIDTH - menuDestRect.w) / 2;
	menuDestRect.y = (SCREEN_HEIGHT - menuDestRect.h) / 2;
	TextureManager::Draw(menuTextbox, menuSrcRect, menuDestRect);
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