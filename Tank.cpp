#include "Tank.hpp"
#include "cmath"

const int PROJECTILE_WIDTH = 32;
const int PROJECTILE_HEIGHT = 32;
const double PROJECTILE_SPEED = 10.0;
const int TANK_WIDTH = 64;
const int TANK_HEIGHT = 64;
const int TANK_SPEED = 10.0;
const int ROTATION_SPEED = 6;
const int ANIMATION_DELAY_IN_FRAMES = 5;

Tank::Tank(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition)
	: movingGameObject(objectTextureSheet, id, xStartingPosition, yStartingPosition, TANK_WIDTH, TANK_HEIGHT, 0, 30)
{

	for (int frame_cnt = 0; frame_cnt < NORMAL_FRAME_COUNT; frame_cnt++)
	{
		normalTextureSheetClips[frame_cnt].x = frame_cnt * 32;
		normalTextureSheetClips[frame_cnt].y = 0;
		normalTextureSheetClips[frame_cnt].w = 32;
		normalTextureSheetClips[frame_cnt].h = 32;
	}

	frame = 0;
	currentClip = normalTextureSheetClips[0];

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
	SDL_Rect currentTankHitBox = getHitBox();
	int currentRotation = getRotationAngle();
	int currentPosX = currentTankHitBox.x;
	int currentPosY = currentTankHitBox.y;
	activeProjectiles.push_back(new Projectile("Assets/Object/Projectile.png", currentPosX, currentPosY, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, PROJECTILE_SPEED, currentRotation));
}

void Tank::render()
{
	if (isDestroyed)
	{
		currentClip = normalTextureSheetClips[3];
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
	isDestroyed = destroyedState;
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

