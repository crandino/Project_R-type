//=================================
// included dependencies
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneGameOver.h"
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;
	current_animation = &idle;

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

	// explosion animation
	explosion.frames.pushBack({ 1, 343, 32, 28 });
	explosion.frames.pushBack({ 35, 343, 32, 28 });
	explosion.frames.pushBack({ 68, 343, 32, 28 });
	explosion.frames.pushBack({ 101, 343, 32, 28 });
	explosion.frames.pushBack({ 134, 343, 32, 28 });
	explosion.frames.pushBack({ 167, 343, 32, 28 });
	explosion.frames.pushBack({ 233, 343, 32, 28 });
	explosion.speed = 0.4f;
	explosion.loop = false;
}

ModulePlayer::~ModulePlayer()
{ }

// Load assets
bool ModulePlayer::start()
{
	LOG("Loading player...");

	position.x = 50;
	position.y = 100;

	speed = 1;

	graphics = app->textures->load("Sprites/Arrowhead.png");
	current_animation = &idle;
	LOG("current animation ship");

	// Collider to player;
	collider = app->collision->addCollider({ position.x, position.y, 32, 14 }, COLLIDER_PLAYER);
	collider->callback = app->player;

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

	if (app->input->getKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		position.y -= speed;

		if (current_animation != &idle_to_upward)
		{
			idle_to_upward.reset();
			current_animation = &idle_to_upward;
		}
	}
	
	if (app->input->getKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y += speed;

		if (current_animation != &idle_to_downward)
		{
			idle_to_downward.reset();
			current_animation = &idle_to_downward;
		}
	}
	
	if (app->input->getKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		position.x -= speed;

	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		position.x += speed;

	if (app->input->getKey(SDL_SCANCODE_UP) == 0 && app->input->getKey(SDL_SCANCODE_DOWN) == 0)
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

	if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_UP)
	{
		app->particles->addParticle(app->particles->shot, position.x + 22, position.y + 3, COLLIDER_PLAYER_SHOT);
	}

	// Updating collider position
	collider->setPos(position.x, position.y);

	//Draw everything
	app->renderer->blit(graphics, position.x, position.y, &(current_animation->getCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::onCollision(Collider *col1, Collider *col2)
{
	speed = 0;
	current_animation = &explosion;
<<<<<<< HEAD
	// Finish game after explosion
=======
	app->scene->scroll_player_speed = 0;
	app->scene->scroll_camera_speed = 0;

>>>>>>> origin/master
	if (!explosion.finished()) app->fade->fadeToBlack(app->scene, app->scene_over, 2.0f);
}