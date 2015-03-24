#pragma once

#include "Module.h"
#include "Application.h"
#include "SDL2-2.0.3\include\SDL.h"

class ModuleRender : public Module
{
public:
	SDL_Renderer* renderer;

	ModuleRender(Application*);
	~ModuleRender();

	bool init();
	bool cleanUp();
};