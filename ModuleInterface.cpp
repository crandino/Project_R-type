//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleInterface.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//=================================
// the actual code

ModuleInterface::ModuleInterface(Application *app, bool start_enabled) : Module(app, start_enabled)
{ }

ModuleInterface::~ModuleInterface()
{ }

// Load assets
bool ModuleInterface::start()
{
	LOG("Loading Interface");

	img_life = app->textures->load("Sprites/Life.png");
	img_beam = app->textures->load("Sprites/BEAM.png");
	img_hi = app->textures->load("Sprites/Hi-.png");
	img_numbers_interface = app->textures->load("Sprites/numbers_interface.png");
	img_bar = app->textures->load("Sprites/Shot_Bar.png");

	position_interface = 32.f;
	speed_interface = 0.333333f;

	return true;
}

// Unload assets
bool ModuleInterface::cleanUp()
{
	LOG("Unloading Interface");

	app->textures->unload(img_life);
	app->textures->unload(img_beam);
	app->textures->unload(img_hi);
	app->textures->unload(img_numbers_interface);
	app->textures->unload(img_bar);

	return true;
}

// Update: draw background
update_status ModuleInterface::update()
{
	position_interface += speed_interface;
	for ( float i = 1; i <= app->player->lives ; i++)
	{
		app->renderer->blit(img_life, position_interface + (8 * i), 241.f, NULL);
	}
	
	app->renderer->blit(img_beam, position_interface + 50.f, 241.f, NULL);
	app->renderer->blit(img_hi, position_interface + 114.f, 249.f, NULL);
	//app->renderer->blit(img_numbers_interface, 183.f, 249.f, NULL);
	app->renderer->blit(img_bar, position_interface + 96.f, 241.f, NULL);
	return UPDATE_CONTINUE;
}