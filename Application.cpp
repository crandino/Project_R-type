#pragma once
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

Application::Application()
{
	window = new ModuleWindow(this);
	addModule(window);

	renderer = new ModuleRender(this);
	addModule(renderer);

	/*textures = new ModuleTextures(this);
	addModule(textures);

	input = new ModuleInput(this);
	addModule(input);*/
}

Application::~Application()
{
	delete window;
	delete renderer;
	/*delete textures;
	delete input;*/
}

bool Application::init()
{
	bool ret = true;
	doubleNode<Module*> *item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->init();
		item = item->next;
	}

	return ret;
}

update_status Application::update() {

	update_status ret = UPDATE_CONTINUE;
	doubleNode<Module*> *item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->update();
		item = item->next;
	}

	return ret;
}
bool Application::cleanUp() {

	bool ret = true;
	doubleNode<Module*> *item = list_modules.getLast();

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