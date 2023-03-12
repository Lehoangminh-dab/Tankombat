#include "Game.hpp"

int main(int argc, char* args[])
{
	const int FPS = 60;
	const int FRAME_DELAY_MILISECONDS = 1000 / FPS;
	const int WINDOW_HEIGHT = 675;
	const int WINDOW_WIDTH = 1375;

	Game* game = new Game();
	game->initialize("Dead Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	Uint32 frameStartTime;
	Uint32 frameEndTime;
	Uint32 ElapsedTimeOfFrame;
	while (game->isRunning())
	{         
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

	game->clean();
	return 0;
}