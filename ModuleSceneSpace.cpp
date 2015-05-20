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
//=================================
// the actual code

ModuleSceneSpace::ModuleSceneSpace(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	boundary_level = NULL;
	//stars = NULL;
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

	//Speeds added
	scroll_player_speed = 0.333f;
	//Map speed IMPORTANT!
	scroll_camera_speed = 1.75f;

	limit_xneg = 10.f;
	limit_xpos = SCREEN_WIDTH - 32.f;

	app->renderer->camera.x = app->renderer->camera.y = 0.f;

	// Wall collider
	app->collision->addCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 142, 192, 64, 32 }, COLLIDER_WALL);
	app->collision->addCollider({ 206, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 592, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 1232, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 720, 192, 64, 32 }, COLLIDER_WALL);
	app->collision->addCollider({ 1376, 16, 112, 80 }, COLLIDER_WALL);
	app->collision->addCollider({ 1376, 144, 112, 80 }, COLLIDER_WALL);
	app->collision->addCollider({ 1376, 0, 560, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 1680, 16, 64, 16 }, COLLIDER_WALL);

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
	// Move camera forward

	app->player->position.x += scroll_player_speed;
	app->renderer->camera.x -= scroll_camera_speed;
	limit_xneg += scroll_player_speed;
	limit_xpos += scroll_player_speed;

	// Draw everything
	app->renderer->blit(boundary_level, 0.f, 0.f, NULL);

	return UPDATE_CONTINUE;
}