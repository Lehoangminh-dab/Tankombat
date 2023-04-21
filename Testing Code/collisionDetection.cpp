
	int tankTopLeftX = tankHitBox.x;
	int tankTopLeftY = tankHitBox.y;

	int tankBottomLeftX = tankHitBox.x;
	int tankBottomLeftY = tankHitBox.y + tankHitBox.h;

	int tankTopRightX = tankHitBox.x + tankHitBox.w;
	int tankTopRightY = tankHitBox.y;

	int tankBottomRightX = tankHitBox.x + tankHitBox.w;
	int tankBottomRightY = tankHitBox.y + tankHitBox.h;

	double tankCenterX = (tankTopLeftX + tankBottomLeftX + tankTopRightX + tankBottomLeftX) / 4;
	double tankCenterY = (tankTopLeftY + tankBottomLeftY + tankTopRightY + tankBottomLeftY) / 4;	

	double rotatedTankTopLeftX = tankCenterX + (tankTopLeftX - tankCenterX) * cos(currentRotationInRadians) - (tankTopLeftY - tankCenterY) * sin(currentRotationInRadians);
	double rotatedTankTopLeftY = tankCenterY + (tankTopLeftX - tankCenterX) * sin(currentRotationInRadians) + (tankTopLeftY - tankCenterY) * cos(currentRotationInRadians);

	double rotatedTankBottomLeftX = tankCenterX + (tankBottomLeftX - tankCenterX) * cos(currentRotationInRadians) - (tankBottomLeftY - tankCenterY) * sin(currentRotationInRadians);
	double rotatedTankBottomLeftY = tankCenterY + (tankBottomLeftX - tankCenterX) * sin(currentRotationInRadians) + (tankBottomLeftY - tankCenterY) * cos(currentRotationInRadians);

	double rotatedTankTopRightX = tankCenterX + (tankTopRightX - tankCenterX) * cos(currentRotationInRadians) - (tankTopRightY - tankCenterY) * sin(currentRotationInRadians);
	double rotatedTankTopRightY = tankCenterY + (tankTopRightX - tankCenterX) * sin(currentRotationInRadians) + (tankTopRightY - tankCenterY) * cos(currentRotationInRadians);

	double rotatedTankBottomRightX = tankCenterX + (tankBottomRightX - tankCenterX) * cos(currentRotationInRadians) - (tankBottomRightY - tankCenterY) * sin(currentRotationInRadians);
	double rotatedTankBottomRightY = tankCenterY + (tankBottomRightX - tankCenterX) * sin(currentRotationInRadians) + (tankBottomRightY - tankCenterY) * cos(currentRotationInRadians);

	double rotatedProjectilePosX = rotatedTankTopRightX + PROJECTILE_DISTANCE_FROM_TANK;
	double rotatedProjectilePosY = rotatedTankTopRightY + (TANK_HEIGHT - PROJECTILE_HEIGHT) / 2;

	double projectileCenterX = tankCenterX + (TANK_WIDTH / 2 + PROJECTILE_WIDTH / 2 + PROJECTILE_DISTANCE_FROM_TANK) * cos(currentRotationInRadians);
	double projectileCenterY = tankCenterY + (TANK_HEIGHT / 2 + PROJECTILE_HEIGHT / 2 + PROJECTILE_DISTANCE_FROM_TANK) * sin(currentRotationInRadians);

	int finalProjectileX = projectileCenterX + (rotatedProjectilePosX - projectileCenterX) * cos(-1 * currentRotationInRadians) - (rotatedProjectilePosY - projectileCenterY) * sin(-1 * currentRotationInRadians);
	int finalProjectileY = projectileCenterY + (rotatedProjectilePosX - projectileCenterX) * sin(-1 * currentRotationInRadians) + (rotatedProjectilePosY - projectileCenterY) * cos(-1 * currentRotationInRadians);
	//int projectilePosX = tankHitBox.x + tankHitBox.w + PROJECTILE_DISTANCE_FROM_TANK;
	//int projectilePosY = (tankHitBox.y + tankHitBox.h - PROJECTILE_HEIGHT) / 2;

	//int rotatedProjectilePosX = projectilePosX * cos(currentRotationInRadians) - projectilePosY * sin(currentRotationInRadians);
	//int rotatedProjectilePosY = projectilePosX * sin(currentRotationInRadians) + projectilePosY * cos(currentRotationInRadians);

	//int finalProjectilePosX = tankHitBox.x + rotatedProjectilePosX;
	//int finalProjectilePosY = tankHitBox.y + rotatedProjectilePosY;