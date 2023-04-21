#pragma once
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
static const int PLAYER_KEYS[4] = { SDLK_x, SDLK_RSHIFT, SDLK_1, SDLK_BACKSPACE };