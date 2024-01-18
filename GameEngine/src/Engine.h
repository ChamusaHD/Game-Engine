#pragma once
#include <SDL.h>
#include <vector>

namespace Engine {

	enum class MoveDirection { Forward, Backward, Right, Left, Downward, Upward };

	class Engine
	{
	public:

		void Initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

		void Run();

		void StopRunning();

		void HandleEvents();

		void Update();

		void Render();

		SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* renderTarget);

		bool Running() { return isRunning; }

	private:

		void InitializeSDL(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

		void ClearMemory();

		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event eventSDL;

		SDL_Texture* ship;
		SDL_Texture* background;

		SDL_Rect playerRect;
		SDL_Rect playerPosition;

		int frameWidth, frameHeight;
		int textureWidth, textureHeight;

		float frameTime = 0.0f;
		int prevTime;
		int currentTime;
		float deltaTime;

		bool movingLeft;
		bool movingRight;
		float moveSpeed = 100;
		float movingTimer;

		float tempPosX;
		float tempPosY;

		float dirY;
		float dirX;
	};
}


