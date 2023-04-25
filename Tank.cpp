#include "Tank.hpp"
#include "cmath"
#include "Constants.hpp"

Tank::Tank(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition)
	: movingGameObject(objectTextureSheet, id, xStartingPosition, yStartingPosition, TANK_WIDTH, TANK_HEIGHT, 0, 30)
{

	for (int frame_cnt = 0; frame_cnt < TANK_FRAME_COUNT; frame_cnt++)
	{
		textureSheetClips[frame_cnt].x = frame_cnt * 32;
		textureSheetClips[frame_cnt].y = 0;
		textureSheetClips[frame_cnt].w = 32;
		textureSheetClips[frame_cnt].h = 32;
	}

	frame = 0;
	currentClip = textureSheetClips[0];

	isRotatingClockWise = true;
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
		movingGameObject.setSpeed(0);
		movingGameObject.setRotationAngle(movingGameObject.getRotationAngle());
	}
	else if (!isMoving)
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
	movingGameObject.move();
	handleWallCollision();
}

void Tank::shoot(std::vector<Projectile*>& activeProjectiles)
{
	if (isDestroyed)
	{
		return;
	}
	isRotatingClockWise = !isRotatingClockWise;
	SDL_Rect tankHitBox = getHitBox();
	double tankSpeed = movingGameObject.getSpeed();
	std::string tankID = movingGameObject.getID();
	int currentRotation = getRotationAngle();
	double currentRotationInRadians = currentRotation * M_PI / 180;
	int projectilePosX = tankHitBox.x + (TANK_WIDTH - PROJECTILE_WIDTH) / 2;
	int projectilePosY = tankHitBox.y + (TANK_HEIGHT - PROJECTILE_HEIGHT) / 2;
	std::string projectilePath;
	if (tankID == PLAYER_ONE_ID)
	{
		projectilePath = PROJECTILE_PATH_ONE;
	}
	else if (tankID == PLAYER_TWO_ID)
	{
		projectilePath = PROJECTILE_PATH_TWO;
	}
	else if (tankID == PLAYER_THREE_ID)
	{
		projectilePath = PROJECTILE_PATH_THREE;
	}
	else if (tankID == PLAYER_FOUR_ID)
	{
		projectilePath = PROJECTILE_PATH_FOUR;
	}
	else 
	{
		std::cout << "Tank ID invalid. Projectile cannot be spawned." << std::endl;
	}
	soundManager.playTankShootingSound();
	activeProjectiles.push_back(new Projectile(projectilePath.c_str(), tankID, projectilePosX, projectilePosY, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, PROJECTILE_SPEED, currentRotation));
}

void Tank::render()
{
	if (isDestroyed)
	{
		currentClip = textureSheetClips[3];
	}

	else if (bulletShot)
	{
		const int SHOOTING_TANK_FRAME_COUNT = TANK_FRAME_COUNT - 1;
		if ((frame / ANIMATION_DELAY_IN_FRAMES) < SHOOTING_TANK_FRAME_COUNT)
		{
			currentClip = textureSheetClips[frame / ANIMATION_DELAY_IN_FRAMES];
			frame++;
		}
		else
		{
			currentClip = textureSheetClips[0];
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
	isDestroyed = destroyedState;
}

bool Tank::getDestroyedState()
{
	return isDestroyed;
}

std::string Tank::getID()
{
	return movingGameObject.getID();
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

void Tank::handleTileCollision()
{
	SDL_Rect newHitBox = movingGameObject.getHitBox();
	double currentVelocityX = movingGameObject.getVelocityX();
	double currentVelocityY = movingGameObject.getVelocityY();
	int roundedVelocityX = std::ceil(currentVelocityX);
	int roundedVelocityY = std::ceil(currentVelocityY);
	newHitBox.x -= roundedVelocityX;
	newHitBox.y -= roundedVelocityY;
	movingGameObject.setHitBox(newHitBox.x, newHitBox.y, newHitBox.w, newHitBox.h);
}

void Tank::handleWallCollision()
{
	if (movingGameObject.collidedWithHorizontalWall())
	{
		std::cout << "TANK HAS COLLIDED WITH HORIZONTAL WALL" << std::endl;
		SDL_Rect newHitBox = movingGameObject.getHitBox();
		double currentVelocityY = movingGameObject.getVelocityY();
		int roundedVelocityY = std::ceil(currentVelocityY);
		std::cout << "Beginning HitBox y" << newHitBox.y << std::endl;
		newHitBox.y -= roundedVelocityY;
		std::cout << "Post HitBox y" << newHitBox.y << std::endl;
		std::cout << "Current Y Tank Velocity: " << currentVelocityY << std::endl;
		std::cout << "Current Y Tank Velocity (Int): " << roundedVelocityY << std::endl;
		movingGameObject.setHitBox(newHitBox.x, newHitBox.y, newHitBox.w, newHitBox.h);
	}
	if (movingGameObject.collidedWithVerticalWall())
	{
		std::cout << "TANK HAS COLLIDED WITH VERTICAL WALL" << std::endl;
		SDL_Rect newHitBox = movingGameObject.getHitBox();
		double currentVelocityX = movingGameObject.getVelocityX();
		int roundedVelocityX = std::ceil(currentVelocityX);
		std::cout << "Beginning HitBox x" << newHitBox.x << std::endl;
		newHitBox.x -= roundedVelocityX;
		std::cout << "Post HitBox x" << newHitBox.x << std::endl;
		std::cout << "Current X Tank Velocity: " << currentVelocityX << std::endl;
		std::cout << "Current X Tank Velocity (Int): " << roundedVelocityX << std::endl;
		movingGameObject.setHitBox(newHitBox.x, newHitBox.y, newHitBox.w, newHitBox.h);
	}
}

