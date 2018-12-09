#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Ray.h"

glm::vec3 color(const Ray& r);

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

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

				glm::vec3 startPoint(-2.0f, -1.0f, -1.0f);
				glm::vec3 width(4.0f, 0.0f, 0.0f);
				glm::vec3 height(0.0f, 2.0f, 0.0f);
				glm::vec3 origin(0.0f, 0.0f, 0.0f);

				for (int y = SCREEN_HEIGHT - 1; y >= 0; y--)
				{
					for (int x = 0; x < SCREEN_WIDTH; x++)
					{
						//glm::vec3 col(float(x) / float(SCREEN_WIDTH), float(y) / float(SCREEN_HEIGHT), 0.2f);
						float h = float(x) / float(SCREEN_WIDTH);
						float v = float(y) / float(SCREEN_HEIGHT);
						Ray r(origin, startPoint + h * width + v * height);
						glm::vec3 col = color(r);

						int red = int(255.99 * col.r);
						int green = int(255.99 * col.g);
						int blue = int(255.99 * col.b);

						SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
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

bool sphere(const glm::vec3& center, float radius, const Ray& r)
{
	glm::vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

glm::vec3 color(const Ray& r)
{
	if (sphere(glm::vec3(0, 0, -1), 0.5f, r))
	{
		return glm::vec3(1, 0, 0);
	}

	glm::vec3 unitDirection = glm::normalize(r.direction());
	float t = 0.5f * (unitDirection.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}