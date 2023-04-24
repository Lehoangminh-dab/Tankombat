#include "Game.hpp"

int main(int argc, char* args[])
{
	const int FPS = 60;
	const int FRAME_DELAY_MILISECONDS = 1000 / FPS;

	Game* game = new Game();
	game->init("Dead Engine", false);

	Uint32 frameStartTime;
	Uint32 frameEndTime;
	Uint32 ElapsedTimeOfFrame;
	while (game->isRunning())
	{         
		if (game->isInMenu())
		{
			game->handleMenuEvents();
			game->renderMenu();
		}
		else
		{
			game->initGamePlay();
			frameStartTime = SDL_GetTicks();

			game->handleEvents();
			game->update();
			game->render();
		
			frameEndTime = SDL_GetTicks();
			ElapsedTimeOfFrame = frameEndTime - frameStartTime;
			if (ElapsedTimeOfFrame < FRAME_DELAY_MILISECONDS)
			{
				SDL_Delay(FRAME_DELAY_MILISECONDS - ElapsedTimeOfFrame);
			}
		}
	}

	game->clean();
	return 0;
}