#pragma once

#include "Module.h"
#include "ModuleWindow.h"
#include "Utilities.h"
#include "SDL2-2.0.3\include\SDL.h"

class ModuleRender : public Module
{

private:

	SDL_Renderer* renderer;

public:

	ModuleRender()
	{
		renderer = NULL;
	}

	~ModuleRender() {}

	bool init()
	{
		LOG("Init SDL Render");
		bool ret = true;
		Uint32 flags = SDL_RENDERER_ACCELERATED;

		renderer = SDL_CreateRenderer( window, -1, flags);

		if (renderer == NULL)
		{
			LOG("Render could not initialize!SDL_Error: &s", SDL_GetError());
			ret = false;
		}

		return ret;
	}

	bool cleanUp()
	{
		LOG("Destroying SDL Render");

		// Destroy render
		if (renderer != NULL)
			SDL_DestroyRenderer(renderer);

		return true;
	}

};