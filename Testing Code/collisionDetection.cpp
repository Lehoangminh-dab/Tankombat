	// Handle all collisions between tanks and tanks
	handleObjectsCollision(player, enemy);

	// Handle all collisions between tanks and projectiles
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		handleObjectsCollision(player, activeProjectiles[projectileCnt]);
		handleObjectsCollision(enemy, activeProjectiles[projectileCnt]);
	}

	// Handle all collisions between tanks and indestructible objects
	for (int indestructibleObstacleCnt = 0; indestructibleObstacleCnt < activeIndestructibleObstacles.size(); indestructibleObstacleCnt++)
	{
		handleObjectsCollision(player, activeIndestructibleObstacles[indestructibleObstacleCnt]);
		handleObjectsCollision(enemy, activeIndestructibleObstacles[indestructibleObstacleCnt]);
	}
	// Handle all collisions between projectiles and projectiles
	for (int firstProjectileCnt = 0; firstProjectileCnt < activeProjectiles.size() - 1; firstProjectileCnt++)
	{
		for (int secondProjectileCnt = firstProjectileCnt + 1; secondProjectileCnt < activeProjectiles.size(); secondProjectileCnt++)
		{
			handleObjectsCollision(activeProjectiles[firstProjectileCnt], activeProjectiles[secondProjectileCnt]);
		}
	}
	// Handle all collisions between projectiles and indestructible objects
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		for (int indestructibleObstacleCnt = 0; indestructibleObstacleCnt < activeIndestructibleObstacles.size(); indestructibleObstacleCnt++)
		{
			handleObjectsCollision(activeProjectiles[projectileCnt], activeIndestructibleObstacles[indestructibleObstacleCnt]);
		}
	}
	// Handle all collisions between projectiles and walls
	for (int projectileCnt = 0; projectileCnt < activeProjectiles.size(); projectileCnt++)
	{
		handleProjectileWallCollision(activeProjectiles[projectileCnt]);
	}