//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleInterface.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//=================================
// the actual code

ModuleInterface::ModuleInterface(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	// From numbers_points animation
	numbers_points.frames.pushBack({ 0, 0, 8, 7 });
	numbers_points.frames.pushBack({ 8, 0, 8, 7 });
	numbers_points.frames.pushBack({ 16, 0, 8, 7 });
	numbers_points.frames.pushBack({ 24, 0, 8, 7 });
	numbers_points.frames.pushBack({ 32, 0, 8, 7 });
	numbers_points.frames.pushBack({ 40, 0, 8, 7 });
	numbers_points.frames.pushBack({ 48, 0, 8, 7 });
	numbers_points.frames.pushBack({ 56, 0, 8, 7 });
	numbers_points.frames.pushBack({ 64, 0, 8, 7 });
	numbers_points.frames.pushBack({ 72, 0, 8, 7 });
	numbers_points.speed = 0.0f;
	numbers_points.loop = false;
}

ModuleInterface::~ModuleInterface()
{ }

// Load assets
bool ModuleInterface::start()
{
	LOG("Loading Interface");

	img_life = app->textures->load("Sprites/Life.png");
	img_beam = app->textures->load("Sprites/BEAM.png");
	img_p1 = app->textures->load("Sprites/P1.png");
	img_hi = app->textures->load("Sprites/Hi-.png");
	img_numbers_interface = app->textures->load("Sprites/numbers_interface.png");
	img_bar = app->textures->load("Sprites/Shot_Bar.png");

	position_interface = 2 * SCALE_FACTOR;

	return true;
}

// Unload assets
bool ModuleInterface::cleanUp()
{
	LOG("Unloading Interface");

	app->textures->unload(img_life);
	app->textures->unload(img_beam);
	app->textures->unload(img_p1);
	app->textures->unload(img_hi);
	app->textures->unload(img_numbers_interface);
	app->textures->unload(img_bar);

	return true;
}

// Update: draw background
update_status ModuleInterface::update()
{
	position_interface += app->scene->scroll_speed;
	for (unsigned int i = 1; i <= app->player->lifes; i++)
	{
		app->renderer->blit(img_life, position_interface + (8 * SCALE_FACTOR * i), 241 * SCALE_FACTOR, NULL);
	}
	
	app->renderer->blit(img_beam, position_interface + 90 * SCALE_FACTOR, 241 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_bar, position_interface + 136 * SCALE_FACTOR, 241 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_p1, position_interface + 30 * SCALE_FACTOR, 250 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_hi, position_interface + 154 * SCALE_FACTOR, 249 * SCALE_FACTOR, NULL);

	// Points visualization
	if (app->player->player_points > 9999)
	{
		unsigned int tens_thousands = (app->player->player_points / 10000) % 10;
		numbers_points.current_frame = tens_thousands;
		app->renderer->blit(img_numbers_interface, position_interface + 78 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}
	if (app->player->player_points > 999)
	{
		unsigned int thousands = (app->player->player_points / 1000) % 10;
		numbers_points.current_frame = thousands;
		app->renderer->blit(img_numbers_interface, position_interface + 87 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}
		
	if (app->player->player_points > 99)
	{
		unsigned int hundreds = (app->player->player_points / 100) % 10;
		numbers_points.current_frame = hundreds;
		app->renderer->blit(img_numbers_interface, position_interface + 96 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}
			
	if (app->player->player_points > 9)
	{
		unsigned int tens = (app->player->player_points / 10) % 10;
		numbers_points.current_frame = tens;
		app->renderer->blit(img_numbers_interface, position_interface + 105 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}
				
	unsigned int units = app->player->player_points % 10;
	numbers_points.current_frame = units;
	app->renderer->blit(img_numbers_interface, position_interface + 114 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
				
	numbers_points.current_frame = 0;
	app->renderer->blit(img_numbers_interface, position_interface + 230 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	
	return UPDATE_CONTINUE;
}