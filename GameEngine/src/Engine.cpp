#include "Engine.h"
#include <iostream>

namespace Engine {

	void Engine::Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
	{
		InitializeSDL(title, xpos, ypos, width, height, fullscreen);
		std::cout << "Engine Initialized!!!" << std::endl;
	}

	void Engine::Run() {

		while (isRunning) //Render Loop
		{
			//Event Handling
			HandleEvents();

			//Update Game Logic
			Update();

			//Render Objects
			Render();
			
		}

		ClearMemory();
	}

	void Engine::StopRunning()
	{
		std::cout << "Engine is shutting down" << std::endl;
	}

	void Engine::HandleEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				isRunning = false;
				break;
			default:
				break;
			}
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				if (event.key.repeat == 0){ 
					movingLeft = false;
					movingTimer = 0;
				}

			case SDLK_d:
				if (event.key.repeat == 0) { 
					movingRight = false;
					movingTimer = 0;
				}
				break;
			default:
				break;
			}
		

		default:
			break;
		}

		const Uint8* keyState;
		keyState = SDL_GetKeyboardState(NULL);

		//continuous-response keys
		if (keyState[SDL_SCANCODE_A]){
			movingLeft = true;
			movingTimer += deltaTime;
			tempPosX -= moveSpeed * deltaTime;
		}
		if (keyState[SDL_SCANCODE_D]){
			movingRight = true;
			movingTimer += deltaTime;
			tempPosX += moveSpeed * deltaTime;
		}
		if (keyState[SDL_SCANCODE_W]){
			tempPosY -= moveSpeed * deltaTime;
		}
		if (keyState[SDL_SCANCODE_S]){
			tempPosY += moveSpeed * deltaTime;
		}
		
	}

	void Engine::Update(){	
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		frameTime += deltaTime;

		playerPosition.x = tempPosX;
		playerPosition.y = tempPosY;

		std::cout << movingTimer << std::endl;

		if (!movingRight && !movingLeft) { playerRect.x = 3 * frameWidth; }
		if (movingLeft){
			if (movingTimer <= 0.5) {
				playerRect.x = 2 * frameWidth;
				std::cout << "pos1" << std::endl;
			}
			else if (movingTimer > 0.5f && movingTimer <= 1) {
				playerRect.x = frameWidth;
				std::cout << "pos2" << std::endl;
			}
			else if (movingTimer > 1) {
				playerRect.x = 0;
				std::cout << "pos3" << std::endl;
			}
		}
		else if(movingRight){
			if(movingTimer <= 0.5) {
				playerRect.x = 4 * frameWidth;
			}
			else if(movingTimer > 0.5f && movingTimer <= 1) {
				playerRect.x = 5 * frameWidth;
			}
			else if(movingTimer > 1){
				playerRect.x = 6 * frameWidth;
			}


		}
	}

	void Engine::Render()
	{
		SDL_RenderClear(renderer);

		//This is where we would add stuff to render
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, ship, &playerRect, &playerPosition);
		
		SDL_RenderPresent(renderer);

	}

	SDL_Texture* Engine::LoadTexture(const char* filePath, SDL_Renderer* renderTarget)
	{
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = SDL_LoadBMP(filePath);

		if (surface == NULL)
			std::cout << "Error Surface: " << filePath << std::endl;
		else
		{
			SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
			texture = SDL_CreateTextureFromSurface(renderTarget, surface);
			if (texture == NULL)
				std::cout << "Error Texture" << std::endl;
		}

		SDL_FreeSurface(surface);

		return texture;
	}

	void Engine::InitializeSDL(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
	{
		int flags = 0;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		if (SDL_Init(SDL_INIT_VIDEO) == 0)
		{
			//Create Window -------------------------------------------------------
			std::cout << "Subsystems initialized!" << std::endl;
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

			if (window)
			{
				std::cout << "Window created!" << std::endl;
			}

			//Create Renderer -----------------------------------------------------
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created!" << std::endl;
			}

			//Load Textures
			background = LoadTexture("assets/bmp/galaxy2.bmp", renderer);
			ship = LoadTexture("assets/bmp/Ship1.bmp", renderer);

			SDL_QueryTexture(ship, NULL, NULL, &textureWidth, &textureHeight);

			tempPosX = width/2 - 32;
			tempPosY = height - 100;

			playerPosition.w = playerPosition.h = 64;

			frameWidth = textureWidth / 7;
			frameHeight = textureHeight / 1;

			playerRect.x = 3 * frameWidth;
			playerRect.y = 0;
			playerRect.w = frameWidth;
			playerRect.h = frameHeight;

			isRunning = true;
		}
		else
		{
			isRunning = false;
		}
	}

	void Engine::ClearMemory()
	{
		SDL_DestroyWindow(window);
		SDL_DestroyTexture(ship);
		SDL_DestroyRenderer(renderer);

		window = nullptr;
		ship = nullptr;
		renderer = nullptr;

		SDL_Quit();
		std::cout << "Memory Cleared" << std::endl;
	}

}

