#include "Renderer.h"

void Renderer::CreateRenderer(SDL_Window* window, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const Ray& r, std::vector<std::shared_ptr<Object>> objects)
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
				glm::vec3 col = color(r/*, objects*/);

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

std::shared_ptr<Tracer> Renderer::get_tracer()
{
	return tracer;
}

void Renderer::set_tracer(std::shared_ptr<Tracer> _tracer)
{
	tracer = _tracer;
}

glm::vec3 Renderer::color(const Ray & r)
{
	ObjectIntersections inter;
	if (tracer->Intersections(r, 0.0f, std::numeric_limits<float>::max(), inter))
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