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

	SDL_Texture *intro;
	SDL_Texture *numbers;
	SDL_Texture *press_space_to_start;
	unsigned int fx;

	Animation numbers_coins;
	Animation press_space_glow;

	ModuleSceneIntro(Application *app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEINTRO_H__