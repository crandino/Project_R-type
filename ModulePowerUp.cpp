//=================================
// included dependencies
#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSceneSpace.h"
#include "BasicPowerUp.h"
#include "RibbonPowerUp.h"
#include "MissilePowerUp.h"
//=================================
// the actual code

ModulePowerUp::ModulePowerUp(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

ModulePowerUp::~ModulePowerUp()
{ }

// Load assets
bool ModulePowerUp::start()
{
	LOG("Loading PowerUp textures");

	fx_power_up = app->audio->loadFx("Sounds/PowerUP.wav");

	basic_graphics = app->textures->load("Sprites/basic_powerup.png");
	ribbon_graphics = app->textures->load("Sprites/ribbon_powerup.png");
	missile_graphics = app->textures->load("Sprites/Missile_PowerUp.png");

	LOG("Loading PowerUps...");

	// Adding powerups
	addPowerUp(BASIC_POWERUP, 3000, 110, COLLIDER_POWER_UP);
	addPowerUp(RIBBON_POWERUP, 1150, 110, COLLIDER_POWER_UP);
	addPowerUp(MISSILE_POWERUP, 200, 110, COLLIDER_POWER_UP);

	return true;
}

bool ModulePowerUp::cleanUp()
{
	app->textures->unload(basic_graphics);
	app->textures->unload(ribbon_graphics);
	app->textures->unload(missile_graphics);

	doubleNode<PowerUp*> *item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	active.clear();

	return true;
}

// Update: draw PowerUps
update_status ModulePowerUp::update()
{
	doubleNode<PowerUp*>* tmp = active.getFirst();
	doubleNode<PowerUp*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		PowerUp *p = tmp->data;
		tmp_next = tmp->next;

		if (p->update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= p->born)
		{
			app->renderer->blit(p->graphics, p->position.x, p->position.y, &(p->anim.getCurrentFrame()));
		}
		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModulePowerUp::onCollision(Collider *col1, Collider *col2)
{
	doubleNode<PowerUp*> *item = active.getFirst();
	while (item != NULL && item->data->collider != col1)
		item = item->next;

	if (item != NULL)
	{
		app->audio->playFx(fx_power_up);

		switch (item->data->type)
		{
			case(BASIC_POWERUP) : app->player->weapon_type = BASIC_PLAYER_SHOT; break;
			case(RIBBON_POWERUP) : app->player->weapon_type = RIBBON_PLAYER_SHOT; break;
			case(MISSILE_POWERUP) : app->player->weapon_type = MISSILE_PLAYER_SHOT; break;
		}

		delete item->data;
		active.del(item);
	}
	
}

void ModulePowerUp::addPowerUp(POWERUP_TYPES type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	PowerUp *p = NULL;

	switch (type)
	{
	case(BASIC_POWERUP) : p = new BasicPowerUp(app, basic_graphics); break;
	case(RIBBON_POWERUP) : p = new RibbonPowerUp(app, ribbon_graphics); break;
	case(MISSILE_POWERUP) : p = new MissilePowerUp(app, missile_graphics); break;
	}

	p->born = SDL_GetTicks() + delay;
	p->position.x = x * SCALE_FACTOR;
	p->position.y = y * SCALE_FACTOR;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, true, this);
	}

	if (p != NULL)
		active.add(p);
}