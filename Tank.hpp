#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Projectile.hpp"

class Tank
{
public:
	Tank(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition);
	~Tank();
	void updateMovement();
	void shoot(std::vector<Projectile*>& activeProjectiles);
	void render();
	void setMovementState(bool moveState);
	void setRotationDirection(bool isClockWise);
	void setBulletShotState(bool isShot);
	void setSpeed(double speedValue);
	void setDestroyedState(bool destroyedState);
	double getSpeed();
	SDL_Rect getHitBox();
	int getRotationAngle();
private:
	MovingGameObject movingGameObject;
	int frame;
	bool isMoving;
	bool isRotatingClockWise;
	bool bulletShot;
	bool isDestroyed;
	SDL_Rect currentClip;
	static const int NORMAL_FRAME_COUNT = 4;
	static const int DESTROYED_FRAME_COUNT = 0;
	SDL_Rect normalTextureSheetClips[NORMAL_FRAME_COUNT];
	SDL_Rect destroyedTextureSheetClips[DESTROYED_FRAME_COUNT];
	void handleWallCollision();
};