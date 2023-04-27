#include <iostream>
#include <SDL.h>
#include "SoundManager.hpp"

const char* MAIN_MENU_SONG_PATH = "Assets/Sounds/Battlefield 1943 Theme.mp3";
const char* GAMEPLAY_SONG_PATH = "Assets/Sounds/Encounter remix.mp3";
const char* BUTTON_CLICKED_SOUND_PATH = "Assets/Sounds/Button Clicking.ogg";
const char* TANK_IDLE_SOUND_PATH = "Assets/Sounds/Engine Idle.ogg";
const char* TANK_MOVING_SOUND_PATH = "Assets/Sounds/Engine Moving.ogg";
const char* TANK_SHOOTING_SOUND_PATH = "Assets/Sounds/Tank Shooting.ogg";
const char* PROJECTILE_EXPLOSION_SOUND_PATH = "Assets/Sounds/Projectile Explosion Sound.flac";

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::loadSounds()
{
	mainMenuSong = Mix_LoadMUS(MAIN_MENU_SONG_PATH);
	if (mainMenuSong == NULL)
	{
		std::cout << "Failed to load main menu song! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	gameplaySong = Mix_LoadMUS(GAMEPLAY_SONG_PATH);
	if (gameplaySong == NULL)
	{
		std::cout << "Failed to load gameplay song! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	buttonClickedSound = Mix_LoadWAV(BUTTON_CLICKED_SOUND_PATH);
	if (buttonClickedSound == NULL)
	{
		std::cout << "Failed to load button clicked sound!" << std::endl;
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

void SoundManager::playMainMenuSong()
{
	Mix_PlayMusic(mainMenuSong, -1);
}

void SoundManager::playGameplaySong()
{
	Mix_PlayMusic(gameplaySong, -1);
}

void SoundManager::playButtonClickedSound()
{
	Mix_PlayChannel(-1, buttonClickedSound, 0);
}

void SoundManager::playTankShootingSound()
{
	Mix_PlayChannel(-1, tankShootingSound, 0);
}

void SoundManager::playProjectileExplosionSound()
{
	Mix_PlayChannel(-1, projectileExplosionSound, 0);
}

