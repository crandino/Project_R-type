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
#include "ModuleParticles.h"
//=================================
// the actual code

ModuleBoss::ModuleBoss(Application *app, bool start_enabled) :
Module(app, start_enabled)
{ 
	stop_scrolling_position = 3929 * SCALE_FACTOR;
	wait_to_shoot = false;

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

	//DOBKERATOPS
	// Head
	SDL_Rect rect_dob_head1 = { stop_scrolling_position - (122 * SCALE_FACTOR), 18 * SCALE_FACTOR, 20, 20 };
	dobkeratops->col_dob_head1 = app->collision->addCollider(rect_dob_head1, COLLIDER_WALL, true, this);

	SDL_Rect rect_dob_head2 = { stop_scrolling_position - (158 * SCALE_FACTOR), 38 * SCALE_FACTOR, 90, 42 };
	dobkeratops->col_dob_head2 = app->collision->addCollider(rect_dob_head2, COLLIDER_WALL, true, this);

	SDL_Rect rect_dob_head3 = { stop_scrolling_position - (170 * SCALE_FACTOR), 58 * SCALE_FACTOR, 16, 34 };
	dobkeratops->col_dob_head3 = app->collision->addCollider(rect_dob_head3, COLLIDER_WALL, true, this);
	// Body
	SDL_Rect rect_dob_body1 = { stop_scrolling_position - (90 * SCALE_FACTOR), 60 * SCALE_FACTOR, 70, 52 };
	dobkeratops->col_dob_body1 = app->collision->addCollider(rect_dob_body1, COLLIDER_WALL, true, this);

	SDL_Rect rect_dob_body2 = { stop_scrolling_position - (82 * SCALE_FACTOR), 142 * SCALE_FACTOR, 62, 80 };
	dobkeratops->col_dob_body2 = app->collision->addCollider(rect_dob_body2, COLLIDER_WALL, true, this);
	// Tail
	SDL_Rect rect_dob_tail = { stop_scrolling_position - (108 * SCALE_FACTOR), 200 * SCALE_FACTOR, 50, 20 };
	dobkeratops->col_dob_tail = app->collision->addCollider(rect_dob_tail, COLLIDER_WALL, true, this);

	//ALIEN
	SDL_Rect rect_alien = { stop_scrolling_position - (96 * SCALE_FACTOR), 116 * SCALE_FACTOR, 50, 24 };
	alien->col = app->collision->addCollider(rect_alien, COLLIDER_ENEMY, true, this);

	// Stopping music level and initiating boss music.
	app->audio->stopAllMusic();
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
	
	if ((int)alien->anim.current_frame == 4)
		wait_to_shoot = false;

	if (wait_to_shoot == false && (int)alien->anim.current_frame == 2 )
	{
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR , app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 80);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 160);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 240);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 320);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 400);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 480);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 560);
		app->particles->addWeapon(BOSS_WEAPON, app->boss->alien->position.x - 5 * SCALE_FACTOR, app->boss->alien->position.y + 8 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT, 640);
		wait_to_shoot = true;
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