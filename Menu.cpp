#include "Menu.hpp"
#include "TextureManager.hpp"

// General button constants
const int CLIP_MOUSEOUT = 0;
const int CLIP_MOUSEOVER = 1;
// Play button
const std::string PLAY_BUTTON_FILE_PATH = "Assets/Menu/PlayButton.png";
SDL_Rect playButtonClips[2];


Button::Button(int x, int y, int w, int h)
{
	textureFilePath = PLAY_BUTTON_FILE_PATH;
	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	// Test: Initializing playButtonClips
	playButtonClips[CLIP_MOUSEOUT].x = 0;
	playButtonClips[CLIP_MOUSEOUT].y = 0;
	playButtonClips[CLIP_MOUSEOUT].w = 600;
	playButtonClips[CLIP_MOUSEOUT].h = 200;

	playButtonClips[CLIP_MOUSEOVER].x = 600;
	playButtonClips[CLIP_MOUSEOVER].y = 0;
	playButtonClips[CLIP_MOUSEOVER].w = 600;
	playButtonClips[CLIP_MOUSEOVER].h = 200;
	//Set the default sprite
	clip = &playButtonClips[CLIP_MOUSEOUT];
}

void Button::handleEvents(SDL_Event event)
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
			clip = &playButtonClips[CLIP_MOUSEOVER];
		}
		else
		{
			//Set the button sprite
			clip = &playButtonClips[CLIP_MOUSEOUT];
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
				std::cout << "Button Pressed" << std::endl;
			}
		}
	}
	//If a mouse button was released
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		//If the left mouse button was released
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;
		}
	}
}

void Button::render()
{
	const char* filePath = textureFilePath.c_str();
	SDL_Texture* buttonTexture = TextureManager::loadTexture(filePath);
	TextureManager::Draw(buttonTexture, *clip, box);
}

GameMenu::GameMenu()
	: playButton(400, 400, 400, 400)
{
}

void GameMenu::handleMenuEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	playButton.handleEvents(event);
}

void GameMenu::renderMenu()
{
	// Test: Only draw a button
	playButton.render();
}

void GameMenu::setClips()
{
}
