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
#include "Animation.h"
//=================================
// the actual class

class ModuleSceneIntro : public Module
{
public:

	SDL_Texture *graphics;
	SDL_Texture *sprite;
	unsigned int fx;

	Animation numbers_coins;

	ModuleSceneIntro(Application *app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEINTRO_H__