//=================================
// included dependencies
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneGameOver.h"
#include "ModuleInterface.h"
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;

	fx_shoot = 0;
	fx_boom = 0;
	
	// idle animation (there is no animation here, just the ship)
	idle.frames.pushBack({ 167, 3, 31, 13 });

	// from idle to upwards animation
	idle_to_upward.frames.pushBack({ 200, 3, 32, 13 });
	idle_to_upward.frames.pushBack({ 233, 4, 32, 14 });
	idle_to_upward.speed = 0.1f;
	idle_to_upward.loop = false;
	animation_set.pushBack(&idle_to_upward);

	// from upwards to idle animation
	upward_to_idle.frames.pushBack({ 233, 4, 32, 14 });
	upward_to_idle.frames.pushBack({ 200, 3, 32, 13 });
	upward_to_idle.speed = 0.1f;
	upward_to_idle.loop = false;
	animation_set.pushBack(&upward_to_idle);

	// from idle to downwards animation
	idle_to_downward.frames.pushBack({ 134, 3, 32, 13 });
	idle_to_downward.frames.pushBack({ 101, 4, 32, 14 });
	idle_to_downward.speed = 0.1f;
	idle_to_downward.loop = false;
	animation_set.pushBack(&idle_to_downward);

	// from downwards to idle animation
	downward_to_idle.frames.pushBack({ 101, 4, 32, 14 });
	downward_to_idle.frames.pushBack({ 134, 3, 32, 13 });
	downward_to_idle.speed = 0.1f;
	downward_to_idle.loop = false;
	animation_set.pushBack(&downward_to_idle);

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
	animation_set.pushBack(&explosion);
}

ModulePlayer::~ModulePlayer()
{ }

// Load assets
bool ModulePlayer::start()
{
	LOG("Loading player...");

	position.x = 50.f;
	position.y = 100.f;
	speed = 1.5f;

	app->input->keyboard_enabled = true;

	fx_shoot = app->audio->loadFx("Sounds/DisparoNave.wav");
	fx_boom = app->audio->loadFx("Sounds/ExplosionNave.wav");
	graphics = app->textures->load("Sprites/Arrowhead.png");
	current_animation = &idle;

	// CRZ ----
	for (unsigned int i = 0; i < animation_set.getNumElements(); i++)
		animation_set[i]->reset();
	// ---- CRZ

	// Collider to player;
	collider = app->collision->addCollider({ position.x, position.y, 32, 14 }, COLLIDER_PLAYER, app->player);
	
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
	{
		if (position.x > app->scene->limit_xneg)
		{
			position.x -= speed;
		}
		else
		{
			position.x -= 0.f;
		}
	}


	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (position.x < app->scene->limit_xpos)
		{
			position.x += speed;
		}
		else
		{
			position.x += 0.f;
		}
	}


	if (app->input->getKey(SDL_SCANCODE_UP) == KEY_IDLE && app->input->getKey(SDL_SCANCODE_DOWN) == KEY_IDLE)
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
		app->audio->playFx(fx_shoot);
		app->particles->addParticle(app->particles->shot, position.x + 22.f, position.y + 3.f, COLLIDER_PLAYER_SHOT);
	}	

	// Updating collider position
	collider->setPos(position.x, position.y);

	//Draw everything
	app->renderer->blit(graphics, position.x, position.y, &(current_animation->getCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::onCollision(Collider *col1, Collider *col2)
{
	speed = 0.f;
	current_animation = &explosion;
	app->audio->playFx(fx_boom);
	app->input->keyboard_enabled = false;
	
	app->scene->scroll_player_speed = 0.f;
	app->scene->scroll_camera_speed = 0.f;
	app->game_interface->speed_interface = 0.f;

	// Finish game after explosion
	if (!explosion.finished()) app->fade->fadeToBlack(app->scene, app->scene_over, 2.0f);
}