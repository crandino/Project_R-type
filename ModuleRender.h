#pragma once

#include "Module.h"
#include "Globals.h"

class ModuleRender : public Module
{
public:
	SDL_Renderer* renderer;

	ModuleRender(Application*);
	~ModuleRender();

	bool init();
	update_status update();
	bool cleanUp();
};