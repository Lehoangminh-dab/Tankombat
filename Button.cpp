#include "Button.hpp"
#include "TextureManager.hpp"

const int CLIP_MOUSEOUT = 0;
const int CLIP_MOUSEOVER = 1;
SDL_Rect clips[2];


Button::Button(int x, int y, int w, int h)
{
    // Test: Set clips 
    clips[CLIP_MOUSEOUT].x = 0;
    clips[CLIP_MOUSEOUT].y = 0;
    clips[CLIP_MOUSEOUT].w = 600;
    clips[CLIP_MOUSEOUT].h = 200;

    clips[CLIP_MOUSEOVER].x = 600;
    clips[CLIP_MOUSEOVER].y = 0;
    clips[CLIP_MOUSEOVER].w = 600;
    clips[CLIP_MOUSEOVER].h = 200;

    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the default sprite
    clip = &clips[CLIP_MOUSEOUT];
}

void Button::handle_events(SDL_Event event)
{
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if (event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            //Set the button sprite
            clip = &clips[CLIP_MOUSEOVER];
        }
        else
        {
            //Set the button sprite
            clip = &clips[CLIP_MOUSEOUT];
        }
    }

    //If a mouse button was pressed
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        //If the left mouse button was pressed
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
            {
                std::cout << "Button Clicked!" << std::endl;
            }
        }
    }
    ////If a mouse button was released
    //if (event.type == SDL_MOUSEBUTTONUP)
    //{
    //    //If the left mouse button was released
    //    if (event.button.button == SDL_BUTTON_LEFT)
    //    {
    //        //Get the mouse offsets
    //        x = event.button.x;
    //        y = event.button.y;

    //        //If the mouse is over the button
    //        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
    //        {
    //            //Set the button sprite
    //            clip = &clips[CLIP_MOUSEUP];
    //        }
    //    }
    //}
}

void Button::show()
{
    //Show the button
    SDL_Texture* buttonTexture = TextureManager::loadTexture("Assets/Menu/PlayButton.png");
    TextureManager::Draw(buttonTexture, *clip, box);
}


