#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Projectile.hpp"
#include "SoundManager.hpp"

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
	std::string getID();
	double getSpeed();
	SDL_Rect getHitBox();
	int getRotationAngle();
	void handleTileCollision();
private:
	MovingGameObject movingGameObject;
	SoundManager soundManager;
	int frame;
	bool isMoving;
	bool isRotatingClockWise;
	bool bulletShot;
	bool isDestroyed;
	SDL_Rect currentClip;
	static const int TANK_FRAME_COUNT = 4;
	SDL_Rect textureSheetClips[TANK_FRAME_COUNT];
	void handleWallCollision();
};