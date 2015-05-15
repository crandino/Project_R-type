//=================================
// include guard
#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
#include "Animation.h"
//=================================
// the actual class

class ModuleSceneGameOver : public Module
{
public:

	SDL_Texture *graphics;
	SDL_Texture *sprite;

	Animation countdown;
	bool fade_to_black;

	ModuleSceneGameOver(Application *app, bool start_enabled = true);
	~ModuleSceneGameOver();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEGAMEOVER_H__