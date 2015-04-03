//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
//=================================
// the actual class

Application::Application()
{
	window = new ModuleWindow(this);
	addModule(window);

	renderer = new ModuleRender(this);
	addModule(renderer);

	textures = new ModuleTextures(this);
	addModule(textures);

	input = new ModuleInput(this);
	addModule(input);
}

Application::~Application()
{
	delete window;
	delete renderer;
	delete textures;
	delete input;
}

bool Application::init()
{
	bool ret = true;

	// We call init() for all modules
	doubleNode<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->init();
		item = item->next;
	}

	// After all initialization, we start each module
	LOG("Application Start -----------------");
	item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->start();
		item = item->next;
	}
	
	return ret;
}

// Update is split into 3: preUpdate, update and postUpdate.
update_status Application::update()
{
	update_status ret = UPDATE_CONTINUE;
	doubleNode<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->preUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->postUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::cleanUp()
{
	bool ret = true;
	doubleNode<Module*>* item = list_modules.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->cleanUp();
		item = item->previous;
	}

	return ret;
}

void Application::addModule(Module *module)
{
	list_modules.add(module);
}