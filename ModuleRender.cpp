#include <Windows.h>
#include <stdio.h>
#include "Utilities.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL2-2.0.3\include\SDL.h"

ModuleRender::ModuleRender(Application *app) : Module(app)
{
	renderer = NULL;
}

ModuleRender::~ModuleRender()
{
}

bool ModuleRender::init()
{
	LOG("Init SDL Render");
	bool ret = true;
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	renderer = SDL_CreateRenderer(app->window->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Render could not initialize!SDL_Error: &s", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::update()
{
	SDL_RenderClear(renderer);

	// TODO: crear un PreUpdate Update PostUpdate
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

bool ModuleRender::cleanUp()
{
	LOG("Destroying SDL Render");

	// Destroy render
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	return true;
}