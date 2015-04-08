//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL_image/include/SDL_image.h"

#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
//=================================
// the actual code

ModuleTextures::ModuleTextures(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

// Destructor
ModuleTextures::~ModuleTextures()
{ }

// Called before render is available
bool ModuleTextures::init()
{
	LOG("Init Image Library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::cleanUp()
{
	LOG("Freeing textures and Image Library");

	doubleNode<SDL_Texture*>* item = textures.getFirst();

	while (item != NULL)
	{
		SDL_DestroyTexture(item->data);
		item = item->next;
	}

	textures.delAll();
	IMG_Quit();
	return true;
}

SDL_Texture* const ModuleTextures::load(const char *path)
{
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(app->renderer->renderer, surface);
	
		if (texture == NULL)
		{
			LOG("Unable to create texture form surface! SDL_Error: %s", SDL_GetError());
		}
		else
		{
			textures.add(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}