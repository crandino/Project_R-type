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
	//app->collision->enable();
	app->audio->playMusic("Music/Level1.ogg", 1.0f);

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
	app->enemy->addEnemy(app->enemy->pata_pata, 600, 10, COLLIDER_ENEMY);
	
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
	app->audio->stopAllMusic(0.1f);
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::update()
{
	// Move camera forward
	int scroll_speed = 1; // It is not used.

	app->player->position.x += 1;
	app->renderer->camera.x -= 2;

	// Draw everything
	app->renderer->blit(boundary_level, 0, 0, NULL);

	return UPDATE_CONTINUE;
}