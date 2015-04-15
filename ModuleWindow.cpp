//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleWindow.h"
//=================================
// the actual code

ModuleWindow::ModuleWindow(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

ModuleWindow::~ModuleWindow()
{ }

bool ModuleWindow::init()
{
	LOG("Init SDL Window & surface");
	bool ret = true;

	// SDL_INIT_VIDEO is a flag to initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create Window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		
		if (WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Get window surface. If we want to resize the window, 
			// this function must be called again.
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;

}
	
// Called before quitting
bool ModuleWindow::cleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems	
	SDL_Quit();
	return true;
}
