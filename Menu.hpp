#pragma once
#include "Game.hpp"
class Button
{
public:
    Button(int x, int y, int w, int h);
    void handleEvents(SDL_Event event);
    void render();
private:
    std::string textureFilePath;
    SDL_Rect box;
    SDL_Rect* clip;
};

class GameMenu
{
public:
    GameMenu();
    ~GameMenu();
    Button playButton;
	void handleMenuEvents();
	void renderMenu();
private:
    void setClips();
};