//=================================
// included dependencies
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleSceneSpace.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
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
	stop_scrolling_position = 650;
	dobkeratops_texture = app->textures->load("Sprites/Boss1_Dobkeratops.png");

	return true;
}
//
//bool ModuleBoss::cleanUp()
//{ }
//
update_status ModuleBoss::update()
{ 
	if ((app->scene->origin / SCALE_FACTOR + SCREEN_WIDTH) > stop_scrolling_position)
	{
		app->scene->scroll_player_speed = 0;
		app->scene->scroll_camera_speed = 0;
		app->game_interface->speed_interface = 0;
	}
	return UPDATE_CONTINUE;
}
//
//void ModuleBoss::onCollision(Collider *col1, Collider *col2)
//{ }