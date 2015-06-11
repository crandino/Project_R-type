//=================================
// included dependencies
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleBoss.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneGameOver.h"
#include "ModuleInterface.h"
#include "ModulePowerUp.h"

#include <time.h>
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;

	fx_shoot = 0;
	fx_big_shoot = 0;
	fx_ribbon_shoot = 0;	
	fx_charging = 0;
	fx_spaceship_explosion = 0;
	
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

	charging_animation.frames.pushBack({ 2, 51, 33, 32 });
	charging_animation.frames.pushBack({ 35, 51, 33, 32 });
	charging_animation.frames.pushBack({ 68, 51, 35, 32 });
	charging_animation.frames.pushBack({ 103, 51, 32, 32 });
	charging_animation.frames.pushBack({ 135, 51, 33, 32 });
	charging_animation.frames.pushBack({ 168, 51, 32, 32 });
	charging_animation.frames.pushBack({ 200, 51, 33, 32 });
	charging_animation.frames.pushBack({ 233, 51, 20, 32 });
	charging_animation.speed = 0.2f;
	charging_animation.loop = true;
	animation_set.pushBack(&charging_animation);
}

ModulePlayer::~ModulePlayer()
{ }

// Load assets
bool ModulePlayer::start()
{
	LOG("Loading player...");

	active = true;
	app->input->keyboard_enabled = true;


	position.x = 400 * SCALE_FACTOR;
	position.y = 100 * SCALE_FACTOR;
	speed = 2 * SCALE_FACTOR;
	start_charging = actual_charging = end_charging = 0;
	charged_shot = false;
	charging = false;
	last_ribbon_shot = 0;
	lifes = 2;

	weapon_type = BASIC_PLAYER_SHOT;
	player_points = 0;

	fx_shoot = app->audio->loadFx("Sounds/DisparoNave.wav");
	fx_big_shoot = app->audio->loadFx("Sounds/DisparoPotenteNave.wav");
	fx_ribbon_shoot = app->audio->loadFx("Sounds/Ribbon_Sound.wav");
	fx_missile_shot = app->audio->loadFx("Sounds/Missile_Sound.wav");
	fx_spaceship_explosion = app->audio->loadFx("Sounds/ExplosionNave.wav");
	fx_charging = app->audio->loadFx("Sounds/Charging_Sound.wav");

	
	graphics = app->textures->load("Sprites/Arrowhead.png");
	current_animation = &idle;

	// Each animation of Player is reseted.
	for (unsigned int i = 0; i < animation_set.getNumElements(); i++)
		animation_set[i]->reset();

	// Collider of player;
	collider = app->collision->addCollider({ position.x, position.y, 32, 14 }, COLLIDER_PLAYER, false, app->player);
	
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
	if (active)
	{
		if (app->input->getKey(SDL_SCANCODE_UP) == KEY_REPEAT  && position.y > 0)
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

		if (app->input->getKey(SDL_SCANCODE_LEFT) == KEY_REPEAT &&
			position.x > app->scene->left_limit)
			position.x -= speed;

		if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT &&
			position.x < app->scene->right_limit)
			position.x += speed;

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

		if (charging == false)
		{
			if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_DOWN && weapon_type == BASIC_PLAYER_SHOT)
			{
				app->audio->playFx(fx_shoot);
				charged_shot = false;
				app->particles->addWeapon(BASIC_PLAYER_SHOT, position.x + 22 * SCALE_FACTOR, position.y + 3 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
				start_charging = SDL_GetTicks();
				charging = true;
			}
		}

		else
		{
			if (weapon_type == BASIC_PLAYER_SHOT)
			{
				actual_charging = SDL_GetTicks();
				if (actual_charging - start_charging > 200)
				{
					app->renderer->blit(graphics, position.x + 30 * SCALE_FACTOR, position.y - 6 * SCALE_FACTOR, &(charging_animation.getCurrentFrame()));
					app->audio->playFx(fx_charging);
				}
			}
		}

		if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_UP)
		{
			switch (weapon_type)
			{
				case BASIC_PLAYER_SHOT:
				{
					end_charging = SDL_GetTicks();
					charging = false;
					if (end_charging - start_charging > 200)
					{
						//No suena casi nunca!!!!!!!
						app->audio->playFx(fx_big_shoot);

						charged_shot = true;
						app->particles->addExplosion(CONTRAIL, position.x + 34 * SCALE_FACTOR, position.y, COLLIDER_NONE);
						app->particles->addExplosion(CONTRAIL, position.x + 34 * SCALE_FACTOR, position.y);
						app->particles->addWeapon(BASIC_PLAYER_SHOT, position.x + 22 * SCALE_FACTOR, position.y, COLLIDER_PLAYER_SHOT);
					}
					start_charging = actual_charging = end_charging = 0;
					break;
				}

				case MISSILE_PLAYER_SHOT:
				{
					app->audio->playFx(fx_missile_shot);
					app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y - 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
					app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y + 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
					break;
				}

				case RIBBON_PLAYER_SHOT:
				{
					
					if ((last_ribbon_shot + 600) < (SDL_GetTicks()) || last_ribbon_shot == 0 || app->particles->active_weapons.count() == 0)
					{
						app->audio->playFx(fx_ribbon_shoot);
						last_ribbon_shot = SDL_GetTicks();
						app->particles->addWeapon(RIBBON_PLAYER_SHOT, position.x + 11 * SCALE_FACTOR, position.y - 22 * SCALE_FACTOR, COLLIDER_RIBBON_SHOT);
					}
					break;
				}
			}
		}
	}

	// Updating collider position
	collider->setPos(position.x, position.y);

	//Draw everything
	if (active)
		app->renderer->blit(graphics, position.x, position.y, &(current_animation->getCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::onCollision(Collider *col1, Collider *col2)
{
	if (col2->type != COLLIDER_POWER_UP && active == true)
	{
		speed = 0;
		app->particles->addExplosion(PLAYER_EXPLOSION, position.x, position.y);
		app->audio->playFx(fx_spaceship_explosion);
		app->input->keyboard_enabled = false;

		app->scene->scroll_speed = 0;

		app->fade->fadeToBlack(app->scene, app->scene_over, 2.0f);
		active = false;
	}
	
}