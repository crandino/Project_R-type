#pragma once 
#include "Globals.h"

class Module
{
public:

	virtual bool init() { return true; }
	virtual update_status update() { return UPDATE_CONTINUE; }
	virtual bool cleanUp() { return true; }
};