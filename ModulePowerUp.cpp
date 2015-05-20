//=================================
// included dependencies
#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSceneSpace.h"
#include "RibbonPowerUp.h"
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

	ribbon_graphics = app->textures->load("Sprites/ribbon_powerup.png");

	LOG("Loading PowerUps...");

	// Adding enemies
	addPowerUp(RIBBON_POWERUP, ribbon_graphics, 500.f, 100.f, COLLIDER_POWER_UP);

	return true;
}

bool ModulePowerUp::cleanUp()
{

	app->textures->unload(ribbon_graphics);

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
	/*doubleNode<PowerUp*> *item = active.getFirst();
	while (item != NULL && item->data->collider != col1)
		item = item->next;

	if (item != NULL)
	{
		app->particles->addParticle(app->particles->explosion, col1->rect.x, col1->rect.y);
		delete item->data;
		active.del(item);
	}*/
}

void ModulePowerUp::addPowerUp(powerup_types type, SDL_Texture *texture, float x, float y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	PowerUp *p = NULL;

	switch (type)
	{
	case(RIBBON_POWERUP) : p = new RibbonPowerUp(app, texture); break;
	}

	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = app->collision->addCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	if (p != NULL)
		active.add(p);
}