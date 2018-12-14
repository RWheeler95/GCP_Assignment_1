#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <thread>

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
	glm::vec3 pixels[640][320];

public:

	Renderer(std::shared_ptr<Window> window, const int _width, const int _height, std::vector<std::shared_ptr<Object>> objects);
	~Renderer();

	std::shared_ptr<Tracer> get_tracer();
	void set_tracer(std::shared_ptr<Tracer> _tracer);
	
	SDL_Renderer* get_renderer();

	glm::vec3 color(const Ray& r);

	glm::vec3 get_pixel(int i, int j);
	void set_pixel(glm::vec3 pixel, int i, int j);

};

void Threads(std::shared_ptr<Renderer> renderer, const int _width, const int _height);

void DrawSections(std::shared_ptr<Renderer> renderer, int minX, int minY, int maxX, int maxY, const int _width, const int _height);

#endif