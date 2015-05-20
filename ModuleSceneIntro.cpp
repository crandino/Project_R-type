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
	graphics = NULL;
	sprite = NULL;
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
	numbers_coins.speed = 0.f;
	numbers_coins.loop = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{ }

// Load assets
bool ModuleSceneIntro::start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	app->input->keyboard_enabled = true;

	graphics = app->textures->load("Images/rtype_intro.png");
	sprite = app->textures->load("Sprites/numbers_blue.png");
	app->audio->playMusic("Music/Intro.ogg", 0.0f);
	fx = app->audio->loadFx("Sounds/Coin.ogg");
	app->renderer->camera.x = app->renderer->camera.y = 0;
	numbers_coins.current_frame = app->coins;

	return ret;
}

// Delete assets
bool ModuleSceneIntro::cleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->unload(graphics);
	app->textures->unload(sprite);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0.f, 0.f, NULL);

	app->renderer->blit(sprite, 344.f, 113.f, &(numbers_coins.getCurrentFrame()));

if (app->input->keyboard_enabled == true)
{
	if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP && app->coins > 0)
	{
		app->input->keyboard_enabled = false;
		app->coins--;
		app->fade->fadeToBlack(this, app->scene, 3.0f);
		
	}
	if (app->input->getKey(SDL_SCANCODE_C) == KEY_UP)
	{
		app->audio->playFx(fx);
		app->coins++;
		numbers_coins.current_frame = app->coins;
	}
}

	return UPDATE_CONTINUE;
}

