#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
#include <limits>

#include "Object.h"
#include "Camera.h"
#include "Ray.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Tracer.h"

glm::vec3 color(const Ray& r, std::vector<std::shared_ptr<Object>> objects);
bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter, std::vector<std::shared_ptr<Object>> objects);

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

	std::vector<std::shared_ptr<Object>> objects;

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

				objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
				objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

				for (int y = SCREEN_HEIGHT - 1; y >= 0; y--)
				{
					for (int x = 0; x < SCREEN_WIDTH; x++)
					{
						float h = float(x) / float(SCREEN_WIDTH);
						float v = float(y) / float(SCREEN_HEIGHT);
						Ray r(origin, startPoint + h * width + v * height);
						
						glm::vec3 p = r.p(2.0f);
						glm::vec3 col = color(r, objects);

						int red = int(255.99 * col.r);
						int green = int(255.99 * col.g);
						int blue = int(255.99 * col.b);

						SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
						SDL_RenderDrawPoint(renderer, x, SCREEN_HEIGHT - y);
					}
				}

				SDL_RenderPresent(renderer);
			}
		}
	}


	SDL_Delay(10000000);
	// Destroy Renderer
	SDL_DestroyRenderer(renderer);
	// Destroy window
	SDL_DestroyWindow(window);
	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}

float sphereIntersections(const glm::vec3& center, float radius, const Ray& r)
{
	glm::vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.0f;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}

glm::vec3 color(const Ray& r, std::vector<std::shared_ptr<Object>> objects)
{
	ObjectIntersections inter;
	if (Intersections(r, 0.0f, std::numeric_limits<float>::max(), inter, objects))
	{
		return 0.5f * glm::vec3(inter.normal.x + 1, inter.normal.y + 1, inter.normal.z + 1);
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(r.direction());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}
	
	//float t = sphereIntersections(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);
	//if (t > 0.0f)
	//{
	//	glm::vec3 N = glm::normalize(r.p(t) - glm::vec3(0.0f, 0.0f, -1.0f));
	//	return 0.5f * glm::vec3(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f);
	//}

	//glm::vec3 unitDirection = glm::normalize(r.direction());
	//t = 0.5f * (unitDirection.y + 1.0f);
	//return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter, std::vector<std::shared_ptr<Object>> objects)
{
	ObjectIntersections rootInter;
	bool AnyIntersections = false;
	float Nearest = t_max;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i)->Intersections(r, t_min, Nearest, rootInter))
		{
			AnyIntersections = true;
			Nearest = rootInter.t;
			inter = rootInter;
		}
	}

	return AnyIntersections;
}