#include "Game.hpp"

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;


int main(int argc, char* args[])
{
	Game* game = new Game();
	game->init("DieEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);

	Uint32 frameStartTime;
	Uint32 frameEndTime;
	Uint32 frameElapsedTime;
	while (game->isRunning())
	{         
		frameStartTime = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();
		
		frameEndTime = SDL_GetTicks();
		frameElapsedTime = frameEndTime - frameStartTime;
		if (frameElapsedTime < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - frameElapsedTime);
		}
	}
	game->clean();
	return 0;
}