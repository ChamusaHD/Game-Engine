//#include "Engine.h"
//#include "SDL.h"
#include "Game.h"


namespace Engine {

	__declspec(dllimport) void Initialize();
}

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "Subsystems initialized!" << std::endl;
			
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (window)
			{
				std::cout << "Window created!" << std::endl;
			}

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				std::cout << "Renderer created!" << std::endl;
			}

			isRunning = true;

			SDL_Delay(3000);
		}
		else 
		{
			isRunning = false;
		}
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{

}

void Game::Render()
{
	SDL_RenderClear(renderer);
	//This is where we would add stuff to render
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

