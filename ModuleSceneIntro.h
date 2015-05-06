//=================================
// include guard
#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleSceneIntro : public Module
{
public:

	SDL_Texture *graphics;
	unsigned int fx;

	ModuleSceneIntro(Application *app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEINTRO_H__