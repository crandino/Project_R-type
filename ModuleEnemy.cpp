//=================================
// included dependencies
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneWin.h"
// -- Enemies --
#include "PataEnemy.h"
#include "BugEnemy.h"
//=================================
// the actual code

ModuleEnemy::ModuleEnemy(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

ModuleEnemy::~ModuleEnemy()
{ }

// Load assets
bool ModuleEnemy::start()
{
	LOG("Loading enemy textures");

	pata_graphics = app->textures->load("Sprites/Pata_pata.png");
	bug_graphics = app->textures->load("Sprites/Bug.png");
	
	LOG("Loading enemies...");

	// Adding enemies
	addEnemy(PATA_ENEMY, pata_graphics, 700.f, 100.f, COLLIDER_ENEMY);
	addEnemy(PATA_ENEMY, pata_graphics, 650.f, 125.f, COLLIDER_ENEMY);
	addEnemy(PATA_ENEMY, pata_graphics, 400.f, 150.f, COLLIDER_ENEMY);

	addEnemy(BUG_ENEMY, bug_graphics, 1100, 50, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 1140, 50, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 1180, 50, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 1220, 50, COLLIDER_ENEMY);
	
	return true;
}

bool ModuleEnemy::cleanUp()
{
	app->textures->unload(pata_graphics);
	app->textures->unload(bug_graphics);

	doubleNode<Enemy*> *item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	active.clear();

	return true;
}

// Update: draw enemies
update_status ModuleEnemy::update()
{
	doubleNode<Enemy*>* tmp = active.getFirst();
	doubleNode<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy *e = tmp->data;
		tmp_next = tmp->next;

		if (e->update() == false)
		{
			delete e;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= e->born)
		{
			app->renderer->blit(e->graphics, e->position.x, e->position.y, &(e->anim.getCurrentFrame()));
			if (e->fx_played == false)
			{
				e->fx_played = true;
				app->audio->playFx(e->fx);
			}
		}
		tmp = tmp_next;
	}
		
	return UPDATE_CONTINUE;
}

void ModuleEnemy::onCollision(Collider *col1, Collider *col2)
{ 
	doubleNode<Enemy*> *item = active.getFirst();
	while (item != NULL && item->data->collider != col1)
		item = item->next;

	if (item != NULL)
	{
		app->particles->addParticle(app->particles->explosion, col1->rect.x, col1->rect.y);
		delete item->data;
		active.del(item);
	}

	/*if (!app->particles->pata_explosion.anim.finished()){
		app->fade->fadeToBlack(app->scene, app->scene_win, 3.0f);*/
}

void ModuleEnemy::addEnemy(enemy_types type, SDL_Texture *texture, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy *e = NULL;

	switch (type)
	{
	case(PATA_ENEMY) : e = new PataEnemy(app, texture); break;
	case(BUG_ENEMY) : e = new BugEnemy(app, texture); break;
	}

	e->born = SDL_GetTicks() + delay;
	e->position.x = x * SCALE_FACTOR;
	e->position.y = y * SCALE_FACTOR;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = app->collision->addCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, true, this);
	}

	if (e != NULL)
		active.add(e);
}
