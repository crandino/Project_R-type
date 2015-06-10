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
//=================================
// the actual code

ModulePlayer::ModulePlayer(Application *app, bool start_enabled) :
Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;

	fx_shoot = 0;
	fx_ribbon_shoot = 0;
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

}

ModulePlayer::~ModulePlayer()
{ }

// Load assets
bool ModulePlayer::start()
{
	LOG("Loading player...");

	active = true;
	app->input->keyboard_enabled = true;

	position.x = 50 * SCALE_FACTOR;
	position.y = 100 * SCALE_FACTOR;
	speed = 2 * SCALE_FACTOR;
	last_shot = 0;

	weapon_type = BASIC_PLAYER_SHOT;

	fx_shoot = app->audio->loadFx("Sounds/DisparoNave.wav");
	fx_ribbon_shoot = app->audio->loadFx("Sounds/DisparoRibbon.wav");
	fx_boom = app->audio->loadFx("Sounds/ExplosionNave.wav");
	graphics = app->textures->load("Sprites/Arrowhead.png");
	current_animation = &idle;

	// CRZ ----
	for (unsigned int i = 0; i < animation_set.getNumElements(); i++)
		animation_set[i]->reset();
	// ---- CRZ

	// Collider to player;
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

		if (app->input->getKey(SDL_SCANCODE_LCTRL) == KEY_UP)
		{
			switch (weapon_type)
			{
				case BASIC_PLAYER_SHOT:
				{
					app->audio->playFx(fx_shoot);
					app->particles->addWeapon(BASIC_PLAYER_SHOT, position.x + 22 * SCALE_FACTOR, position.y + 3 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
					break;
				}

				case MISSILE_PLAYER_SHOT:
				{
					app->audio->playFx(fx_shoot);
					app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y - 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
					app->particles->addWeapon(MISSILE_PLAYER_SHOT, position.x + 10 * SCALE_FACTOR, position.y + 8 * SCALE_FACTOR, COLLIDER_PLAYER_SHOT);
					break;
				}

				case RIBBON_PLAYER_SHOT:
				{
					
					if ((last_shot + 600) < (SDL_GetTicks()) || last_shot == 0 || app->particles->active_weapons.count() == 0)
					{
						app->audio->playFx(fx_ribbon_shoot);
						last_shot = SDL_GetTicks();
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
		app->particles->addExplosion(PLAYER_EXPLOSION, position.x, position.y, COLLIDER_NONE);
		app->audio->playFx(fx_boom);
		app->input->keyboard_enabled = false;

		app->scene->scroll_player_speed = 0;
		app->scene->scroll_camera_speed = 0;
		app->game_interface->speed_interface = 0;

		app->fade->fadeToBlack(app->scene, app->scene_over, 2.0f);
		active = false;
	}
	
}