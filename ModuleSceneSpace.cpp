//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleSceneSpace.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
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

	app->collision->enable();
	app->player->enable();
	app->enemy->enable();
	app->particles->enable();
	app->audio->playMusic("Music/Level1.ogg", 1.0f);

	//Speeds added
	scroll_player_speed = 1;
	scroll_camera_speed = 2;

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Wall collider
	app->collision->addCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 142, 192, 64, 32 }, COLLIDER_WALL);
	app->collision->addCollider({ 206, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 592, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 1232, 208, 64, 16 }, COLLIDER_WALL);
	app->collision->addCollider({ 720, 192, 64, 32 }, COLLIDER_WALL);
	app->collision->addCollider({ 1376, 16, 112, 80 }, COLLIDER_WALL);
	app->collision->addCollider({ 1376, 144, 112, 80 }, COLLIDER_WALL);

	// Adding enemies
	app->enemy->addEnemy(app->enemy->pata_pata, 600, 40, COLLIDER_ENEMY);
	
	return true;
}

// Unload assets
bool ModuleSceneSpace::cleanUp()
{
	LOG("Unloading space scene");

	app->textures->unload(boundary_level);
	app->player->disable();
	app->enemy->disable();
	app->collision->disable();
	app->particles->disable();
	app->audio->stopAllMusic(0.1f);
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::update()
{
	// Move camera forward

	app->player->position.x += scroll_player_speed;
	app->renderer->camera.x -= scroll_camera_speed;

	// Draw everything
	app->renderer->blit(boundary_level, 0, 0, NULL);

	return UPDATE_CONTINUE;
}