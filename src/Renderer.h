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
	std::vector<std::shared_ptr<Object>> objects;

public:

	Renderer(std::shared_ptr<Window> window, const int _width, const int _height, std::vector<std::shared_ptr<Object>> objects);
	~Renderer();

	std::shared_ptr<Tracer> get_tracer();
	void set_tracer(std::shared_ptr<Tracer> _tracer);

	glm::vec3 color(const Ray& r);

};
#endif