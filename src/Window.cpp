#include "Window.h"

Window::Window()
{
	// Create window
	window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);  // Destroy window
}

SDL_Window * Window::get_window()
{
	return window;
}