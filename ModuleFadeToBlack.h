//=================================
// include guard
#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__
//=================================
// forward declared dependencies
//class Application;
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleFadeToBlack : public Module
{
private:

	Uint32 start_time;
	Uint32 total_time;
	SDL_Rect screen;
	bool fading_in;
	Module *mod_on;
	Module *mod_off;

public:

	ModuleFadeToBlack(Application *app, bool start_enabled = true);
	~ModuleFadeToBlack();

	update_status update();
	void fadeToBlack(Module* module_off, Module* module_on, float time = 2.0f);

};

#endif //!__MODULEFADETOBLACK_H__