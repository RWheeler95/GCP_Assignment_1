/*
https://medium.com/@phostershop/solving-multithreaded-raytracing-issues-with-c-11-7f018ecd76fa
https://docs.microsoft.com/en-gb/windows/desktop/ProcThread/creating-threads
http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
http://www.cplusplus.com/forum/windows/34660/
https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm
*/

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
//#include <limits>

#include "Object.h"
#include "Camera.h"
#include "Ray.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Tracer.h"
#include "Window.h"

int main(int argc, char* args[])
{
	std::shared_ptr<Window> window = NULL;  // The window I'll be rendering to
	std::shared_ptr<Renderer> renderer = NULL;
	

	std::vector<std::shared_ptr<Object>> objects;

	objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
	objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = std::make_shared<Window>();

		renderer = std::make_shared<Renderer>(window, 640, 320, objects);

		Threads(renderer, window->get_width(), window->get_height());

		for (int y = 0; y < 320; y++)
		{
			for (int x = 0; x < 640; x++)
			{
				glm::vec3 pixel = renderer->get_pixel(x, y);

				SDL_SetRenderDrawColor(renderer->get_renderer(), pixel.r, pixel.g, pixel.b, 255);
				SDL_RenderDrawPoint(renderer->get_renderer(), x, 320 - y);
			}
		}

		SDL_RenderPresent(renderer->get_renderer());
	}

	bool quit{ };
	SDL_Event event;

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:

			quit = true;
			break;
		}
	}

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}
