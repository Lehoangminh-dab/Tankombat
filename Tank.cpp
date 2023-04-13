#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Projectile.hpp"

class Tank
{
public:

	void moveAndShoot(const std::vector<Projectile*>& activeProjectiles);
private:
	MovingGameObject movingGameObject;
};