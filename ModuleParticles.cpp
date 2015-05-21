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
#include "BasicShot.h"
#include "PataShot.h"
// -- Explosions -- 
#include "PlayerExplosion.h"
#include "CommonExplosion.h"

//=================================
// the actual code

ModuleParticles::ModuleParticles(Application *app, bool start_enabled) : Module(app, start_enabled)
{ 
	//Player Ribbon shot
	/*first_ribbon_shot.anim.frames.pushBack({ 0, 0, 12, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 12, 0, 18, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 30, 0, 27, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 57, 0, 37, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 94, 0, 47, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 141, 0, 55, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 196, 0, 61, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 257, 0, 64, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 321, 0, 70, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 391, 0, 81, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 472, 0, 87, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 559, 0, 92, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 651, 0, 98, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 749, 0, 101, 56 });
	first_ribbon_shot.anim.frames.pushBack({ 850, 0, 112, 56 });
	second_ribbon_shot.anim.frames.pushBack({ 962, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1026, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1090, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1154, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1218, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1282, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1346, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1410, 12, 64, 32 });
	second_ribbon_shot.anim.frames.pushBack({ 1474, 12, 64, 32 });
	first_ribbon_shot.anim.loop = false;
	second_ribbon_shot.anim.loop = false;
	first_ribbon_shot.anim.speed = 0.5f;
	second_ribbon_shot.anim.speed = 0.5f;
	first_ribbon_shot.speed.x = 0.5 * SCALE_FACTOR;
	first_ribbon_shot.speed.y = 0 * SCALE_FACTOR;
	second_ribbon_shot.speed.x = 0.5 * SCALE_FACTOR;
	second_ribbon_shot.speed.y = 0 * SCALE_FACTOR;
	first_ribbon_shot.life = 1500;
	second_ribbon_shot.life = 1500;*/

}

ModuleParticles::~ModuleParticles()
{ }

// Load assets
bool ModuleParticles::start()
{
	LOG("Loading particles");

	// Shot particle
	basic_shot = app->textures->load("Sprites/Arrowhead.png");
	//Ribbon particle
	/*first_ribbon_shot.graphics = app->textures->load("Sprites/Ribbon_shot.png");
	second_ribbon_shot.graphics = app->textures->load("Sprites/Ribbon_shot.png");*/
	// Pata-pata shot
	pata_shot = app->textures->load("Sprites/Basic_shot_pata_pata.png");
	// Pata-pata explosion
	common_explosion = app->textures->load("Sprites/Common_explosion.png");
	player_explosion = app->textures->load("Sprites/Arrowhead.png");

	fx_shot_explosion = app->audio->loadFx("Sounds/ColisionDisparo.wav");

	return true;
}

bool ModuleParticles::cleanUp()
{
	LOG("Unloading particles");
	app->textures->unload(basic_shot);
	app->textures->unload(pata_shot);
	app->textures->unload(player_explosion);
	app->textures->unload(common_explosion);
	/*app->textures->unload(explosion.graphics);
	app->textures->unload(first_ribbon_shot.graphics);
	app->textures->unload(second_ribbon_shot.graphics);*/

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
			app->renderer->blit(w->graphics, w->position.x, w->position.y, &(w->anim.getCurrentFrame()));
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
			app->renderer->blit(x->graphics, x->position.x, x->position.y, &(x->anim.getCurrentFrame()));
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

void ModuleParticles::onCollision(Collider *c1, Collider *c2)
{

	doubleNode<Weapons*> *tmp_weapon = active_weapons.getFirst();

	while (tmp_weapon != NULL)
	{
		if (tmp_weapon->data->collider == c1)
		{
			app->audio->playFx(fx_shot_explosion);
			delete tmp_weapon->data;
			active_weapons.del(tmp_weapon);
			break;
		}

		tmp_weapon = tmp_weapon->next;
	}

	doubleNode<Explosions*> *tmp_explosion = active_explosions.getFirst();

	while (tmp_explosion != NULL)
	{
		if (tmp_explosion->data->collider == c1)
		{
			app->audio->playFx(fx_shot_explosion);
			delete tmp_explosion->data;
			active_explosions.del(tmp_explosion);
			break;
		}

		tmp_explosion = tmp_explosion->next;
	}
}

void ModuleParticles::addWeapon(WEAPON_TYPES type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Weapons *p = NULL;

	switch (type)
	{
		case(BASIC_SHOT) : p = new BasicShot(app, basic_shot); break;
		case(PATA_SHOT) : p = new PataShot(app, pata_shot); break;
	}

	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, true, this);
	}

	active_weapons.add(p);
}

void ModuleParticles::addExplosion(EXPLOSION_TYPES type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Explosions *p = NULL;

	switch (type)
	{
	case(COMMON_EXPLOSION) : p = new CommonExplosion(app, common_explosion); break;
	case(PLAYER_EXPLOSION) : p = new PlayerExplosion(app, player_explosion); break;
	}

	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, true, this);
	}

	active_explosions.add(p);
}