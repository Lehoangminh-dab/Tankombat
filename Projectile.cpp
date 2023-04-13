#include "Projectile.hpp"

Projectile::Projectile(const char* textureSheetPath, int xPos, int yPos, double speed, int rotationAngle)
	: movingGameObject(textureSheetPath, "PROJECTILE", xPos, yPos, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, speed, rotationAngle)
{
	collided = false;
	detonationComplete = false;

	for (int frame_cnt = 0; frame_cnt < TEXTURE_SHEET_FRAME_COUNT; frame_cnt++)
	{
		textureSheetClips[frame_cnt].x = frame_cnt * PROJECTILE_WIDTH;
		textureSheetClips[frame_cnt].y = 0;
		textureSheetClips[frame_cnt].w = PROJECTILE_WIDTH;
		textureSheetClips[frame_cnt].h = PROJECTILE_HEIGHT;
	}

	frame = 0;
	currentClip = textureSheetClips[frame / 4];
}

Projectile::~Projectile()
{
	movingGameObject.~MovingGameObject();
}

void Projectile::render()
{
	if (collided && frame / 4 < TEXTURE_SHEET_FRAME_COUNT)
	{
		currentClip = textureSheetClips[frame / 4];
		movingGameObject.setSourceRectangle(currentClip);
		frame++;
	}
	else if (collided && frame / 4 >= TEXTURE_SHEET_FRAME_COUNT)
	{
		detonationComplete = true;
	}
	movingGameObject.render();
}

void Projectile::update()
{
	if (!collided)
	{
		movingGameObject.move();
	}
}

bool Projectile::setCollisionStatus(bool collisionStatus)
{
	collided = collisionStatus;
}

bool Projectile::getCollisionStatus()
{
	return collided;
}

bool Projectile::getDetonationStatus()
{
	return detonationComplete;
}

