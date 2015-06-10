//=================================
// included dependencies
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleSceneSpace.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleInterface.h"
//=================================
// the actual code

ModuleBoss::ModuleBoss(Application *app, bool start_enabled) :
Module(app, start_enabled)
{ 
	stop_scrolling_position = 3929 * SCALE_FACTOR;

	// Breeding of Dobkeratops
	alien = new Alien();
	alien->position.x = stop_scrolling_position - (97 * SCALE_FACTOR);
	alien->position.y = 112 * SCALE_FACTOR;
	boss_parts.add(alien);

	// Dobkeratops itself
	dobkeratops = new Dobkeratops();
	dobkeratops->position.x = stop_scrolling_position - (170 * SCALE_FACTOR);
	dobkeratops->position.y = 18 * SCALE_FACTOR;
	boss_parts.add(dobkeratops);

	// Antenna1
	antenna1 = new Antenna1();
	antenna1->position.x = stop_scrolling_position - (201 * SCALE_FACTOR);
	antenna1->position.y = 15 * SCALE_FACTOR;

	boss_parts.add(antenna1);

	// Antenna2
	antenna2 = new Antenna2();
	antenna2->position.x = stop_scrolling_position - (113 * SCALE_FACTOR);
	antenna2->position.y = 71 * SCALE_FACTOR;

	boss_parts.add(antenna2);

	// Antenna3
	antenna3 = new Antenna3();
	antenna3->position.x = stop_scrolling_position - (113 * SCALE_FACTOR);
	antenna3->position.y = 144 * SCALE_FACTOR;

	boss_parts.add(antenna3);

	// Antenna4
	antenna4 = new Antenna4();
	antenna4->position.x = stop_scrolling_position - (201 * SCALE_FACTOR);
	antenna4->position.y = 192 * SCALE_FACTOR;

	boss_parts.add(antenna4);
}

ModuleBoss::~ModuleBoss()
{ }

bool ModuleBoss::start()
{

	// Adding texture of boss
	dobkeratops_texture = app->textures->load("Sprites/Boss1_Dobkeratops.png");

	// Adding colliders...
	// Antenna1 
	SDL_Rect rect_antenna1 = { stop_scrolling_position - (200 * SCALE_FACTOR), 32 * SCALE_FACTOR, 16, 16 };
	antenna1->col = app->collision->addCollider(rect_antenna1, COLLIDER_ENEMY, true, this);
	// Antenna2
	SDL_Rect rect_antenna2 = { stop_scrolling_position - (113 * SCALE_FACTOR), 96 * SCALE_FACTOR, 16, 16 };
	antenna2->col = app->collision->addCollider(rect_antenna2, COLLIDER_ENEMY, true, this);
	// Antenna3
	SDL_Rect rect_antenna3 = { stop_scrolling_position - (113 * SCALE_FACTOR), 144 * SCALE_FACTOR, 16, 16 };
	antenna3->col = app->collision->addCollider(rect_antenna3, COLLIDER_ENEMY, true, this);
	// Antenna4
	SDL_Rect rect_antenna4 = { stop_scrolling_position - (200 * SCALE_FACTOR), 192 * SCALE_FACTOR, 16, 16 };
	antenna4->col = app->collision->addCollider(rect_antenna4, COLLIDER_ENEMY, true, this);

	// Stopping music level and initiating boss music.
	app->audio->stopAllMusic(0.1f);
	app->audio->playMusic("Music/Boss_Level.ogg", 1.0f);

	return true;
}
//
//bool ModuleBoss::cleanUp()
//{ }
//
update_status ModuleBoss::update()
{ 
	if ((app->scene->origin + SCREEN_WIDTH * SCALE_FACTOR) > stop_scrolling_position)
	{
		app->scene->scroll_player_speed = 0;
		app->scene->scroll_camera_speed = 0;
		app->game_interface->speed_interface = 0;
	}

	doubleNode<Boss*> *tmp = boss_parts.getFirst();

	while (tmp != NULL)
	{
		Boss *e = tmp->data;

		app->renderer->blit(dobkeratops_texture, e->position.x, e->position.y, &(e->anim.getCurrentFrame()));

		tmp = tmp->next;
	}

	return UPDATE_CONTINUE;
}
//
//void ModuleBoss::onCollision(Collider *col1, Collider *col2)
//{ }