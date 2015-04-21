//=================================
// include guard
#ifndef __MODULESCENEWIN_H__
#define __MODULESCENEWIN_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleSceneWin : public Module
{
public:

	SDL_Texture *graphics;

	unsigned int fx;

	ModuleSceneWin(Application *app, bool start_enabled = true);
	~ModuleSceneWin();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULESCENEWIN_H__