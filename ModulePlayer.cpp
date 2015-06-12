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

	fx_charging = 0;
	
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
	//Initialize atributes
	active = true;
	app->input->keyboard_enabled = true;

	position.x = 50 * SCALE_FACTOR;
	position.y = 100 * SCALE_FACTOR;
	speed = 2 * SCALE_FACTOR;
	start_charging = actual_charging = end_charging = first_sound_moment = 0;
	charging_sound_duration = 836;
	charged_shot = false;
	charging = false;
	first_charging_sound_played = false;
	last_ribbon_shot = 0;
	lifes = 2;

	weapon_type = BASIC_PLAYER_SHOT;
	player_points = 0;
	
	//Load images and sounds
	graphics = app->textures->load("Sprites/Arrowhead.png");
	current_animation = &idle;

	fx_charging = app->audio->loadFx("Sounds/Charging_Sound.wav");

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
		//Method that manages the movement of the player
		move();

		//Method that manages the shot of the player
		shoot();
	}

	// Updating collider position
	collider->setPos(position.x, position.y);

	//Draw everything
	if (active)
		app->renderer->blit(graphics, position.x, position.y, &(current_animation->getCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::shoot()
{
	//Method that manages the charging of the basic weapon 
	charge_basic_shot();

	if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_UP)
	{
		//A switch for each type of weapons
		switch (weapon_type)
		{
			case BASIC_PLAYER_SHOT:
			{
				//Player finishes the charge.
				end_charging = SDL_GetTicks();
				charging = false;
				//Only do the charge shot if the time of charge is enough big
				if (end_charging - start_charging > 200)
				{
					charged_shot = true;
					//Boolean that is used in charge_basic_shot() to indicate if the first charging sound is played 
					first_charging_sound_played = false;
					app->audio->playFx(app->particles->fx_big_shot);
					app->particles->addExplosion(CONTRAIL, position.x + 34 * SCALE_FACTOR, position.y);
					app->particles->addWeapon(BASIC_PLAYER_SHOT, position.x + 22 * SCALE_FACTOR, position.y, COLLIDER_PLAYER_SHOT);
				}
				start_charging = actual_charging = end_charging = first_sound_moment= 0;
				break;
			}

			case MISSILE_PLAYER_SHOT:
			{
				app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y - 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
				app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y + 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
				break;
			}

			case RIBBON_PLAYER_SHOT:
			{
				app->particles->addWeapon(RIBBON_PLAYER_SHOT, position.x + 11 * SCALE_FACTOR, position.y - 22 * SCALE_FACTOR, COLLIDER_RIBBON_SHOT);
				break;
			}
		}
	}
}

//Method that create and update the charging of the basic weapon
void ModulePlayer::charge_basic_shot()
{
	//If player is not charging, starts to charge and shoots a basic shot.
	if (charging == false)
	{
		if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_DOWN && weapon_type == BASIC_PLAYER_SHOT)
		{
			app->audio->playFx(app->particles->fx_shot);
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
			//Only can render and play the animation of charging if the player push 0,2 sec CTRL
			if (actual_charging - start_charging > 200)
			{
				app->renderer->blit(graphics, position.x + 30 * SCALE_FACTOR, position.y - 6 * SCALE_FACTOR, &(charging_animation.getCurrentFrame()));
				//The sound of charge only sounds each time that finish last charging_sound. 
				//We saved the moment that sounds the first sound and after we calcule the remainder to know if it's necessary play the next sound.
				if (first_charging_sound_played != true)
				{
					app->audio->playFx(fx_charging);
					first_sound_moment = SDL_GetTicks();
					first_charging_sound_played = true;
				}

				if ((actual_charging - first_sound_moment) % charging_sound_duration < 100)//100 = margin of error of remainder
					app->audio->playFx(fx_charging);
			}
		}
	}
}

void ModulePlayer::move()
{
	//Upward movement
	if (app->input->getKey(SDL_SCANCODE_UP) == KEY_REPEAT  && position.y > 0)
	{
		position.y -= speed;

		if (current_animation != &idle_to_upward)
		{
			idle_to_upward.reset();
			current_animation = &idle_to_upward;
		}
	}

	//Downward movement
	if (app->input->getKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y += speed;

		if (current_animation != &idle_to_downward)
		{
			idle_to_downward.reset();
			current_animation = &idle_to_downward;
		}
	}

	//Left movement
	if (app->input->getKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && position.x > app->scene->left_limit)
		position.x -= speed;

	//Right movement
	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && position.x < app->scene->right_limit)
		position.x += speed;

	//Stabilize animation
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
}

void ModulePlayer::onCollision(Collider *col1, Collider *col2)
{
	//If player collides with a powerup doesnt die, if it does with another entity die.
	//When player die scroll stops and inputs are not accepted. Then close SceneSpace and open GameOverSpace
	if (col2->type != COLLIDER_POWER_UP && active == true)
	{
		speed = 0;
		app->particles->addExplosion(PLAYER_EXPLOSION, position.x, position.y);
		app->input->keyboard_enabled = false;

		app->scene->scroll_speed = 0;

		app->fade->fadeToBlack(app->scene, app->scene_over, 2.0f);
		active = false;
	}
	
}