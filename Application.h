#pragma once
#include <stdio.h>
#include "DList.h"
#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"


class Application
{
public:

	DList<Module*> list_modules;

	Application()
	{
		ModuleWindow* pWindow = new ModuleWindow();
		addModule(pWindow);

		ModuleRender* pRender = new ModuleRender();
		addModule(pRender);


	}

	bool init()
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

	int update() { 
		
		update_status ret = UPDATE_CONTINUE;
		doubleNode<Module*> *item = list_modules.getFirst();

		while (item != NULL && ret == UPDATE_CONTINUE)
		{
			ret = item->data->update();
			item = item->next;
		}

		return ret;
	}
	bool cleanUp() { 

		bool ret = true;
		doubleNode<Module*> *item = list_modules.getLast();

		while (item != NULL && ret == true)
		{
			ret = item->data->cleanUp();
			item = item->previous;
		}

		return ret;
	}

private:

	void addModule(Module *_mod)
	{
		list_modules.add(_mod);
	}
};