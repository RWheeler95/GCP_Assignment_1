#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "Window.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Object.h"

class Renderer
{
private:

	SDL_Renderer* renderer = NULL;
	std::shared_ptr<Tracer> tracer;

public:

	void CreateRenderer(SDL_Window* window, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const Ray& r, std::vector<std::shared_ptr<Object>> objects);

	std::shared_ptr<Tracer> get_tracer();
	void set_tracer(std::shared_ptr<Tracer> _tracer);

	glm::vec3 color(const Ray& r);

};
#endif