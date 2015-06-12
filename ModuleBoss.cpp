//=================================
// included dependencies
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneWin.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleInterface.h"
#include "ModuleParticles.h"
#include <math.h>
//=================================
// the actual code

ModuleBoss::ModuleBoss(Application *app, bool start_enabled) :
Module(app, start_enabled)
{ 
	stop_scrolling_position = 3929 * SCALE_FACTOR;
}

ModuleBoss::~ModuleBoss()
{ }

bool ModuleBoss::start()
{
	faded = false;
	wait_to_shoot = false;

	fx_explosion = app->audio->loadFx("Sounds/BossExplosion.wav");
	fx_hit = app->audio->loadFx("Sounds/BossHit.wav");
	fx_explosion_antenna = app->audio->loadFx("Sounds/ExplosionTabrok.wav");

	// Breeding of Dobkeratops
	alien = new Alien();
	alien->position.x = stop_scrolling_position - (97 * SCALE_FACTOR);
	alien->position.y = 112 * SCALE_FACTOR;
	boss_parts.add(alien);
	alien->points = 300;
	alien->last_hit_time = 0;

	alien->life = 30;
	alien->dead_time = 0;
	// Dobkeratops itself
	dobkeratops = new Dobkeratops();
	dobkeratops->position.x = stop_scrolling_position - (170 * SCALE_FACTOR);
	dobkeratops->position.y = 18 * SCALE_FACTOR;
	boss_parts.add(dobkeratops);
	dobkeratops->points = 5000;

	// Antenna1
	antenna1 = new Antenna1();
	antenna1->position.x = stop_scrolling_position - (201 * SCALE_FACTOR);
	antenna1->position.y = 15 * SCALE_FACTOR;

	boss_parts.add(antenna1);
	antenna1->points = 300;

	// Antenna2
	antenna2 = new Antenna2();
	antenna2->position.x = stop_scrolling_position - (113 * SCALE_FACTOR);
	antenna2->position.y = 71 * SCALE_FACTOR;

	boss_parts.add(antenna2);
	antenna2->points = 300;

	// Antenna3
	antenna3 = new Antenna3();
	antenna3->position.x = stop_scrolling_position - (113 * SCALE_FACTOR);
	antenna3->position.y = 144 * SCALE_FACTOR;

	boss_parts.add(antenna3);
	antenna3->points = 300;

	// Antenna4
	antenna4 = new Antenna4();
	antenna4->position.x = stop_scrolling_position - (201 * SCALE_FACTOR);
	antenna4->position.y = 192 * SCALE_FACTOR;
	antenna4->points = 300;

	boss_parts.add(antenna4);

	// Tail
	tail = new Tail();

	float incr = 0.05f;
	float incr_delta = 0.1f;
	for (unsigned int i = 0; i < tail->num_balls; i++)
	{

		tail->current_positions.pushBack({ stop_scrolling_position - ((121 + (i * 7)) * SCALE_FACTOR), 195 * SCALE_FACTOR });
		tail->top_positions.pushBack({ stop_scrolling_position - ((121 + (i * 6)) * SCALE_FACTOR), (195 - (i * 3 * incr)) * SCALE_FACTOR });
		tail->bottom_positions.pushBack({ stop_scrolling_position - ((121 + (i * 7)) * SCALE_FACTOR), 195 * SCALE_FACTOR });
		tail->speeds.pushBack({ 0 * SCALE_FACTOR, 0 * SCALE_FACTOR });

		incr += incr_delta;
	}
	
	tail->going_up = true;

	// Adding texture of boss
	dobkeratops_texture = app->textures->load("Sprites/BossDobkeratops.png");

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

	// Tail
	SDL_Rect rect_tail;
	for (unsigned int i = 0; i < tail->num_balls; i++)
	{
		rect_tail = { tail->current_positions[i].x, tail->current_positions[i].y, 16, 16 };
		tail->colliders.pushBack(app->collision->addCollider(rect_tail, COLLIDER_WALL, true, this));
	}

	// Stopping music level and initiating boss music.
	app->audio->stopAllMusic();
	app->audio->playMusic("Music/Boss_Level.ogg", 1.0f);

	return true;
}

bool ModuleBoss::cleanUp()
{
	LOG("Unloading boss");

	app->textures->unload(dobkeratops_texture);

	doubleNode<Boss*> *item = boss_parts.getFirst();
	
	while (item != NULL)
	{
		delete item->data;
		item = item->next;
	}

	delete tail;

	boss_parts.clear();

	return true;
}

update_status ModuleBoss::update()
{ 
	//Stop the scroll
	if ((app->scene->origin + SCREEN_WIDTH * SCALE_FACTOR) > stop_scrolling_position)
		app->scene->scroll_speed = 0;
	
	if ((int)alien->anim.current_frame == 4)
		wait_to_shoot = false;

	if (wait_to_shoot == false && (int)alien->anim.current_frame == 2 && alien->life > 0)
	{
		//Alien shot
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

	//When player wins
	if (app->boss->alien->life <= 0)
	{
		if(alien->dead_time == 0) app->boss->alien->dead_time = SDL_GetTicks();

		if (SDL_GetTicks() >(app->boss->alien->dead_time + 2550))
		{
			SDL_SetTextureColorMod(dobkeratops_texture,0,0,0);
		}

		if (SDL_GetTicks() >(app->boss->alien->dead_time + 5000) && faded == false)
		{
			faded = true;
			app->fade->fadeToBlack(app->scene, app->scene_win, 3.0f);
		}
	}

	// ----------------------------
	// --------- LA COLA ----------

	float dx, dy;
	unsigned int pos_reached = 0;
	int speed_value = 0.4 * SCALE_FACTOR;
	float incr_factor = 1.1f;

	for (unsigned int i = 0; i < tail->current_positions.getNumElements(); i++)
	{

		if (tail->going_up == true)
		{
			dx = tail->top_positions[i].x - tail->current_positions[i].x;
			dy = tail->top_positions[i].y - tail->current_positions[i].y;
		}
		else
		{
			dx = tail->bottom_positions[i].x - tail->current_positions[i].x;
			dy = tail->bottom_positions[i].y - tail->current_positions[i].y;
		}

		float angle = atan(dy / dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}

		if (tail->going_up == true)
		{
			if (tail->current_positions[i].isClosedTo(tail->top_positions[i], 1.5 * SCALE_FACTOR))
			{
				tail->speeds[i].setZero();
				pos_reached++;
			}			
			else
			{
				tail->speeds[i].x = (cos(angle) * speed_value);
				tail->speeds[i].y = (sin(angle) * speed_value);
				tail->current_positions[i] += tail->speeds[i];
			}
		}
		else
		{
			if (tail->current_positions[i].isClosedTo(tail->bottom_positions[i], 1.5 * SCALE_FACTOR))
			{
				tail->speeds[i].setZero();
				pos_reached++;
			}
			else
			{
				tail->speeds[i].x = (cos(angle) * speed_value);
				tail->speeds[i].y = (sin(angle) * speed_value);
				tail->current_positions[i] += tail->speeds[i];
			}
		}

		speed_value *= incr_factor;
	}	

	if (pos_reached == tail->num_balls)
	{
		if (tail->going_up == true)
			tail->going_up = false;
		else
			tail->going_up = true;
	}	

	for (unsigned int i = 0; i < tail->colliders.getNumElements(); i++)
		tail->colliders[i]->setPos(tail->current_positions[i].x, tail->current_positions[i].y);

	for (unsigned int i = 0; i < tail->num_balls; i++)
	{
		if (i < 8) { tail->anim.current_frame = 1; }
		else if (i < 14) { tail->anim.current_frame = 2; }
		else if (i < 19) { tail->anim.current_frame = 3; }
		else { tail->anim.current_frame = 0; }

		app->renderer->blit(dobkeratops_texture, tail->current_positions[i].x, tail->current_positions[i].y, &(tail->anim.getCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}

void ModuleBoss::onCollision(Collider *col1, Collider *col2)
{
	doubleNode<Boss*> *item = boss_parts.getFirst();
	while (item != NULL && item->data->col != col1)
		item = item->next;

	if (item != NULL)
	{
		if (item->data->col == alien->col){
			//hit alien col
			if (alien->life >= 1){
				alien->life--;
				if (alien->last_hit_time == 0 || alien->last_hit_time + 300 < SDL_GetTicks())
				{
					alien->last_hit_time = SDL_GetTicks();
					app->audio->playFx(fx_hit);
				}
				app->particles->addExplosion(BOSS_HIT, stop_scrolling_position - (170 * SCALE_FACTOR), 18 * SCALE_FACTOR, 0);
			}
			if (alien->life == 0)
			{
				alien->life--;
				app->player->player_points += alien->points;
				app->player->player_points += dobkeratops->points;
				app->particles->addExplosion(COMMON_EXPLOSION, col1->rect.x, col1->rect.y);
				col1->to_delete = true;
				app->audio->playFx(fx_explosion);

				//BOSS EXPLOSION
				//Start head
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (132 * SCALE_FACTOR), (4 * SCALE_FACTOR), 0);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (162 * SCALE_FACTOR), (22 * SCALE_FACTOR), 300);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (22 * SCALE_FACTOR), 600);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (182 * SCALE_FACTOR), (42 * SCALE_FACTOR), 900);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (90 * SCALE_FACTOR), (52 * SCALE_FACTOR), 1200);
				//Head 2
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (132 * SCALE_FACTOR), (4 * SCALE_FACTOR), 1500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (162 * SCALE_FACTOR), (22 * SCALE_FACTOR), 2100);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (22 * SCALE_FACTOR), 1700);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (182 * SCALE_FACTOR), (42 * SCALE_FACTOR), 2300);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (90 * SCALE_FACTOR), (52 * SCALE_FACTOR), 1900);
				//Start body
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (130 * SCALE_FACTOR), (52 * SCALE_FACTOR), 1500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (62 * SCALE_FACTOR), (90 * SCALE_FACTOR), 1800);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (90 * SCALE_FACTOR), 2000);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (66 * SCALE_FACTOR), (126 * SCALE_FACTOR), 2200);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (106 * SCALE_FACTOR), (126 * SCALE_FACTOR), 2400);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (170 * SCALE_FACTOR), 2500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (122 * SCALE_FACTOR), (174 * SCALE_FACTOR), 2600);

				//Head sec
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (132 * SCALE_FACTOR), (4 * SCALE_FACTOR), 1200);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (162 * SCALE_FACTOR), (22 * SCALE_FACTOR), 1500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (22 * SCALE_FACTOR), 1800);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (182 * SCALE_FACTOR), (42 * SCALE_FACTOR), 2100);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (90 * SCALE_FACTOR), (52 * SCALE_FACTOR), 2400);
				//Head 2 sec
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (132 * SCALE_FACTOR), (4 * SCALE_FACTOR), 1700);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (162 * SCALE_FACTOR), (22 * SCALE_FACTOR), 3300);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (22 * SCALE_FACTOR), 2900);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (182 * SCALE_FACTOR), (42 * SCALE_FACTOR), 3500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (90 * SCALE_FACTOR), (52 * SCALE_FACTOR), 3100);
				//Body sec
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (130 * SCALE_FACTOR), (52 * SCALE_FACTOR), 4100);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (62 * SCALE_FACTOR), (90 * SCALE_FACTOR), 4000);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (90 * SCALE_FACTOR), 3600);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (66 * SCALE_FACTOR), (126 * SCALE_FACTOR), 3400);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (106 * SCALE_FACTOR), (126 * SCALE_FACTOR), 3200);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (170 * SCALE_FACTOR), 3000);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (122 * SCALE_FACTOR), (174 * SCALE_FACTOR), 2700);

				//Head all
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (132 * SCALE_FACTOR), (4 * SCALE_FACTOR), 2600);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (162 * SCALE_FACTOR), (22 * SCALE_FACTOR), 2580);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (22 * SCALE_FACTOR), 2560);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (182 * SCALE_FACTOR), (42 * SCALE_FACTOR), 2540);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (90 * SCALE_FACTOR), (52 * SCALE_FACTOR), 2500);
				//Body all
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (130 * SCALE_FACTOR), (52 * SCALE_FACTOR), 2500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (62 * SCALE_FACTOR), (90 * SCALE_FACTOR), 2500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (90 * SCALE_FACTOR), 2500);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (66 * SCALE_FACTOR), (126 * SCALE_FACTOR), 2540);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (106 * SCALE_FACTOR), (126 * SCALE_FACTOR), 2560);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (102 * SCALE_FACTOR), (170 * SCALE_FACTOR), 2580);
				app->particles->addExplosion(HUGE_EXPLOSION, stop_scrolling_position - (122 * SCALE_FACTOR), (174 * SCALE_FACTOR), 2600);
			}
		}
		//hil antenna col
		else
		{
			app->player->player_points += item->data->points;
			app->audio->playFx(fx_explosion_antenna);
			app->particles->addExplosion(COMMON_EXPLOSION, col1->rect.x, col1->rect.y);
			col1->to_delete = true;
			delete item->data;
			boss_parts.del(item);
		}
	}

	
}
