#pragma once 

//#include "Globals.h"
//#include "Utilities.h"

class Application;

class Module
{
public:

	Application* app;

	Module(Application* parent) : app(parent) {}

	virtual bool init() { return true; }
	virtual update_status update() { return UPDATE_CONTINUE; }
	virtual bool cleanUp() { return true; }
};