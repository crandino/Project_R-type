//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
//=================================
// the actual code

ModuleFadeToBlack::ModuleFadeToBlack(Application *app, bool start_enabled) :
Module(app, start_enabled), start_time(0), total_time(0), fading_in(true)
{
	screen = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{ }

// Load assets
bool ModuleFadeToBlack::start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(app->renderer->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

update_status ModuleFadeToBlack::update()
{
	if (start_time > 0)
	{
		Uint32 now = SDL_GetTicks() - start_time;
		float normalized = (float)now / (float)total_time;

		if(normalized > 1.0f)
			normalized = 1.0f;

		if (fading_in == false)
			normalized = 1.0f - normalized;

		SDL_SetRenderDrawColor(app->renderer->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(app->renderer->renderer, &screen);

		if (now >= total_time)
		{
			if (fading_in == true)
			{
				total_time += total_time;
				start_time = SDL_GetTicks();
				fading_in = false;
			}
			else
				start_time = 0;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleFadeToBlack::fadeToBlack(Module *module_off, Module *module_on, float time)
{
	fading_in = true;
	start_time = SDL_GetTicks();
	total_time = (Uint32)(time * 0.5f * 1000.0f);
}