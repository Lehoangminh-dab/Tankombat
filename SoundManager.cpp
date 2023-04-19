#include "SoundManager.hpp"
#include <iostream>

const char* TANK_IDLE_SOUND_PATH = "Assets/Sounds/Engine Idle.ogg";
const char* TANK_MOVING_SOUND_PATH = "Assets/Sounds/Engine Moving.ogg";
const char* TANK_SHOOTING_SOUND_PATH = "Assets/Sounds/Tank Shooting.ogg";
const char* PROJECTILE_EXPLOSION_SOUND_PATH = "Assets/Sounds/Projectile Explosion Sound.flac";

SoundManager::SoundManager()
{
	tankIdleSound = Mix_LoadWAV(TANK_IDLE_SOUND_PATH);
	if (tankIdleSound == NULL)
	{
		std::cout << "Failed to load tank idle sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	tankMovingSound = Mix_LoadWAV(TANK_MOVING_SOUND_PATH);
	if (tankMovingSound == NULL)
	{
		std::cout << "Failed to load tank moving sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	tankShootingSound = Mix_LoadWAV(TANK_SHOOTING_SOUND_PATH);
	if (tankShootingSound == NULL)
	{
		std::cout << "Failed to load tank shooting sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	projectileExplosionSound = Mix_LoadWAV(PROJECTILE_EXPLOSION_SOUND_PATH);
	if (projectileExplosionSound == NULL)
	{
		std::cout << "Failed to load projectile explosion sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
}

SoundManager::~SoundManager()
{
}

void SoundManager::playTankIdleSound()
{
	Mix_PlayChannel(-1, tankIdleSound, 0);
}

void SoundManager::playTankMovingSound()
{
	Mix_PlayChannel(-1, tankMovingSound, 0);
}

void SoundManager::playTankShootingSound()
{
	Mix_PlayChannel(-1, tankShootingSound, 0);
}

void SoundManager::playProjectileExplosionSound()
{
	Mix_PlayChannel(-1, projectileExplosionSound, 0);
}

