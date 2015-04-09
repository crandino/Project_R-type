//=================================
// include guard
#ifndef __MODULEPOINT2D_H__
#define __MODULEPOINT2D_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "Point2d.h"
//=================================
// the actual class

class ModulePlayer : public Module
{
public:
	SDL_Texture *graphics;
	Animation idle;
	Animation downward;
	Animation upward;
	Point2d<int> position;

	ModulePlayer(Application *app, bool start_enabled = true);
	~ModulePlayer();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULEPOINT2D_H__