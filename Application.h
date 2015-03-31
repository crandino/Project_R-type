#pragma once

#include "DList.h"
#include "Globals.h"
#include "Module.h"

class ModuleWindow;
class ModuleRender;

class Application
{
private:

	DList<Module*> list_modules;
	void addModule(Module*);

public:

	ModuleWindow* window;
	ModuleRender* renderer;

	/*ModuleTextures* textures;
	ModuleInput* input;*/

	Application();
	~Application();

	bool init();
	update_status update();
	bool cleanUp(); 
};