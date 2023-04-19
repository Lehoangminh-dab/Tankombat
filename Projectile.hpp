#pragma once
#include "GameObject.hpp"
#include "SoundManager.hpp"

class Projectile
{
public:
	Projectile(const char* textureSheetPath, std::string id, int xPos, int yPos, int width, int height, double speed, int rotationAngle);
	~Projectile();
	void render();
	void update();
	void setCollisionStatus(bool collisionStatus);
	SDL_Rect getHitBox();
	std::string getID();
	bool getCollisionStatus();
	bool getDetonationStatus();
private:
	MovingGameObject movingGameObject;
	SoundManager soundManager;
	bool collided;
	bool detonationSoundPlayed;
	bool detonationComplete;
	const int PROJECTILE_WIDTH = 32;
	const int PROJECTILE_HEIGHT = 32;
	static const int TEXTURE_SHEET_FRAME_COUNT = 3;
	SDL_Rect textureSheetClips[TEXTURE_SHEET_FRAME_COUNT];
	int frame;
	SDL_Rect currentClip;
};