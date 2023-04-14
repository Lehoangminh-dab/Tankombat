#pragma once
#include "GameObject.hpp"


class Projectile
{
public:
	Projectile(const char* textureSheetPath, int xPos, int yPos, int width, int height, double speed, int rotationAngle);
	~Projectile();
	void render();
	void update();
	void setCollisionStatus(bool collisionStatus);
	SDL_Rect getHitBox();
	bool getCollisionStatus();
	bool getDetonationStatus();
	static const double PROJECTILE_SPEED = 10.0;
	static const int PROJECTILE_WIDTH = 32;
	static const int PROJECTILE_HEIGHT = 32;
private:
	MovingGameObject movingGameObject;
	bool collided;
	bool detonationComplete;
	static const int TEXTURE_SHEET_FRAME_COUNT = 3;
	SDL_Rect textureSheetClips[TEXTURE_SHEET_FRAME_COUNT];
	int frame;
	SDL_Rect currentClip;
};