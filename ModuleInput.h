//=================================
// include guard
#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
private:
	KEY_STATE *keyboard;
	int mouse_x;
	int mouse_y;
	
public:
	
	ModuleInput(Application *app, bool start_enabled = true);
	~ModuleInput();

	bool init();
	update_status preUpdate();
	bool cleanUp();

	bool keyboard_enabled;

	KEY_STATE getKey(int id) const
	{
		return keyboard[id];
	}

	int getMouseX() const
	{
		return mouse_x;
	}

	int getMouseY() const
	{
		return mouse_y;
	}

};

#endif // !__MODULEINPUT_H__