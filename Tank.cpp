#include "Tank.hpp"
const int TANK_WIDTH = 32;
const int TANK_HEIGHT = 32;
const int TANK_SPEED = 10.0;
const int ROTATION_SPEED = 6;
const int ANIMATION_DELAY_IN_FRAMES = 5;

Tank::Tank(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition)
	: movingGameObject(objectTextureSheet, id, xStartingPosition, yStartingPosition, TANK_WIDTH, TANK_HEIGHT, 0, (rand() % 60) * 6)
{
	
	for (int frame_cnt = 0; frame_cnt < NORMAL_FRAME_COUNT; frame_cnt++)
	{
		normalTextureSheetClips[frame_cnt].x = frame_cnt * 32;
		normalTextureSheetClips[frame_cnt].y = 0;
		normalTextureSheetClips[frame_cnt].w = 32;
		normalTextureSheetClips[frame_cnt].h = 32;
	}

	frame = 0;
	currentClip = normalTextureSheetClips[frame / ANIMATION_DELAY_IN_FRAMES];

	isRotatingClockWise = rand() % 1;
	isMoving = false;
	bulletShot = false;
	isDestroyed = false;
}

Tank::~Tank()
{
	movingGameObject.~MovingGameObject();
}

void Tank::updateMovement()
{
	if (isDestroyed)
	{
		return;
	}

	if (!isMoving)
	{
		movingGameObject.setSpeed(0);
		int currentRotationAngle = movingGameObject.getRotationAngle();
		if (isRotatingClockWise)
		{
			movingGameObject.setRotationAngle(currentRotationAngle + ROTATION_SPEED);
		}
		else
		{
			movingGameObject.setRotationAngle(currentRotationAngle - ROTATION_SPEED);
		}
	}
	else
	{
		movingGameObject.setSpeed(TANK_SPEED);
	}
}

void Tank::shoot(std::vector<Projectile*>& activeProjectiles)
{
	isRotatingClockWise = !isRotatingClockWise;
	SDL_Rect currentTankHitBox = getHitBox();
	int currentRotation = getRotationAngle();
	int currentPosX = currentTankHitBox.x;
	int currentPosY = currentTankHitBox.y;
	activeProjectiles.push_back(new Projectile("Assets/Object/Projectile.png", currentPosX, currentPosY, Projectile::PROJECTILE_WIDTH, Projectile::PROJECTILE_HEIGHT, Projectile::PROJECTILE_SPEED, currentRotation));
}

void Tank::render()
{
	if (isDestroyed)
	{
		if ((frame / ANIMATION_DELAY_IN_FRAMES < DESTROYED_FRAME_COUNT))
		{
			currentClip = destroyedTextureSheetClips[frame / ANIMATION_DELAY_IN_FRAMES];
			frame++;
		}
		else
		{
			currentClip = destroyedTextureSheetClips[0];
		}
	}
	else if (bulletShot)
	{
		if ((frame / ANIMATION_DELAY_IN_FRAMES) < NORMAL_FRAME_COUNT)
		{
			currentClip = normalTextureSheetClips[frame / ANIMATION_DELAY_IN_FRAMES];
			frame++;
		}
		else
		{
			currentClip = normalTextureSheetClips[0];
			frame = 0;
			bulletShot = false;
		}
	}

	movingGameObject.setSourceRectangle(currentClip);
	movingGameObject.render();
}

void Tank::setMovementState(bool moveState)
{
	isMoving = moveState;
}

void Tank::setRotationDirection(bool isClockWise)
{
	isRotatingClockWise = isClockWise;
}

void Tank::setBulletShotState(bool isShot)
{
	bulletShot = isShot;
}

void Tank::setSpeed(double speedValue)
{
	movingGameObject.setSpeed(speedValue);
}

void Tank::setDestroyedState(bool destroyedState)
{
	isDestroyed = true;
}

double Tank::getSpeed()
{
	return movingGameObject.getSpeed();
}

SDL_Rect Tank::getHitBox()
{
	return movingGameObject.getHitBox();
}

int Tank::getRotationAngle()
{
	return movingGameObject.getRotationAngle();
}


