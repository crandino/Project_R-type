//=================================
// include guard
#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "DList.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleTextures : public Module
{
public:

	DList<SDL_Texture*> textures;

	ModuleTextures(Application *app, bool start_enabled = true);
	~ModuleTextures();

	bool init();
	bool cleanUp();

	SDL_Texture* const load(const char* path);
	void unload(SDL_Texture *texture);
};

#endif //!__MODULETEXTURES_H__