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
{ }

ModuleBoss::~ModuleBoss()
{ }

bool ModuleBoss::start()
{
	stop_scrolling_position = 3929 * SCALE_FACTOR;
	dobkeratops_texture = app->textures->load("Sprites/Boss1_Dobkeratops.png");

	app->audio->stopAllMusic(0.1f);

	// Breeding of Dobkeratops
	alien = new Alien();
	alien->position.x = stop_scrolling_position - ( 97 * SCALE_FACTOR) ;
	alien->position.y = 112 * SCALE_FACTOR;
	boss_parts.add(alien);
	// Dobkeratops itself
	dobkeratops = new Dobkeratops();
	dobkeratops->position.x = stop_scrolling_position - ( 170 * SCALE_FACTOR );
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