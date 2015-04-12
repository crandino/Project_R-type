//=================================
// included dependencies
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = &idle;

	position.x = 50;
	position.y = 100;

	// idle animation (there is no animation here, just the ship)
	idle.frames.pushBack({ 167, 3, 31, 13 });

	// from idle to upwards animation
	idle_to_upward.frames.pushBack({ 200, 3, 32, 13 });
	idle_to_upward.frames.pushBack({ 233, 4, 32, 14 });
	idle_to_upward.speed = 0.1f;
	idle_to_upward.loop = false;

	// from upwards to idle animation
	upward_to_idle.frames.pushBack({ 233, 4, 32, 14 });
	upward_to_idle.frames.pushBack({ 200, 3, 32, 13 });
	upward_to_idle.speed = 0.1f;
	upward_to_idle.loop = false;

	// from idle to downwards animation
	idle_to_downward.frames.pushBack({ 134, 3, 32, 13 });
	idle_to_downward.frames.pushBack({ 101, 4, 32, 14 });
	idle_to_downward.speed = 0.1f;
	idle_to_downward.loop = false;

	// from downwards to idle animation
	downward_to_idle.frames.pushBack({ 101, 4, 32, 14 });
	downward_to_idle.frames.pushBack({ 134, 3, 32, 13 });
	downward_to_idle.speed = 0.1f;
	downward_to_idle.loop = false;
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
	// debug camera movement
	int speed = 1;

	if (app->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		position.y -= speed;

		if (current_animation != &idle_to_upward)
		{
			idle_to_upward.reset();
			current_animation = &idle_to_upward;
		}
	}
	
	if (app->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		position.y += speed;

		if (current_animation != &idle_to_downward)
		{
			idle_to_downward.reset();
			current_animation = &idle_to_downward;
		}
	}
	
	if (app->input->keyboard[SDL_SCANCODE_LEFT] == 1)
		position.x -= speed;

	if (app->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
		position.x += speed;

	if (app->input->keyboard[SDL_SCANCODE_UP] == 0 && app->input->keyboard[SDL_SCANCODE_DOWN] == 0)
	{
		if (current_animation == &idle_to_upward)
			current_animation = &upward_to_idle;

		if (current_animation == &idle_to_downward)
			current_animation = &downward_to_idle;

		if (upward_to_idle.finished() || downward_to_idle.finished())
		{
			upward_to_idle.reset();
			downward_to_idle.reset();
			current_animation = &idle;
		}
	}	

	if (app->input->keyboard_down[SDL_SCANCODE_LCTRL] == 1)
	{
		app->particles->addParticle(app->particles->shot, 
									position.x + 22,
									position.y + 3);
	}

	//Draw everything
	app->renderer->blit(graphics, position.x, position.y, &(current_animation->getCurrentFrame()));

	return UPDATE_CONTINUE;
}