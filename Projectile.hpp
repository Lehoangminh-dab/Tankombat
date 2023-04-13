#pragma once
#include "GameObject.hpp"


class Projectile
{
public:
	Projectile(const char* textureSheetPath, int xPos, int yPos, double speed, int rotationAngle);
	~Projectile();
	void render();
	void update();
	bool setCollisionStatus(bool collisionStatus);
	bool getCollisionStatus();
	bool getDetonationStatus();
private:
	MovingGameObject movingGameObject;
	bool collided;
	bool detonationComplete;
	const int PROJECTILE_WIDTH = 32;
	const int PROJECTILE_HEIGHT = 32;
	static const int TEXTURE_SHEET_FRAME_COUNT = 3;
	SDL_Rect textureSheetClips[TEXTURE_SHEET_FRAME_COUNT];
	int frame;
	SDL_Rect currentClip;
};