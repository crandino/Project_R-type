//=================================
// include guard
#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleSceneSpace : public Module
{
public:

	SDL_Texture *level1;
	SDL_Texture *background;

	int scroll_speed;    // Velocity to move the scenario.
	int right_limit;	 // Screen right limit for the screen.
	int left_limit;		 // Screen left limit for the screen.

	int origin;          // Position reference to other modules.

	ModuleSceneSpace(Application *app, bool start_enabled = true);
	~ModuleSceneSpace();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENESPACE_H__