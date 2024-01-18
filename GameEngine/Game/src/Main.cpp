#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->Init("Jogo Mega Fixe!!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	//Game::Init("!", 500, 500, 800, 600, false);

	return 0;
	//while 


}




/*
	xint width = 800;
	int height = 600;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Game Engine do Jorge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);

	Engine::Initialize();

	return 0;
*/