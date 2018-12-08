#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Ray.h"

//glm::vec3 color(const Ray& r);

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Renderer* renderer = NULL;

	SDL_Texture* texture = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Create renderer
			renderer = SDL_CreateRenderer(window, -1, 0/*SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC*/);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderClear(renderer);

				for (int y = SCREEN_HEIGHT - 1; y >= 0; y--)
				{
					for (int x = 0; x < SCREEN_WIDTH; x++)
					{
						glm::vec3 col(float(x) / float(SCREEN_WIDTH), float(y) / float(SCREEN_HEIGHT), 0.2f);
						int iRed = int(255.99 * col.r);
						int iGreen = int(255.99 * col.g);
						int iBlue = int(255.99 * col.b);

						SDL_SetRenderDrawColor(renderer, iRed, iGreen, iBlue, 255);
						SDL_RenderDrawPoint(renderer, x, SCREEN_HEIGHT - y);
					}
				}

				SDL_RenderPresent(renderer);

				SDL_Delay(10000000);
			}
		}
	}

	// Destroy Renderer
	SDL_DestroyRenderer(renderer);
	// Destroy window
	SDL_DestroyWindow(window);
	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}

glm::vec3 color(const Ray& r)
{
	//glm::vec3 unit_direction = unit_vector(r.direction());
}