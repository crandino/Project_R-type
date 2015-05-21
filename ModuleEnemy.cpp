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

	fx_pata_explosion = app->audio->loadFx("Sounds/ExplosionPataPata.wav");
	
	LOG("Loading enemies...");

	/*addEnemy(BUG_ENEMY, bug_graphics, 650, 120, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 690, 120, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 730, 120, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 770, 120, COLLIDER_ENEMY);
	addEnemy(BUG_ENEMY, bug_graphics, 810, 120, COLLIDER_ENEMY);*/
	
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

update_status ModuleEnemy::preUpdate()
{
	/* The intention of this method is to create enemies on the fly
	and to eliminate each enemy that will be outside the screen limits.*/

	// Adding enemies
	switch (app->scene->proyectile_barrier->rect.x / SCALE_FACTOR)
	{
	// PATA-PATA -----------------------------------------------------
	case(450) :

		// PATA-PATA - Group 1 ( 4 units )
		addEnemy(PATA_ENEMY, pata_graphics, 450, 30, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 485, 35, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 535, 45, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 575, 60, COLLIDER_ENEMY);
		break;

	case(515) :
		// PATA-PATA - Group 2 ( 4 units )
		addEnemy(PATA_ENEMY, pata_graphics, 515, 185, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 545, 175, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 580, 190, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 625, 180, COLLIDER_ENEMY);
		break;

	case(700) :
		// PATA-PATA - Group 3 ( 3 units )
		addEnemy(PATA_ENEMY, pata_graphics, 700, 160, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 725, 170, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 760, 165, COLLIDER_ENEMY);
		break;
	
	case(740) :
		// PATA-PATA - Group 4 ( 12 units )
		addEnemy(PATA_ENEMY, pata_graphics, 740, 80, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 760, 65, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 790, 55, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 815, 90, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 850, 60, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 875, 70, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 890, 95, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 955, 52, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 990, 58, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1025, 80, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1060, 45, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1095, 80, COLLIDER_ENEMY);
		break;

	case(1150) :
		// PATA-PATA - Group 5 ( 3 units )
		addEnemy(PATA_ENEMY, pata_graphics, 1150, 50, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1265, 65, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1285, 55, COLLIDER_ENEMY);
		break;

	case(1400) :
		// PATA-PATA - Group 6 ( 1 units )
		addEnemy(PATA_ENEMY, pata_graphics, 1400, 175, COLLIDER_ENEMY);
		break;

	case(1525) :
		// PATA-PATA - Group 7 ( 2 units )
		addEnemy(PATA_ENEMY, pata_graphics, 1525, 175, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1565, 175, COLLIDER_ENEMY);
		break;

	case(1680) :
		// PATA-PATA - Group 8 ( 1 units )
		addEnemy(PATA_ENEMY, pata_graphics, 1680, 175, COLLIDER_ENEMY);
		break;

	case(1935) :
		// PATA-PATA - Group 9 ( 2 units )
		addEnemy(PATA_ENEMY, pata_graphics, 1935, 175, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 1980, 175, COLLIDER_ENEMY);
		break;

	case(2165) :
		// PATA-PATA - Group 10 ( 2 units )
		addEnemy(PATA_ENEMY, pata_graphics, 2165, 175, COLLIDER_ENEMY);
		addEnemy(PATA_ENEMY, pata_graphics, 2215, 175, COLLIDER_ENEMY);
		break;

	// And there are more inside the mothership.

	// BUG -----------------------------------------------------
	case(560) :
		// BUG - Group 1 ( 5 units)
		addEnemy(BUG_ENEMY, bug_graphics, 600, 160, COLLIDER_ENEMY);
		addEnemy(BUG_ENEMY, bug_graphics, 638, 160, COLLIDER_ENEMY);
		addEnemy(BUG_ENEMY, bug_graphics, 676, 160, COLLIDER_ENEMY);
		addEnemy(BUG_ENEMY, bug_graphics, 714, 160, COLLIDER_ENEMY);
		addEnemy(BUG_ENEMY, bug_graphics, 752, 160, COLLIDER_ENEMY);


	}




	// We elimante enemies that were at the left side of the screen.
	/*doubleNode<Enemy*> *tmp = active.getFirst();
	doubleNode<Enemy*> *tmp_next;

	while (tmp != NULL)
	{
		Enemy *e = tmp->data;
		tmp_next = tmp->next;

		if (e->position.x < (app->scene->proyectile_barrier->rect.x / SCALE_FACTOR) - SCREEN_WIDTH)
		{
			delete e;
			active.del(tmp);
		}
		tmp = tmp_next;
	}*/

	return UPDATE_CONTINUE;	
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
		app->particles->addExplosion(COMMON_EXPLOSION, col1->rect.x, col1->rect.y);
		app->audio->playFx(fx_pata_explosion);
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
