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

	SDL_Texture* const load(const char* path);
	DList<SDL_Texture*> textures;

	ModuleTextures(Application*);
	~ModuleTextures();

	bool init();
	bool cleanUp();
};

#endif //!__MODULETEXTURES_H__