//=================================
// include guard
#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleBoss : public Module
{

public:

	SDL_Texture *dobkeratops_texture;

	unsigned int stop_scrolling_position;

	ModuleBoss(Application *app, bool start_enabled = true);
	~ModuleBoss();

	bool start();
	update_status update();
	//bool cleanUp();
	//void onCollision(Collider *col1, Collider *col2);

};
#endif // !__MODULEBOSS_H__