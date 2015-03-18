#pragma once
#include <stdio.h>
#include "DList.h"
#include "Globals.h"
#include "Module.h"
#include "ModuleDummy.h"

class Application
{
public:

	DList<Module*> list_modules;

	Application()
	{
		ModuleDummy* pDummy = new ModuleDummy();
		addModule(pDummy);
	}

	bool init()
	{
		doubleNode<Module*> *item = list_modules.getFirst();

		while (item != NULL)
		{
			item->data->init();
			item = item->next;
		}

		return true;
	}

	int update() { return UPDATE_STOP; }
	bool cleanUp() { return true; }

private:

	void addModule(Module *_mod)
	{
		list_modules.add(_mod);
	}
};