#pragma once 
#include "Globals.h"

class Module
{
public:

	virtual bool init() { return true; }
	virtual int update() { return UPDATE_STOP; }
	virtual bool cleanUp() { return true; }
};