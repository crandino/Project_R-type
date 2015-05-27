//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneSpace.h"

//=================================
// the actual class

ModuleSceneIntro::ModuleSceneIntro(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	intro = NULL;
	numbers = NULL;
	fx = 0;

	// from numbers_coins animation
	numbers_coins.frames.pushBack({ 0, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 8, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 16, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 24, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 32, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 40, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 48, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 56, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 64, 0, 8, 7 });
	numbers_coins.frames.pushBack({ 72, 0, 8, 7 });
	numbers_coins.speed = 0.0f;
	numbers_coins.loop = false;

	press_space_glow.frames.pushBack({ 0, 0, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 8, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 16, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 24, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 32, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 40, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 48, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 56, 160, 7 });
	press_space_glow.frames.pushBack({ 0, 0, 160, 7 });
	press_space_glow.speed = 0.15f;
	press_space_glow.loop = true;
}

ModuleSceneIntro::~ModuleSceneIntro()
{ }

// Load assets
bool ModuleSceneIntro::start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	app->input->keyboard_enabled = true;

	intro = app->textures->load("Images/Intro_tuned2.png");
	numbers = app->textures->load("Sprites/numbers_blue.png");
	press_space_to_start = app->textures->load("Images/Press_space_to_start_black.png");

	app->audio->playMusic("Music/Intro.ogg", 0.0f);
	fx = app->audio->loadFx("Sounds/Coin.ogg");

	app->renderer->camera.x = app->renderer->camera.y = 0;
	numbers_coins.current_frame = app->coins;

	//DTM ANIMATION
	ticks = 0;
	seconds = 0;

	rects[10] = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE }; // full screen rect

	for (unsigned int i = 0; i < 6; i++)
	{
		rects[i] = { 420 * SCREEN_SIZE, 76 * SCREEN_SIZE, 56 * SCREEN_SIZE, 56 * SCREEN_SIZE };
	}
	source_rects[0] = { 9, 3, 74, 75 };
	source_rects[1] = { 92, 27, 70, 75 };
	source_rects[2] = { 153, 3, 74, 75 };
	source_rects[3] = { 227, 3, 87, 75 };
	source_rects[4] = { 314, 3, 82, 75 };
	source_rects[5] = { 396, 3, 65, 75 };

	//rects[0] = { 0, 0, 0, 0 }; //

	title = app->textures->load("Images/rtype_logo.png");

	return ret;
}

// Delete assets
bool ModuleSceneIntro::cleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->unload(intro);
	app->textures->unload(numbers);
	app->textures->unload(press_space_to_start);
	app->textures->unload(title);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::update()
{
	//// start animation
	//if (ticks < 216) //420)
	//{
	//	if (ticks < 80) // move letters to the left
	//	{
	//		for (unsigned int i = 7; i > 0; i--)
	//		{
	//			rects[i - 1].x -= 5 * SCREEN_SIZE;

	//			SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
	//		}
	//	}

	//	else if (ticks < 100) // small pause
	//	{
	//		for (unsigned int i = 7; i > 0; i--)
	//		{
	//			SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
	//		}
	//	}

	//	else if (ticks < 156) // move letters to the right
	//	{
	//		for (unsigned int i = 7; i > 0; i--)
	//		{
	//			rects[i - 1].x += (i - 1)  * SCREEN_SIZE;

	//			SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
	//		}
	//	}
	//	else if (ticks < 216) // move letters to the right
	//	{
	//		for (unsigned int i = 7; i > 0; i--)
	//		{
	//			rects[i - 1].y += SCREEN_SIZE;

	//			SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
	//		}
	//	}



	//	// update ticks counter
	//	ticks++;
	//}

	//else
	//{
		// Draw everything
		app->renderer->blit(intro, 0 * SCALE_FACTOR, 0 * SCALE_FACTOR, NULL);
		if (app->coins > 0)
			app->renderer->blit(press_space_to_start, 200 * SCALE_FACTOR, 97 * SCALE_FACTOR, &(press_space_glow.getCurrentFrame()));

		// Coins visualization
		unsigned int units = app->coins % 10;
		numbers_coins.current_frame = units;
		app->renderer->blit(numbers, 348 * SCALE_FACTOR, 113 * SCALE_FACTOR, &(numbers_coins.getCurrentFrame()));

		unsigned int tens = (app->coins / 10) % 100;
		numbers_coins.current_frame = tens;
		app->renderer->blit(numbers, 340 * SCALE_FACTOR, 113 * SCALE_FACTOR, &(numbers_coins.getCurrentFrame()));


		if (app->input->keyboard_enabled == true)
		{
			if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP && app->coins > 0)
			{
				app->input->keyboard_enabled = false;
				app->coins--;
				app->fade->fadeToBlack(this, app->scene, 3.0f);

			}
			if (app->input->getKey(SDL_SCANCODE_C) == KEY_UP && app->coins < 99)
			{
				app->audio->playFx(fx);
				app->coins++;
				numbers_coins.current_frame = app->coins;
			}
		}
	//}
	return UPDATE_CONTINUE;
}

