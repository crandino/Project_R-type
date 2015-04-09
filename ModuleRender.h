//=================================
// include guard
#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__
//=================================
// forward declared dependencies
//class Application;
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleRender : public Module
{
public:

	SDL_Renderer *renderer;
	SDL_Rect camera;

	ModuleRender(Application *app, bool start_enabled = true);
	~ModuleRender();

	bool init();
	update_status preUpdate();
	update_status update();
	update_status postUpdate();
	bool cleanUp();

	bool blit(SDL_Texture *texture, int x, int y, SDL_Rect *section, float speed = 1.0f);
	
};

#endif // !__MODULERENDER_H__