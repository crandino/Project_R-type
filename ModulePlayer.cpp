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
	position.y = 300;

	// idle animation (there is no animation here!)
	//idle.frames.pushBack({ 167, 3, 31, 13 });

	// upwards animation
	upward.frames.pushBack({ 167, 3, 31, 13 });
	upward.frames.pushBack({ 200, 3, 32, 13 });
	upward.frames.pushBack({ 233, 4, 32, 14 });
	upward.speed = 0.1f;
	upward.loop = false;

	// downwards animation
	downward.frames.pushBack({ 167, 3, 31, 13 });
	downward.frames.pushBack({ 134, 3, 32, 13 });
	downward.frames.pushBack({ 101, 4, 32, 14 });
	downward.speed = 0.1f;
	downward.loop = false;
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

	if (app->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		current_animation = &upward;
		position.y -= speed;
	}
	
	if (app->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		current_animation = &downward;
		position.y += speed;
	}
	
	if (app->input->keyboard[SDL_SCANCODE_LEFT] == 1)
		position.x -= speed;

	if (app->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
		position.x += speed;

	//Draw everything
	SDL_Rect r = current_animation->getCurrentFrame();

	app->renderer->blit(graphics, position.x, position.y - r.h , &r);

	return UPDATE_CONTINUE;
}