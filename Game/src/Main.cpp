#include "SDL.h"
#include "../../GameEngine/src/Engine.h"

int main(int argc, char* argv[])
{

	Engine::Engine gameEngine;

	gameEngine.Initialize("Cool Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	gameEngine.Run();
	
	
	SDL_Quit();

	return 0;
}









