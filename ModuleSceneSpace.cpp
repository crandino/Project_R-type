//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleSceneSpace.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInterface.h"
#include "ModuleEnemy.h"
#include "ModulePowerUp.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneWin.h"
//=================================
// the actual code

//SDL_Rect& scale(SDL_Rect rect)
//{
//	SDL_Rect *rectangle = &rect;
//	rectangle->x *= SCALE_FACTOR;
//	rectangle->y *= SCALE_FACTOR;
//	rectangle->w *= SCALE_FACTOR;
//	rectangle->h *= SCALE_FACTOR;
//	return *rectangle;
//}

ModuleSceneSpace::ModuleSceneSpace(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	boundary_level = NULL;
}

ModuleSceneSpace::~ModuleSceneSpace()
{ }

// Load assets
bool ModuleSceneSpace::start()
{
	LOG("Loading space scene");

	boundary_level = app->textures->load("Sprites/boundary_level.png");

	app->player->enable();
	app->game_interface->enable();
	app->collision->enable();
	app->enemy->enable();
	app->powerup->enable();
	app->particles->enable();	
	app->audio->playMusic("Music/Level1.ogg", 1.0f);

	// Speeds added
	scroll_player_speed = (int)(0.5 * SCALE_FACTOR); //0.333f;
	// Map speed IMPORTANT!
	scroll_camera_speed = (int)(0.5 * SCALE_FACTOR); //1.75f;

	left_limit = (10 * SCALE_FACTOR);
	right_limit = (SCREEN_WIDTH - 22) * SCALE_FACTOR;

	finish = false;

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Wall collider
	app->collision->addCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 142, 192, 64, 32 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 206, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 592, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1232, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 720, 192, 64, 32 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1376, 16, 112, 80 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1376, 144, 112, 80 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1376, 0, 560, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1680, 16, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1680, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1744, 192, 64, 32 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 1744, 16, 64, 32 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2000, 0, 640, 16 }, COLLIDER_WALL, false);

	//Concrete walls by pixel
	app->collision->addCollider({ 2064, 16, 13, 24 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2077, 16, 2, 23 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2079, 16, 1, 22 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2080, 16, 1, 21 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2081, 16, 2, 20 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2083, 16, 1, 19 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2084, 16, 2, 18 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2086, 16, 3, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2089, 16, 2, 15 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2091, 16, 2, 14 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2093, 16, 2, 13 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2095, 16, 2, 12 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2097, 16, 2, 11 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2099, 16, 2, 10 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2101, 16, 2, 9 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2103, 16, 2, 8 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2105, 16, 2, 7 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2107, 16, 3, 6 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2110, 16, 3, 5 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2113, 16, 3, 4 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2116, 16, 3, 3 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2119, 16, 3, 2 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2122, 16, 4, 1 }, COLLIDER_WALL, false);

	//Concrete walls by pixel
	app->collision->addCollider({ 2243, 16, 13, 24 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2241, 16, 2, 23 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2240, 16, 1, 22 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2239, 16, 1, 21 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2237, 16, 2, 20 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2236, 16, 1, 19 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2234, 16, 2, 18 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2231, 16, 3, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2229, 16, 2, 15 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2227, 16, 2, 14 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2225, 16, 2, 13 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2223, 16, 2, 12 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2221, 16, 2, 11 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2219, 16, 2, 10 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2217, 16, 2, 9 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2215, 16, 2, 8 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2213, 16, 2, 7 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2210, 16, 3, 6 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2207, 16, 3, 5 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2204, 16, 3, 4 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2201, 16, 3, 3 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2198, 16, 3, 2 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2194, 16, 4, 1 }, COLLIDER_WALL, false);

	//Concrete walls by pixel
	app->collision->addCollider({ 2064, 200, 13, 24 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2077, 201, 2, 23 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2079, 202, 1, 22 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2080, 203, 1, 21 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2081, 204, 2, 20 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2083, 205, 1, 19 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2084, 206, 2, 18 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2086, 208, 3, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2089, 209, 2, 15 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2091, 210, 2, 14 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2093, 211, 2, 13 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2095, 212, 2, 12 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2097, 213, 2, 11 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2099, 214, 2, 10 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2101, 215, 2, 9 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2103, 216, 2, 8 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2105, 217, 2, 7 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2107, 218, 3, 6 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2110, 219, 3, 5 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2113, 220, 3, 4 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2116, 221, 3, 3 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2119, 222, 3, 2 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2122, 223, 4, 1 }, COLLIDER_WALL, false);


	//Concrete walls by pixel
	app->collision->addCollider({ 2243, 200, 13, 24 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2241, 201, 2, 23 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2240, 202, 1, 22 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2239, 203, 1, 21 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2237, 204, 2, 20 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2236, 205, 1, 19 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2234, 206, 2, 18 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2231, 208, 3, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2229, 209, 2, 15 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2227, 210, 2, 14 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2225, 211, 2, 13 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2223, 212, 2, 12 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2221, 213, 2, 11 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2219, 214, 2, 10 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2217, 215, 2, 9 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2215, 216, 2, 8 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2213, 217, 2, 7 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2210, 218, 3, 6 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2207, 219, 3, 5 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2204, 220, 3, 4 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2201, 221, 3, 3 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2198, 222, 3, 2 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2194, 223, 4, 1 }, COLLIDER_WALL, false);

	app->collision->addCollider({ 2384, 16, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2384, 192, 64, 32 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2640, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2704, 192, 64, 32 }, COLLIDER_WALL, false);

	app->collision->addCollider({ 2704, 0, 64, 48 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2768, 0, 1162, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 3152, 16, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 3472, 16, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 3536, 16, 64, 32 }, COLLIDER_WALL, false);

	app->collision->addCollider({ 3152, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 3472, 208, 64, 16 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 3536, 192, 64, 32 }, COLLIDER_WALL, false);

	app->collision->addCollider({ 2832, 16, 192, 80 }, COLLIDER_WALL, false);
	app->collision->addCollider({ 2832, 148, 192, 80 }, COLLIDER_WALL, false);

	return true;
}

// Unload assets
bool ModuleSceneSpace::cleanUp()
{
	LOG("Unloading space scene");

	app->textures->unload(boundary_level);
	app->player->disable();
	app->game_interface->disable();
	app->enemy->disable();
	app->powerup->disable();
	app->particles->disable();
	app->collision->disable();
	app->audio->stopAllMusic(0.1f);
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::update()
{
	LOG("%d", app->renderer->camera.x)
	if (app->renderer->camera.x > (-3930 * SCALE_FACTOR) && finish == false)
	{
		// Move camera forward
		app->player->position.x += scroll_player_speed;
		app->renderer->camera.x -= scroll_camera_speed;
		left_limit += scroll_player_speed;
		right_limit += scroll_player_speed;

		// Draw everything
		app->renderer->blit(boundary_level, 0, 0, NULL);
	}
	else
	{
		finish = true;
		app->fade->fadeToBlack(this, app->scene_win, 2.0f);
	}
	

	return UPDATE_CONTINUE;
}