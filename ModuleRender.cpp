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
{ }

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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	// this function clears the current
	// rendering target with the drawing color
	// (black by default or SDL_SetRenderDrawColor
	// to specify one).
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::update()
{
	float speed = 3.f;

	if (app->input->getKey(SDL_SCANCODE_KP_8) == KEY_REPEAT)
		app->renderer->camera.y += speed;
	if (app->input->getKey(SDL_SCANCODE_KP_2) == KEY_REPEAT)
		app->renderer->camera.y -= speed;
	if (app->input->getKey(SDL_SCANCODE_KP_4) == KEY_REPEAT)
		app->renderer->camera.x += 2*speed;
	if (app->input->getKey(SDL_SCANCODE_KP_6) == KEY_REPEAT)
		app->renderer->camera.x -= speed;

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
bool ModuleRender::blit(SDL_Texture *texture, float x, float y, SDL_Rect *section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (float)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (float)(camera.y * speed) + y * SCREEN_SIZE;

	//LOG("%s %d %d", "Camera:", camera.x, camera.y);

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

bool ModuleRender::drawQuad(const SDL_Rect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
	}

	return ret;
}
