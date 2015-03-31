#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "DList.h"
#include "Globals.h"
#include "Module.h"

class ModuleWindow;
class ModuleRender;
class ModuleTextures;

class Application
{
private:

	DList<Module*> list_modules;
	void addModule(Module*);

public:

	ModuleWindow* window;
	ModuleRender* renderer;
	ModuleTextures* textures;
	/*ModuleInput* input;*/

	Application();
	~Application();

	bool init();
	update_status update();
	bool cleanUp(); 
};

#endif __APPLICATION_H__