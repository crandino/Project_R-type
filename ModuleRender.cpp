#pragma once

#include "ModuleRender.h"
#include "SDL2-2.0.3\include\SDL.h"

ModuleRender::ModuleRender(Application *app) : Module(app)
{
	renderer = NULL;
}

ModuleRender::~ModuleRender() {}

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

bool ModuleRender::cleanUp()
{
	LOG("Destroying SDL Render");

	// Destroy render
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	return true;
}