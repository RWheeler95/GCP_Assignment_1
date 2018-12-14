#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>

#include <iostream>

// Screen dimension constants
#define SCREEN_WIDTH 640;
#define SCREEN_HEIGHT 320;

class Window
{
private:

	// The window we'll be rendering to
	SDL_Window* window = NULL;

public:

	Window();
	~Window();

	SDL_Window* get_window();
	const int get_width();
	const int get_height();

};
#endif
