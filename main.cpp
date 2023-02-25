#include "Game.hpp"

int main(int argc, char* args[])
{
	Game* game = new Game();
	game->init("DieEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, true);
	while (game->isRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}