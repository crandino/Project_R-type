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
	app->enemy->enable();
	app->audio->playMusic("Music/Level1.ogg", 1.0f);

	app->renderer->camera.x = app->renderer->camera.y = 0;

	return true;
}

// Unload assets
bool ModuleSceneSpace::cleanUp()
{
	LOG("Unloading space scene");

	app->textures->unload(boundary_level);
	app->player->disable();
	app->enemy->disable();

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