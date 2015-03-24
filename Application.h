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

	ModuleRender* renderer;
	ModuleWindow* window;
	/*ModuleTextures* textures;
	ModuleInput* input;*/

	Application();
	~Application();
	

	bool init();
	int update();
	bool cleanUp(); 
};