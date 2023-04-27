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
const std::string PLAY_BUTTON_PATH = "Assets/Menu/PlayButton.png";
const std::string RESUME_BUTTON_PATH = "Assets/Menu/ResumeButton.png";
const std::string QUIT_BUTTON_PATH = "Assets/Menu/QuitButton.png";
const std::string RESTART_BUTTON_PATH = "Assets/Menu/RestartButton.png";
const std::string TUTORIAL_BUTTON_PATH = "Assets/Menu/TutorialButton.png";
const std::string TUTORIAL_BACK_BUTTON_PATH = "Assets/Menu/TutorialBackButton.png";
const std::string EXIT_BUTTON_PATH = "Assets/Menu/ExitButton.png";


const std::string MENU_BACKGROUND_PATH = "Assets/Menu/Tank Background.png";

const std::string TITLE_FONT_PATH = "Assets/Fonts/Helvetica Neue LT Std 107 Extra Black Condensed.ttf";
const std::string TITLE_STARS_TEXTURE_PATH = "Assets/Menu/Main Title Stars.png";
const std::string GLOBAL_FONT_PATH = "Assets/Fonts/Eurostile LT Std Condensed.ttf";

const std::string MENU_TEXTBOX_PATH = "Assets/Menu/TextBox.png";
const int MENU_TEXTBOX_WIDTH = 860;
const int MENU_TEXTBOX_HEIGHT = 510;

const std::string WON_MENU_TEXTBOX_PATH = "Assets/Menu/TextBox.png";
const int WON_MENU_TEXTBOX_WIDTH = 860;
const int WON_MENU_TEXTBOX_HEIGHT = 510;

const std::string TUTORIAL_TEXTBOX_PATH = "Assets/Menu/Textbox.png";
const int TUTORIAL_TEXTBOX_WIDTH = 860;
const int TUTORIAL_TEXTBOX_HEIGHT = 510;

// Fonts
TTF_Font* gameTitleFont = NULL;
TTF_Font* globalFont = NULL;

// Font colors
const SDL_Color TITLE_TEXT_COLOR = { 255, 255, 255 };
const SDL_Color ANNOUNCEMENT_TEXT_COLOR = { 0, 0, 0 };
const SDL_Color TUTORIAL_TEXT_COLOR = { 255, 255, 255 };
// Object storers
std::vector<Tank*> activeTanks;
std::vector<Projectile*> activeProjectiles;
std::vector<IndestructibleObstacle*> activeIndestructibleObstacles;
Tile* tiles[TOTAL_TILES];

void executeKeyPressed(Tank* tank);
void executeKeyLifted(Tank* tank);

Map* map;
SDL_Renderer* Game::renderer = nullptr;

// Collision functions
bool checkCollision(SDL_Rect a, SDL_Rect b);

void handleObjectsCollision(Tank* a, Tank* b);
void handleObjectsCollision(Tank* object, Projectile* projectile);
void handleObjectsCollision(Tank* object, IndestructibleObstacle* obstacle);
void handleObjectsCollision(Projectile* a, Projectile* b);
void handleObjectsCollision(Projectile* projectile, IndestructibleObstacle* obstacle);
void handleObjectsCollision(Tank* tank, Tile* tiles[]);
void handleObjectsCollision(Projectile* projectile, Tile* tiles[]);
void handleProjectileWallCollision(Projectile* projectile);

void updateCollision();

// Utility functions
void cleanGameplayResources();

// Button IDs
Game::Game()
	: playButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - LARGE_BUTTON_HEIGHT) / 2 + 50, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, PLAY_BUTTON_PATH, true),
	tutorialButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - LARGE_BUTTON_HEIGHT) / 2 + 200, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, TUTORIAL_BUTTON_PATH, true),
	tutorialBackButton((SCREEN_WIDTH - SMALL_BUTTON_WIDTH) / 2, 800, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT, TUTORIAL_BACK_BUTTON_PATH, false),
	exitButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - LARGE_BUTTON_HEIGHT) / 2 + 350, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, EXIT_BUTTON_PATH, true),
	resumeButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, 375, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, RESUME_BUTTON_PATH, true),
	restartButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, 525, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, RESTART_BUTTON_PATH, true),
	quitButton((SCREEN_WIDTH - LARGE_BUTTON_WIDTH) / 2, 675, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT, QUIT_BUTTON_PATH, true)
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

	soundManager.loadSounds();
	// Initialize game flags
	loadingScreenFrame = 0;
	gameInMenu = true;
	gamePaused = false;
	gameplayInitialized = false;
	gameInTutorial = false;
	gameRestarted = false;
	// Initialize fonts
	gameTitleFont = TTF_OpenFont(TITLE_FONT_PATH.c_str(), 160);
	globalFont = TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), 40);
}

void Game::handleMenuEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (!gameInTutorial)
	{
		playButton.handle_events(event);
		tutorialButton.handle_events(event);
		exitButton.handle_events(event);

		if (playButton.isClicked())
		{
			gameInMenu = false;
			Mix_HaltMusic();
			playButton.resetClickedState();
		}
		else if (tutorialButton.isClicked())
		{
			renderTutorialScreen();
			gameInTutorial = true;
			tutorialButton.resetClickedState();
		}
		else if (exitButton.isClicked())
		{
			gameRunning = false;
		}
	}
	else
	{
		handleTutorialScreenEvents(event);
	}
	// Handle X button
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
		break;
	}
}

void Game::updateMenu()
{
	// Play menu theme
	if (Mix_PlayingMusic() == 0)
	{
		soundManager.playMainMenuSong();
		std::cout << "Music Played!" << std::endl;
	}
}

void Game::renderMenu()
{
	SDL_RenderClear(renderer);

	// Render Menu Background
	renderBackground(MENU_BACKGROUND_PATH);
	
	// Render main menu screen
	if (!gameInTutorial)
	{
		// Render game title
		TextureManager::DrawText(gameTitleFont, "TANKOMBAT", TITLE_TEXT_COLOR, 0, 100, true);

		// Render the game title stars
		SDL_Texture* titleStarsTexture = TextureManager::loadTexture(TITLE_STARS_TEXTURE_PATH.c_str());
		SDL_Rect titleStarsSrcRect = { 0, 0, 430, 50 };
		SDL_Rect titleStarsDestRect;
		titleStarsDestRect.w = 800;
		titleStarsDestRect.h = 100;
		titleStarsDestRect.x = (SCREEN_WIDTH - titleStarsDestRect.w) / 2;
		titleStarsDestRect.y = 250;
		TextureManager::Draw(titleStarsTexture, titleStarsSrcRect, titleStarsDestRect);
		SDL_DestroyTexture(titleStarsTexture);

		// Render buttons
		playButton.show();
		tutorialButton.show();
		exitButton.show();
	}
	// Render tutorial screen
	else
	{
		renderTutorialScreen();
	}
	
	// Presenting all the textures
	SDL_RenderPresent(renderer);
}

void Game::renderBackground(std::string backgroundFilePath)
{
	SDL_Texture* background = TextureManager::loadTexture(backgroundFilePath.c_str());
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 1920;
	sourceRect.h = 1080;

	destinationRect.x = 0;
	destinationRect.y = 0;
	destinationRect.w = SCREEN_WIDTH;
	destinationRect.h = SCREEN_HEIGHT;

	TextureManager::Draw(background, sourceRect, destinationRect);
	SDL_DestroyTexture(background);
}

void Game::renderTutorialScreen()
{
	// Render text box
	SDL_Texture* tutorialTextbox = TextureManager::loadTexture(TUTORIAL_TEXTBOX_PATH.c_str());

	SDL_Rect tutorialSrcRect;
	tutorialSrcRect.x = 0;
	tutorialSrcRect.y = 0;
	tutorialSrcRect.w = TUTORIAL_TEXTBOX_WIDTH;
	tutorialSrcRect.h = TUTORIAL_TEXTBOX_HEIGHT;

	SDL_Rect tutorialDestRect;
	tutorialDestRect.w = TUTORIAL_TEXTBOX_WIDTH * 1.4; // Text box rendering sizes
	tutorialDestRect.h = TUTORIAL_TEXTBOX_HEIGHT * 1.4;
	tutorialDestRect.x = (SCREEN_WIDTH - tutorialDestRect.w) / 2;
	tutorialDestRect.y = (SCREEN_HEIGHT - tutorialDestRect.h) / 2 - 48;

	TextureManager::Draw(tutorialTextbox, tutorialSrcRect, tutorialDestRect);
	SDL_DestroyTexture(tutorialTextbox);

	// Render the tutorial title text

	// Setting each line's text
	std::string tutorialTitle = "TUTORIAL";
	std::string tutorialTextPlayerOne = "Player 1 (Blue): Press X to shoot and move forward";
	std::string tutorialTextPlayerTwo = "Player 2 (Red): Press RIGHT SHIFT to shoot and move forward";
	std::string tutorialTextPlayerThree = "Player 3 (Gray): Press LEFT TAB to shoot and move forward";
	std::string tutorialTextPlayerFour = "Player 4 (Green): Press BACKSPACE to shoot and move forward";

	// Rendering the lines of text
	TextureManager::DrawText(gameTitleFont, tutorialTitle, TUTORIAL_TEXT_COLOR, 0, 95, true);
	TextureManager::DrawText(globalFont, tutorialTextPlayerOne, TUTORIAL_TEXT_COLOR, 0, 350, true);
	TextureManager::DrawText(globalFont, tutorialTextPlayerTwo, TUTORIAL_TEXT_COLOR, 0, 450, true);
	TextureManager::DrawText(globalFont, tutorialTextPlayerThree, TUTORIAL_TEXT_COLOR, 0, 550, true);
	TextureManager::DrawText(globalFont, tutorialTextPlayerFour, TUTORIAL_TEXT_COLOR, 0, 650, true);

	// Render the tutorial menu buttons
	tutorialBackButton.show();
}

void Game::renderPauseMenu()
{
	// Render the pause menu textbox
	SDL_Texture* menuTextbox = TextureManager::loadTexture(MENU_TEXTBOX_PATH.c_str());

	SDL_Rect menuSrcRect;
	menuSrcRect.x = 0;
	menuSrcRect.y = 0;
	menuSrcRect.w = MENU_TEXTBOX_WIDTH;
	menuSrcRect.h = MENU_TEXTBOX_HEIGHT;

	SDL_Rect menuDestRect;
	menuDestRect.w = 1150; // Text box rendering sizes
	menuDestRect.h = 700;
	menuDestRect.x = (SCREEN_WIDTH - menuDestRect.w) / 2;
	menuDestRect.y = (SCREEN_HEIGHT - menuDestRect.h) / 2;
	TextureManager::Draw(menuTextbox, menuSrcRect, menuDestRect);
	SDL_DestroyTexture(menuTextbox);

	// Render the game paused title
	std::string gamePausedText = "GAME PAUSED";
	TextureManager::DrawText(gameTitleFont, gamePausedText, TITLE_TEXT_COLOR, 0, menuDestRect.y + 25, true);

	// Render the pause menu buttons
	resumeButton.show();
	restartButton.show();
	quitButton.show();
}

void Game::handlePauseMenuEvents(SDL_Event event)
{
	// Check which button is clicked
	resumeButton.handle_events(event);
	restartButton.handle_events(event);
	quitButton.handle_events(event);


	// Execute corresponding clicked actions
	if (resumeButton.isClicked())
	{
		resumeGameplay();
		resumeButton.resetClickedState();
	}
	else if (restartButton.isClicked())
	{
		restartGameplay();
		// Stop gameplay music
		Mix_HaltMusic();
		restartButton.resetClickedState();
	}
	else if (quitButton.isClicked())
	{
		quitToMainMenu();
		// Stop gameplay music
		Mix_HaltMusic();
		quitButton.resetClickedState();
	}
}

void Game::handleTutorialScreenEvents(SDL_Event event)
{
	tutorialBackButton.handle_events(event);
	if (tutorialBackButton.isClicked())
	{
		std::cout << "Tutorial back button pressed! " << std::endl;
		gameInTutorial = false;
		tutorialBackButton.resetClickedState();
	}
}

void Game::renderLoadingScreen()
{
	// Render the main menu background
	renderBackground(MENU_BACKGROUND_PATH);
	// Render the loading text
	std::string loadingText = "LOADING...";
	TextureManager::DrawText(gameTitleFont, loadingText, TITLE_TEXT_COLOR, 0, 300, true);
}

void Game::initGameplay()
{
	if (gameplayInitialized)
	{
		return;
	}
	if (!gameRestarted)
	{
		map = new Map(tiles);
	}
	activeTanks.push_back(new Tank(BLUE_TANK_TEXTURE_PATH, PLAYER_ONE_ID, 100, 300));
	activeTanks.push_back(new Tank(RED_TANK_TEXTURE_PATH, PLAYER_TWO_ID, 200, 400));
	activeTanks.push_back(new Tank(GREEN_TANK_TEXTURE_PATH, PLAYER_THREE_ID, 300, 500));
	activeTanks.push_back(new Tank(BEIGE_TANK_TEXTURE_PATH, PLAYER_FOUR_ID, 600, 500));

	// Play gameplay music
	soundManager.playGameplaySong();
	// Reset flags
	gameWon = false;
	gameplayInitialized = true;
	// Confirmation to console
	std::cout << "Gameplay Initialized!" << std::endl;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	// Handle quit button
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
		break;
	}

	if (gameWon)
	{
		handleWonMenuEvents(event);
	}

	if (gamePaused)
	{
		handlePauseMenuEvents(event);
	}
	else
	{
		// Handle gameplay buttons
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (!gameWon)
			{
				for (int playerCnt = 0; playerCnt < NUM_OF_PLAYERS; playerCnt++)
				{
					if (event.key.keysym.sym == PLAYER_KEYS[playerCnt] && !KEY_PRESSED[playerCnt])
					{
						executeKeyPressed(activeTanks[playerCnt]);
						KEY_PRESSED[playerCnt] = true;
					}
				}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					gamePaused = true;
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
	if (gameplayInitialized)
	{
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
		else if (gameWon)
		{
			renderWonMenu();
		}
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

void Game::cleanGameplayResources()
{
	// Clear all gameplay objects
	for (int tankCnt = activeTanks.size() - 1; tankCnt >= 0; tankCnt--) // Clear all tank objects
	{
		delete activeTanks[tankCnt];
		activeTanks.pop_back();
	}

	std::cout << "Remaining Tanks Left: " << activeTanks.size() << std::endl;

	for (int projectileCnt = activeProjectiles.size() - 1; projectileCnt >= 0; projectileCnt--) // Clear all projectile objects
	{
		delete activeProjectiles[projectileCnt];
		activeProjectiles.pop_back();
	}

	std::cout << "Remaining Projectiles Left: " << activeProjectiles.size() << std::endl;
}


void Game::resumeGameplay()
{
	gamePaused = false;
}

void Game::restartGameplay()
{
	cleanGameplayResources();
	gameplayInitialized = false;
	gamePaused = false;
	gameRestarted = true;
}

void Game::quitToMainMenu()
{
	// Reset flags
	gameInMenu = true; // Set game to in menu
	gameplayInitialized = false; // Reset gameplay initialization state
	gamePaused = false; // Reset game in pause menu state
	gameRestarted = false;

	cleanGameplayResources();

	// Clear the map
	map->~Map();
	for (int tileCnt = 0; tileCnt < TOTAL_TILES; tileCnt++)
	{
		delete tiles[tileCnt];
	}
}

void Game::renderWonMenu()
{
	// Render the won menu background
	SDL_Texture* wonMenuTextbox = TextureManager::loadTexture(WON_MENU_TEXTBOX_PATH.c_str());
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = WON_MENU_TEXTBOX_WIDTH;
	srcRect.h = WON_MENU_TEXTBOX_HEIGHT;

	SDL_Rect destRect;
	destRect.w = 600; // Text box rendering sizes
	destRect.h = 600;
	destRect.x = (SCREEN_WIDTH - destRect.w) / 2;
	destRect.y = (SCREEN_HEIGHT - destRect.h) / 2;
	TextureManager::Draw(wonMenuTextbox, srcRect, destRect);
	SDL_DestroyTexture(wonMenuTextbox);

	// Render winning announcement
	std::string winningTankID;
	for (int tankCnt = 0; tankCnt < activeTanks.size(); tankCnt++)
	{
		if (!activeTanks[tankCnt]->getDestroyedState())
		{
			winningTankID = activeTanks[tankCnt]->getID();
		}
	}

	std::string winAnnouncement = winningTankID + " WINS! ";

	SDL_Rect announcementDestRectangle;
	announcementDestRectangle.w = 600;
	announcementDestRectangle.h = 200;
	announcementDestRectangle.x = (SCREEN_WIDTH - announcementDestRectangle.w) / 2;
	announcementDestRectangle.y = 200;
	/*TextureManager::DrawText(globalFont, winAnnouncement, ANNOUNCEMENT_TEXT_COLOR, announcementDestRectangle);*/

	// Render the won menu buttons
	restartButton.show();
	quitButton.show();
}

void Game::handleWonMenuEvents(SDL_Event event)
{
	restartButton.handle_events(event);
	quitButton.handle_events(event);

	if (restartButton.isClicked())
	{
		restartGameplay();
		restartButton.resetClickedState();
	}
	else if (quitButton.isClicked())
	{
		quitToMainMenu();
		quitButton.resetClickedState();
	}
}

// Flag Getters
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