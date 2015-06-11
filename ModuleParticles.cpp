//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollision.h"
// -- Weapons -- 
#include "BasicPlayerShot.h"
#include "RibbonShot.h"
#include "MissilePlayerShot.h"
#include "BasicEnemyShot.h"
#include "BossWeapon.h"

// -- Explosions -- 
#include "PlayerExplosion.h"
#include "Contrail.h"
#include "PlayerBasicShotExplosion.h"
#include "PlayerMissileShotExplosion.h"
#include "CommonExplosion.h"
#include "HugeExplosion.h"
#include "BossHit.h"
#include "PlayerBasicShotChargedExplosion.h"
//=================================
// the actual code

ModuleParticles::ModuleParticles(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

ModuleParticles::~ModuleParticles()
{ }

// Load assets
bool ModuleParticles::start()
{
	LOG("Loading particles");

	// Weapons
	basic_player_shot = app->textures->load("Sprites/Arrowhead.png");
	ribbon_player_shot = app->textures->load("Sprites/Ribbon_shot.png");
	missile_player_shot = app->textures->load("Sprites/Player_missiles.png");
	missile_propulsion = app->textures->load("Sprites/Missile_propulsion.png");
	basic_enemy_shot = app->textures->load("Sprites/Basic_shot_pata_pata.png");
	boss_weapon = app->textures->load("Sprites/Boss_weapon.png");
	
	// Explosions
	basic_player_shot_explosion = app->textures->load("Sprites/basic_player_shot_explosion.png");
	missile_player_shot_explosion = app->textures->load("Sprites/missile_player_shot_explosion.png");
	common_explosion = app->textures->load("Sprites/Common_explosion.png");
	huge_explosion = app->textures->load("Sprites/huge_explosion.png");
	player_explosion = app->textures->load("Sprites/Arrowhead.png");
	contrail = app->textures->load("Sprites/Contrail.png");
	charged_explosion = app->textures->load("Sprites/Charged_Explosion.png");
	boss_hit = app->textures->load("Sprites/Boss1_Dobkeratops_negative.png");

	fx_shot_explosion = app->audio->loadFx("Sounds/ColisionDisparo.wav");

	last_missile_shot = last_ribbon_shot = missile_counter = 0;
	ribbon_delay = 600;
	missile_delay = 1000;

	return true;
}

bool ModuleParticles::cleanUp()
{
	LOG("Unloading particles");
	app->textures->unload(basic_player_shot_explosion);
	app->textures->unload(basic_player_shot);
	app->textures->unload(missile_player_shot_explosion);
	app->textures->unload(missile_player_shot);
	app->textures->unload(basic_enemy_shot);
	app->textures->unload(player_explosion);
	app->textures->unload(contrail);
	app->textures->unload(common_explosion);
	app->textures->unload(huge_explosion);
	app->textures->unload(ribbon_player_shot);
	app->textures->unload(charged_explosion);
	app->textures->unload(boss_hit);
	

	doubleNode<Weapons*> *item_weapon = active_weapons.getLast();

	while (item_weapon != NULL)
	{
		delete item_weapon->data;
		item_weapon = item_weapon->previous;
	}

	active_weapons.clear();

	doubleNode<Explosions*> *item_explosion = active_explosions.getLast();

	while (item_explosion != NULL)
	{
		delete item_explosion->data;
		item_explosion = item_explosion->previous;
	}

	active_explosions.clear();

	return true;
}

// Update: draw background
update_status ModuleParticles::update()
{
	doubleNode<Weapons*>* tmp_weapon = active_weapons.getFirst();
	doubleNode<Weapons*>* tmp_weapon_next = active_weapons.getFirst();

	while (tmp_weapon != NULL)
	{
		Weapons *w = tmp_weapon->data;
		tmp_weapon_next = tmp_weapon->next;

		if (w->update() == false)
		{
			delete w;
			active_weapons.del(tmp_weapon);
		}
		else if (SDL_GetTicks() >= w->born)
		{
			app->renderer->blit(w->graphics, w->position.x, w->position.y, &(w->current_animation->getCurrentFrame()));				

			if (w->fx_played == false)
			{
				w->fx_played = true;
				app->audio->playFx(w->fx);
			}
		}

		tmp_weapon = tmp_weapon_next;
	}

	doubleNode<Explosions*>* tmp_explosion = active_explosions.getFirst();
	doubleNode<Explosions*>* tmp_explosion_next = active_explosions.getFirst();

	while (tmp_explosion != NULL)
	{
		Explosions *x = tmp_explosion->data;
		tmp_explosion_next = tmp_explosion->next;

		if (x->update() == false)
		{
			delete x;
			active_explosions.del(tmp_explosion);
		}
		else if (SDL_GetTicks() >= x->born)
		{
			app->renderer->blit(x->graphics, x->position.x, x->position.y, &(x->current_animation->getCurrentFrame()));
			if (x->fx_played == false)
			{
				x->fx_played = true;
				app->audio->playFx(x->fx);
			}
		}

		tmp_explosion = tmp_explosion_next;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleParticles::postUpdate()
{
	doubleNode<Weapons*>* tmp_weapon = active_weapons.getFirst();
	doubleNode<Weapons*>* tmp_weapon_next = active_weapons.getFirst();

	while (tmp_weapon != NULL)
	{
		Weapons *w = tmp_weapon->data;
		tmp_weapon_next = tmp_weapon->next;

		if (w->position.x > app->scene->origin + ((SCREEN_WIDTH + 30) * SCALE_FACTOR))
		{
			delete w;
			active_weapons.del(tmp_weapon);
		}

		tmp_weapon = tmp_weapon_next;
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::onCollision(Collider *c1, Collider *c2)
{

	doubleNode<Weapons*> *tmp_weapon = active_weapons.getFirst();

	while (tmp_weapon != NULL)
	{
		if (tmp_weapon->data->collider == c1)
		{
			switch (tmp_weapon->data->type)
			{
				case(BASIC_PLAYER_SHOT):
				{
					if (c2->type == COLLIDER_WALL)
					{
						if (app->player->charged_shot == true)
						{
							//Print position from charged explosion with collider shot measures and explosion measures
							addExplosion(CHARGED_EXPLOSION, c1->rect.x + (c1->rect.w - (28 * SCALE_FACTOR)), c1->rect.y - 13 *SCALE_FACTOR);
							app->audio->playFx(fx_shot_explosion);
						}

						else
						{
							addExplosion(BASIC_PLAYER_SHOT_EXPLOSION, c1->rect.x, c1->rect.y);
							app->audio->playFx(fx_shot_explosion);
						}

						delete tmp_weapon->data;
						active_weapons.del(tmp_weapon);
						break;
					}

					if (c2->type == COLLIDER_ENEMY)
					{
						if (tmp_weapon->data->power > 0)
							tmp_weapon->data->power--;

						if (tmp_weapon->data->power <= 0)
						{
							delete tmp_weapon->data;
							active_weapons.del(tmp_weapon);
						}
						break;
					}
				}

				case(MISSILE_PLAYER_SHOT) :
				{
					addExplosion(MISSILE_PLAYER_SHOT_EXPLOSION, c1->rect.x, c1->rect.y);
					app->audio->playFx(app->enemy->fx_pata_explosion);
					delete tmp_weapon->data;
					active_weapons.del(tmp_weapon);
					break;
				}

				case(RIBBON_PLAYER_SHOT) :
				{
					break;
				}
			}
			break;
		}

		tmp_weapon = tmp_weapon->next;
	}
}

void ModuleParticles::addWeapon(WEAPON_TYPES type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Weapons *p = NULL;

	switch (type)
	{
		case(BASIC_PLAYER_SHOT) : p = new BasicPlayerShot(app, basic_player_shot); break;
		case(RIBBON_PLAYER_SHOT) : 
		{
			if ((last_ribbon_shot + ribbon_delay) < (SDL_GetTicks()))
			{
				last_ribbon_shot = SDL_GetTicks();
				p = new RibbonShot(app, ribbon_player_shot);
			}
			break; 
		}
		case(MISSILE_PLAYER_SHOT) : 
		{
			if ((last_missile_shot + missile_delay) < (SDL_GetTicks()) || missile_counter % 2 != 0)
			{
				last_missile_shot = SDL_GetTicks();
				p = new MissilePlayerShot(app, missile_player_shot, missile_propulsion);
				missile_counter++;
			}
			break;
		}
		case(BASIC_ENEMY_SHOT) : p = new BasicEnemyShot(app, basic_enemy_shot); break;
		case(BOSS_WEAPON) : p = new BossWeapon(app, boss_weapon); break;
	}

	if (p != NULL)
	{
		p->born = SDL_GetTicks() + delay;
		p->position.x = x;
		p->position.y = y;

		if (collider_type != COLLIDER_NONE)
			p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, true, this);

		active_weapons.add(p);
	}
}

void ModuleParticles::addExplosion(EXPLOSION_TYPES type, int x, int y, Uint32 delay)
{
	Explosions *p = NULL;

	switch (type)
	{
	case(COMMON_EXPLOSION) : p = new CommonExplosion(app, common_explosion); break;
	case(CHARGED_EXPLOSION) : p = new PlayerBasicShotChargedExplosion(app, charged_explosion); break;
	case(HUGE_EXPLOSION) : p = new HugeExplosion(app, huge_explosion); break;
	case(PLAYER_EXPLOSION) : p = new PlayerExplosion(app, player_explosion); break;
	case(CONTRAIL) : p = new Contrail(app, contrail); break;
	case(BASIC_PLAYER_SHOT_EXPLOSION) : p = new PlayerBasicShotExplosion(app, basic_player_shot_explosion); break;
	case(MISSILE_PLAYER_SHOT_EXPLOSION) : p = new PlayerMissileShotExplosion(app, missile_player_shot_explosion); break;
	case(BOSS_HIT) : p = new BossHit(app, boss_hit); break;
	}

	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active_explosions.add(p);
}