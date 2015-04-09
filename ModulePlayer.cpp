//=================================
// included dependencies
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 100;
	position.y = 100;

	// idle animation (there is no animation here!)
	idle.frames.pushBack({ 101, 3, 32, 14 });
	idle.frames.pushBack({ 134, 3, 32, 13 });
	idle.frames.pushBack({ 167, 3, 31, 13 });
	idle.frames.pushBack({ 200, 3, 32, 13 });
	idle.frames.pushBack({ 233, 3, 32, 14 });
	idle.speed = 0.01f;
}

ModulePlayer::~ModulePlayer()
{ }

// Load assets
bool ModulePlayer::start()
{
	LOG("Loading player...");

	graphics = app->textures->load("Sprites/Arrowhead.png");

	return true;
}

bool ModulePlayer::cleanUp()
{
	LOG("Unloading player");

	app->textures->unload(graphics);

	return true;
}

update_status ModulePlayer::update()
{
	Animation *current_animation = &idle;
	// debug camera movement
	int speed = 1;

	if (app->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;
	}

	if (app->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		position.y += speed;
	}

	//Draw everything
	SDL_Rect r = current_animation->getCurrentFrame();

	app->renderer->blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}