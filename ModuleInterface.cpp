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
#include "BasicPlayerShot.h"
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
	img_beam = app->textures->load("Sprites/Beam.png");
	img_p1 = app->textures->load("Sprites/P1.png");
	img_hi = app->textures->load("Sprites/HighScore.png");
	img_numbers_interface = app->textures->load("Sprites/NumbersInterface.png");
	img_bar = app->textures->load("Sprites/ShotBar.png");
	charge_beam = app->textures->load("Sprites/BeamFill.png");

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
	app->textures->unload(charge_beam);

	return true;
}

// Update: draw background
update_status ModuleInterface::update()
{
	position_interface += app->scene->scroll_speed;
	for (unsigned int i = 1; i <= app->player->lifes; i++)
		app->renderer->blit(img_life, position_interface + (8 * SCALE_FACTOR * i), 241 * SCALE_FACTOR, NULL);
	
	app->renderer->blit(img_beam, position_interface + 90 * SCALE_FACTOR, 241 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_bar, position_interface + 136 * SCALE_FACTOR, 241 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_p1, position_interface + 30 * SCALE_FACTOR, 250 * SCALE_FACTOR, NULL);
	app->renderer->blit(img_hi, position_interface + 154 * SCALE_FACTOR, 249 * SCALE_FACTOR, NULL);

	//Beam rectangle to charge
	if (app->player->charging == true)
	{	
		Uint32 now = SDL_GetTicks();
		unsigned int max_beam = (now - app->player->start_charging) * 128 / 1200;
		if (max_beam > 128) { max_beam = 128;}
		for (unsigned int i = 0; i < max_beam; i++)
			app->renderer->blit(charge_beam, position_interface + (141 + i) * SCALE_FACTOR, 243 * SCALE_FACTOR, NULL);
	}

	print_score(position_interface);
	
	return UPDATE_CONTINUE;
}

void ModuleInterface::print_score(unsigned int pos)
{
	// Score calculation. The method calculates each number on the whole number: units, tens, hundreds, thousands and tens thousands.

	// Printing tens_thousands..
	if (app->player->player_points > 9999)
	{
		numbers_points.current_frame = (app->player->player_points / 10000) % 10;
		app->renderer->blit(img_numbers_interface, pos + 78 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}

	// Printing thousands...
	if (app->player->player_points > 999)
	{
		numbers_points.current_frame = (app->player->player_points / 1000) % 10;
		app->renderer->blit(img_numbers_interface, pos + 87 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}

	// Printing hundreds...
	if (app->player->player_points > 99)
	{
		numbers_points.current_frame = (app->player->player_points / 100) % 10;
		app->renderer->blit(img_numbers_interface, pos + 96 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}

	// Printing tens...
	if (app->player->player_points > 9)
	{
		numbers_points.current_frame = (app->player->player_points / 10) % 10;
		app->renderer->blit(img_numbers_interface, pos + 105 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
	}

	// Printing units
	numbers_points.current_frame = app->player->player_points % 10;
	app->renderer->blit(img_numbers_interface, pos + 114 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));

	// Code for high puntuation.
	/*numbers_points.current_frame = 0;
	app->renderer->blit(img_numbers_interface, pos + 230 * SCALE_FACTOR, 250 * SCALE_FACTOR, &(numbers_points.getCurrentFrame()));
*/
}