#include "Engine.h"
#include "SDL.h"
#include <iostream>

namespace Engine {

	void Initialize()
	{
		std::cout << "Engine Initialized!!!" << std::endl;
	}
	void StopRunning()
	{
		std::cout << "Engine is shutting down" << std::endl;
	}
}