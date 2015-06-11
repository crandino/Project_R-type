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

	//Game over textures
	SDL_Texture *graphics;
	SDL_Texture *sprite;
	SDL_Texture *numbers;
	SDL_Texture *press_space_to_start;

	Animation numbers_coins;
	Animation countdown;
	Animation press_space_glow;
	bool fade_to_black;

	ModuleSceneGameOver(Application *app, bool start_enabled = true);
	~ModuleSceneGameOver();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEGAMEOVER_H__