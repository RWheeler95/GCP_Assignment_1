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
#include "Window.h"

glm::vec3 color(const Ray& r, std::vector<std::shared_ptr<Object>> objects);
bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter, std::vector<std::shared_ptr<Object>> objects);

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

int main(int argc, char* args[])
{
	// The window we'll be rendering to
	std::shared_ptr<Window> window = NULL;

	std::shared_ptr<Renderer> renderer = NULL;


	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	SDL_Texture* texture = NULL;


	std::vector<std::shared_ptr<Object>> objects;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = std::make_shared<Window>();

		renderer = std::make_shared<Renderer>();

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

//float sphereIntersections(const glm::vec3& center, float radius, const Ray& r)
//{
//	glm::vec3 oc = r.origin() - center;
//	float a = dot(r.direction(), r.direction());
//	float b = 2.0f * dot(oc, r.direction());
//	float c = dot(oc, oc) - radius * radius;
//	float discriminant = b * b - 4 * a * c;
//	if (discriminant < 0)
//	{
//		return -1.0f;
//	}
//	else
//	{
//		return (-b - sqrt(discriminant)) / (2.0f * a);
//	}
//}


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
}

// Object
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