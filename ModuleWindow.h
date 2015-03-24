#pragma once

#include "Module.h"
#include "Application.h"
#include "SDL2-2.0.3\include\SDL.h"

class ModuleWindow : public Module
{
public:

	// The window where we'll be rendering to...
	SDL_Window* window;
	// The surface contained by the window...
	SDL_Surface* screen_surface;

	ModuleWindow(Application*);
	virtual ~ModuleWindow();

	bool init();
	bool cleanUp();
};