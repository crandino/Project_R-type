#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

class ModuleRender : public Module
{
public:
	SDL_Renderer* renderer;

	ModuleRender(Application*);
	~ModuleRender();

	bool init();
	update_status update();
	bool cleanUp();

	// Put a graphic over another is called Blit.
	bool blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);
};

#endif __MODULERENDER_H__
