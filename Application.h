#pragma once

#include <stdio.h>
#include "DList.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

class Application
{
private:

	DList<Module*> list_modules;
	void addModule(Module*);

public:

	ModuleWindow *window;
	ModuleRender *renderer;
	/*ModuleTextures* textures;
	ModuleInput* input;*/

	Application();
	~Application();

	bool init();
	update_status update();
	bool cleanUp(); 
};