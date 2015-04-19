//=================================
// include guard
#ifndef __MODULE_H__
#define __MODULE_H__
//=================================
// forward declared dependencies
class Application;
struct Collider;
//=================================
// included dependencies
#include "Globals.h"
//=================================
// the actual class

class Module
{
private:
	bool enabled;

public:

	Application *app;

	Module(Application *parent, bool start_enabled = true) : app(parent), enabled(start_enabled)
	{ }

	bool isEnabled() const { return enabled; }
	
	void enable()
	{
		if (enabled == false)
		{
			enabled = true;
			start();
		}
	}

	void disable()
	{
		if (enabled == true)
		{
			enabled = false;
			cleanUp();
		}
	}

	virtual bool init() { return true; }
	virtual bool start() { return true; }
	virtual update_status preUpdate() { return UPDATE_CONTINUE; }
	virtual update_status update() { return UPDATE_CONTINUE; }
	virtual update_status postUpdate() { return UPDATE_CONTINUE; }
	virtual bool cleanUp() { return true; }
	virtual void onCollision(Collider *col1, Collider *col2)
	{ }

};

#endif // !__MODULE_H__