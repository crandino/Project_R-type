#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Module.h"
#include "Globals.h"
#include "SDL2-2.0.3\include\SDL.h"

class ModuleTextures : public Module
{

public:

	ModuleTextures(Application*);
	~ModuleTextures();

	bool init();
	bool cleanUp();

	SDL_Texture* const load(const char* path);

	DList<SDL_Texture> textures;
};

#endif __MODULETEXTURES_H__