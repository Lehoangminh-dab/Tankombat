#pragma once
#include <SDL.h>
#include <string>
class Button
{
public:
    //Initialize the variables
    Button(int x, int y, int w, int h);

    //Handles events and set the button's sprite region
    void handle_events(SDL_Event event);

    //Shows the button on the screen
    void show();
    bool isClicked();
private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    bool buttonClicked;
};
