//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
//=================================
// the actual code
ModuleRender::ModuleRender(Application *app, bool start_enabled) : Module(app, start_enabled)
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

update_status ModuleRender::preUpdate()
{
	// this function clears the current
	// rendering target with the drawing color
	// (black by default or SDL_SetRenderDrawColor
	// to specify one).
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::update()
{
	int speed = 3;

	// TODO: Change this part to use the pad arrows instead 
	// and add the three remaining options.

	if (app->input->keyboard[SDL_SCANCODE_UP] == 1)
		app->renderer->camera.y += speed;

	return UPDATE_CONTINUE;
}

update_status ModuleRender::postUpdate()
{
	/*This function updates the screen with any
	rendering performed since the previous call.
	As such, you compose your entire scene and "present"
	the composed backbuffer to the screen as a complete picture.*/
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
	{
		//This function queries the attributes of a texture.
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	// It copies a portion of the texture to the current rendering target.
	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return true;
}
