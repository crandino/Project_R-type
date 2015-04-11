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

	SDL_Texture *boundary_level;
	//SDL_Texture* stars;

	ModuleSceneSpace(Application *app, bool start_enabled = true);
	~ModuleSceneSpace();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENESPACE_H__