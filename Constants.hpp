#pragma once
//Screen dimensions
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 928;

// Projectile and tank constants
static const std::string PROJECTILE_PATH_ONE = "Assets/Objects/Projectile/BlueProjectileSheet.png";
static const std::string PROJECTILE_PATH_TWO = "Assets/Objects/Projectile/RedProjectileSheet.png";
static const std::string PROJECTILE_PATH_THREE = "Assets/Objects/Projectile/GreenProjectileSheet.png";
static const std::string PROJECTILE_PATH_FOUR = "Assets/Objects/Projectile/BeigeProjectileSheet.png";

static const int PROJECTILE_WIDTH = 32;
static const int PROJECTILE_HEIGHT = 32;
static const double PROJECTILE_SPEED = 15.0;
static const int PROJECTILE_DISTANCE_FROM_TANK = 32;

static const int TANK_WIDTH = 48;
static const int TANK_HEIGHT = 48;
static const int TANK_SPEED = 10.0;
static const int ROTATION_SPEED = 6;
static const int ANIMATION_DELAY_IN_FRAMES = 5;

// Asset file Paths
static const char* BLUE_TANK_TEXTURE_PATH = "Assets/Objects/Tank/BlueTankSheet.png";
static const char* RED_TANK_TEXTURE_PATH = "Assets/Objects/Tank/RedTankSheet.png";
static const char* GREEN_TANK_TEXTURE_PATH = "Assets/Objects/Tank/GreenTankSheet.png";
static const char* BEIGE_TANK_TEXTURE_PATH = "Assets/Objects/Tank/BeigeTankSheet.png";

// Map background constants
static const char* DESERT_BACKGROUND_PATH = "Assets/Maps/sMap.png";

// Projectile constants
static const int NUM_OF_PLAYERS = 4;

// Control constants
static const int PLAYER_KEYS[4] = { SDLK_x, SDLK_RSHIFT, SDLK_TAB, SDLK_BACKSPACE };

// Menu background constants
static const SDL_Rect menuBackgroundSourceRect;

// Button constants
static const int LARGE_BUTTON_WIDTH = 300;
static const int LARGE_BUTTON_HEIGHT = 100;
static const int SMALL_BUTTON_WIDTH = 100;
static const int SMALL_BUTTON_HEIGHT = 100;

// Tile constants
static const int SOURCE_TILE_SIZE = 32;
static const int TILE_WIDTH = 16;
static const int TILE_HEIGHT = 16;
static const int TOTAL_TILES = (SCREEN_WIDTH / TILE_WIDTH) * (SCREEN_HEIGHT / TILE_HEIGHT);
static const int TOTAL_TILE_SPRITES = 4;

// The different tile types
static const int TILE_DIRT = 0;
static const int TILE_GRASS = 1;
static const int TILE_WATER = 2;
static const int TILE_OBSTACLE_WALL = 3;

// Tank IDs
static const std::string PLAYER_ONE_ID = "PLAYER ONE";
static const std::string PLAYER_TWO_ID = "PLAYER TWO";
static const std::string PLAYER_THREE_ID = "PLAYER THREE";
static const std::string PLAYER_FOUR_ID = "PLAYER FOUR";
