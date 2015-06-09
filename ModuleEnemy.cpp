//=================================
// included dependencies
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleBoss.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneWin.h"
// -- Enemies --
#include "PataEnemy.h"
#include "BugEnemy.h"
#include "BlasterEnemy.h"
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
	blaster_graphics = app->textures->load("Sprites/Blaster.png");

	fx_pata_explosion = app->audio->loadFx("Sounds/ExplosionPataPata.wav");
	
	LOG("Loading enemies...");

	last_wave = 0;
	
	return true;
}

bool ModuleEnemy::cleanUp()
{
	app->textures->unload(pata_graphics);
	app->textures->unload(bug_graphics);
	app->textures->unload(blaster_graphics);

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
	
	int wave = (app->scene->origin / SCALE_FACTOR + SCREEN_WIDTH);
	switch (wave)
	{
	//	//  ---------------------------------------------------------------
	//	//	---------------------  PATA-PATA ------------------------------
	//	//  ---------------------------------------------------------------
	//case(450) :
	//	// PATA-PATA - Group 1 ( 4 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 450, 30, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 485, 35, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 535, 45, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 575, 60, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(515) :
	//	// PATA-PATA - Group 2 ( 4 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 515, 185, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 545, 175, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 580, 170, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 625, 180, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(700) :
	//	// PATA-PATA - Group 3 ( 3 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 700, 160, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 725, 170, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 760, 165, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(740) :
	//	// PATA-PATA - Group 4 ( 12 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 740, 80, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 760, 65, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 790, 55, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 815, 90, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 850, 60, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 875, 70, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 890, 95, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 955, 52, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 990, 58, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 1025, 80, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 1060, 45, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 1095, 80, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(840) :
	//	// PATA-PATA - Group 5 ( 3 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 840, 60, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 895, 100, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 915, 70, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(875) :
	//	// PATA-PATA - Group 6 ( 1 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 875, 95, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(900) :
	//	// PATA-PATA - Group 7 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 900, 95, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 940, 95, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(945) :
	//	// PATA-PATA - Group 8 ( 1 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 945, 95, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(975) :
	//	// PATA-PATA - Group 9 ( 2 unit )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 975, 50, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 1020, 170, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//case(1040) :
	//	// PATA-PATA - Group 10 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 1040, 60, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 1090, 90, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//	break;

	//// Inside the mothership ------------------------------------------------------

	//case(2495) :
	//	// PATA-PATA - Group 11 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 2495, 140, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 2520, 160, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 2550, 125, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;
	//case(2540) :
	//	// PATA-PATA - Group 11 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(PATA_ENEMY, pata_graphics, 2540, 60, COLLIDER_ENEMY);
	//		addEnemy(PATA_ENEMY, pata_graphics, 2640, 80, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	//	//  ---------------------------------------------------------------
	//	//  ------------------------  BUG ---------------------------------
	//	//  ---------------------------------------------------------------
	//case(550) :
	//	// BUG - Group 1 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BUG_ENEMY, bug_graphics, 600, 110, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 640, 110, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 680, 110, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 720, 110, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 760, 110, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	//case(2000) :
	//	// BUG - Group 5 ( 6 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -30, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -70, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -110, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -150, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -190, COLLIDER_ENEMY);
	//		addEnemy(BUG_ENEMY, bug_graphics, 1960, -230, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		  break;

	//	//  ---------------------------------------------------------------
	//	//  ----------------------  BLASTER -------------------------------
	//	//  ---------------------------------------------------------------
	//case(1687) :
	//	// BLASTER - Group 1 ( 8 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1687, 32, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1687, 193, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1721, 32, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1721, 193, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1753, 48, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1753, 177, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1782, 48, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 1782, 177, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//	break;

	//case(2008) :
	//	// BLASTER - Group 2 ( 2 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2008, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2038, 16, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	//case(2391) :
	//	// BLASTER - Group 3 ( 8 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2391, 32, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2424, 32, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2456, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2488, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2520, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2552, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2584, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2616, 16, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	//case(2711) :
	//	// BLASTER - Group 4 ( 4 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2711, 48, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2743, 48, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2711, 177, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 2743, 177, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	//case(3031) :
	//	// BLASTER - Group 5 ( 6 units )
	//	if (last_wave != wave)
	//	{
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3031, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3064, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3096, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3128, 16, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3160, 32, COLLIDER_ENEMY);
	//		addEnemy(BLASTER_ENEMY, blaster_graphics, 3192, 32, COLLIDER_ENEMY);
	//		last_wave = wave;
	//	}
	//		   break;

	case(3650) :
		// Boss Dobkeratops
		if (last_wave != wave)
		{
			app->boss->enable();
		}
		break;
	}

	return UPDATE_CONTINUE;	
}

// Update: draw enemies
update_status ModuleEnemy::update()
{
	doubleNode<Enemy*> *tmp = active.getFirst();
	doubleNode<Enemy*> *tmp_next = active.getFirst();

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

update_status ModuleEnemy::postUpdate()
{
	doubleNode<Enemy*> *tmp = active.getFirst();
	doubleNode<Enemy*> *tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy *e = tmp->data;
		tmp_next = tmp->next;

		// The enemies that go 30 pixels beyond the left edge of the screen
		// are deleted.
		if (e->position.x < app->scene->origin - 30 * SCALE_FACTOR)
		{
			delete e;
			active.del(tmp);
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
}

void ModuleEnemy::addEnemy(ENEMY_TYPES type, SDL_Texture *texture, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy *e = NULL;

	switch (type)
	{
	case(PATA_ENEMY) : e = new PataEnemy(app, texture); break;
	case(BUG_ENEMY) : e = new BugEnemy(app, texture); break;
	case(BLASTER_ENEMY) : e = new BlasterEnemy(app, texture); break;
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
