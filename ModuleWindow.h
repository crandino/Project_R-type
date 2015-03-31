#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"
#include "SDL2-2.0.3\include\SDL.h"

class Application;

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

#endif __MODULEWINDOW_H__