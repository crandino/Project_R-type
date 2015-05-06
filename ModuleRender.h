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

	bool blit(SDL_Texture *texture, float x, float y, SDL_Rect *section, float speed = 1.0f);
	bool drawQuad(const SDL_Rect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

};

#endif // !__MODULERENDER_H__