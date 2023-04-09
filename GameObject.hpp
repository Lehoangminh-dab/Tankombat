#pragma once
#include "Game.hpp"

class GameObject
{
public:
	GameObject(const char* objectTextureSheet, std::string id, int xStartingPosition, int yStartingPosition, int width, int height);
	~GameObject();
	void render();
	std::string getID();
	SDL_Rect getHitBox();
private:
	std::string ID;
	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect hitBox;
};