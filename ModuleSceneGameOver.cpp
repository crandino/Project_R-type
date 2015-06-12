//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneSpace.h"

//=================================
// the actual class

ModuleSceneGameOver::ModuleSceneGameOver(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	sprite = NULL;
	numbers = NULL;

	// From countdown animation
	countdown.frames.pushBack({ 0, 0, 48, 71 });
	countdown.frames.pushBack({ 48, 0, 48, 71 });
	countdown.frames.pushBack({ 96, 0, 48, 71 });
	countdown.frames.pushBack({ 144, 0, 48, 71 });
	countdown.frames.pushBack({ 192, 0, 48, 71 });
	countdown.frames.pushBack({ 240, 0, 48, 71 });
	countdown.frames.pushBack({ 288, 0, 48, 71 });
	countdown.frames.pushBack({ 336, 0, 48, 71 });
	countdown.frames.pushBack({ 384, 0, 48, 71 });
	countdown.frames.pushBack({ 432, 0, 48, 71 });
	countdown.speed = 0.014f;
	countdown.loop = false;

	// From numbers_coins animation
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

ModuleSceneGameOver::~ModuleSceneGameOver()
{ }

// Load assets
bool ModuleSceneGameOver::start()
{
	LOG("Loading GameOver assets");
	bool ret = true;

	fade_to_black = false;
	app->input->keyboard_enabled = true;

	graphics = app->textures->load("Images/GameOver.png");
	sprite = app->textures->load("Sprites/Numbers.png");
	numbers = app->textures->load("Sprites/NumbersBlue2.png");
	press_space_to_start = app->textures->load("Images/PressSpaceToStartBlackGameOver.png");

	app->audio->playMusic("Sounds/CountdownMusic.wav", 1.0f);

	app->renderer->camera.x = app->renderer->camera.y = 0;
	numbers_coins.current_frame = app->coins;
	countdown.reset();

	return ret;
}

// Delete assets
bool ModuleSceneGameOver::cleanUp()
{
	LOG("Unloading GameOver scene");

	app->textures->unload(graphics);
	app->textures->unload(sprite);
	app->textures->unload(numbers);
	app->textures->unload(press_space_to_start);

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0 * SCALE_FACTOR, 0 * SCALE_FACTOR, NULL);
	app->renderer->blit(sprite, 170 * SCALE_FACTOR, 100 * SCALE_FACTOR, &(countdown.getCurrentFrame()));
	if (app->coins > 0)
		app->renderer->blit(press_space_to_start, 114 * SCALE_FACTOR, 194 * SCALE_FACTOR, &(press_space_glow.getCurrentFrame()));

	// Coins visualization
	unsigned int units = app->coins % 10;
	numbers_coins.current_frame = units;
	app->renderer->blit(numbers, 248 * SCALE_FACTOR, 217 * SCALE_FACTOR, &(numbers_coins.getCurrentFrame()));

	unsigned int tens = (app->coins / 10) % 100;
	numbers_coins.current_frame = tens;
	app->renderer->blit(numbers, 240 * SCALE_FACTOR, 217 * SCALE_FACTOR, &(numbers_coins.getCurrentFrame()));

	if (app->input->getKey(SDL_SCANCODE_C) == KEY_UP && app->coins < 99)
	{
		app->audio->playFx(app->scene_intro->fx);
		app->coins++;
	}

	if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP && app->coins > 0)
	{
			app->input->keyboard_enabled = false;
			app->coins--;
			app->fade->fadeToBlack(this, app->scene, 3.0f);
	}
	
	if (countdown.finished())
	{
		if (fade_to_black == false)
		{
			fade_to_black = true;
			app->audio->stopAllMusic(1.0f);
			app->fade->fadeToBlack(this, app->scene_intro, 3.0f);
		}
	}

	return UPDATE_CONTINUE;
}