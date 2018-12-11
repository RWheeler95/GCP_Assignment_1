#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>

#include <iostream>

class Window
{
private:

	// Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 320;

	// The window we'll be rendering to
	SDL_Window* window = NULL;

public:

	void CreateWindow();

};
#endif
