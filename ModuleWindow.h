#pragma once

#include "Module.h"
#include "SDL2-2.0.3/include/SDL.h"

class Application;

class ModuleWindow : public Module
{

public:

	// The window where we'll be rendering to...
	SDL_Window* window;
	// The surface contained by the window...
	SDL_Surface* screen_surface;

public:


	ModuleWindow(Application* app) : Module(app)
	{
		window = NULL;
		screen_surface = NULL;
	}

	~ModuleWindow() {}

	bool init()
	{
		LOG("Init SDL window & surface");
		bool ret = true;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			LOG("SDL_VIDEO could not initialize!SDL_Error: &s", SDL_GetError());
			ret = false;
		}
		else
		{
			// Create window
			int width = SCREEN_WIDTH;
			int height = SCREEN_HEIGHT;
			Uint32 flags = SDL_WINDOW_SHOWN;

			if (FULLSCREEN == true)
			{
				flags |= SDL_WINDOW_FULLSCREEN;
			}

			// TODO: SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE,  SDL_WINDOW_FULLSCREEN_DESKTOP

			window = SDL_CreateWindow("",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width, height, flags);

			if (window == NULL)
			{
				LOG("Window could not be created! SDL_ERROR: &s", SDL_GetError());
				ret = false;
			}
			else
			{
				// With successful creation, we obtaion window surface.
				screen_surface = SDL_GetWindowSurface(window);
			}
		}

		return ret;
	}

	bool cleanUp()
	{
		LOG("Destroying SDL window & surface. Quitting all SDL systems");

		// Destroy window
		if (window != NULL)
			SDL_DestroyWindow(window);

		// Quit SDL Subsystems
		SDL_Quit();
		return true;
	}
};