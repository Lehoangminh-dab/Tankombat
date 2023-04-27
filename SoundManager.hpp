#pragma once
#include "SDL_mixer.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void loadSounds();
	void playMainMenuSong();
	void playGameplaySong();
	void playButtonClickedSound();
	void playTankShootingSound();
	void playProjectileExplosionSound();
private:
	Mix_Music* mainMenuSong = NULL;
	Mix_Music* gameplaySong = NULL;
	Mix_Chunk* buttonClickedSound = NULL;
	Mix_Chunk* tankShootingSound = NULL;
	Mix_Chunk* projectileExplosionSound = NULL;
};