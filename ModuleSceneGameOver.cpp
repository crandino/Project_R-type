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

	// from countdown animation
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
	countdown.speed = 0.015f;
	//countdown.speed = 0.15f;
	countdown.loop = false;
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
	app->audio->playMusic("Sounds/CountdownMusic.wav", 1.0f);
	app->renderer->camera.x = app->renderer->camera.y = 0;
	countdown.reset();
	return ret;
}

// Delete assets
bool ModuleSceneGameOver::cleanUp()
{
	LOG("Unloading GameOver scene");

	app->textures->unload(graphics);
	app->textures->unload(sprite);

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0.f, 0.f, NULL);
	app->renderer->blit(sprite, 170.f, 100.f, &(countdown.getCurrentFrame()));

	if (app->input->getKey(SDL_SCANCODE_C) == KEY_UP)
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
			app->fade->fadeToBlack(this, app->scene_intro, 3.0f);
		}
	}

	return UPDATE_CONTINUE;
}