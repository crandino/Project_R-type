//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "Application.h"
//=================================
// the actual code
ModuleRender::ModuleRender(Application *app) : Module(app)
{
	renderer = NULL;
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{
}

bool ModuleRender::init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(app->window->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::update()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	return UPDATE_CONTINUE;
}

bool ModuleRender::cleanUp()
{
	LOG("Destroying renderer");

	// Destroy window
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	return true;
}

//Blit to screen
bool ModuleRender::blit(SDL_Texture *texture, int x, int y, SDL_Rect *section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return true;
}
