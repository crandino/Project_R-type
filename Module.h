//=================================
// include guard
#ifndef __MODULE_H__
#define __MODULE_H__
//=================================
// forward declared dependencies
class Application; 
//=================================
// included dependencies
#include "Globals.h"
//=================================
// the actual class

class Module
{
public:

	Application *app;

	Module(Application *parent) : app(parent)
	{	}

	virtual bool init() { return true; }
	virtual bool start() { return true; }
	virtual update_status preUpdate() { return UPDATE_CONTINUE; }
	virtual update_status update() { return UPDATE_CONTINUE; }
	virtual update_status postUpdate() { return UPDATE_CONTINUE; }
	virtual bool cleanUp() { return true; }

};

#endif // !__MODULE_H__