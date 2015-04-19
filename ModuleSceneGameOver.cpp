//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneGameOver.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"

//=================================
// the actual class

ModuleSceneGameOver::ModuleSceneGameOver(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	sprite = NULL;
	fx = 0;

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
	countdown.loop = false;
}

ModuleSceneGameOver::~ModuleSceneGameOver()
{ }

// Load assets
bool ModuleSceneGameOver::start()
{
	LOG("Loading GameOver assets");
	bool ret = true;

	graphics = app->textures->load("Images/GameOver.png");
	sprite = app->textures->load("Sprites/Numbers.png");
	//fx = app->audio->loadFx("Sounds/Coin.ogg");
	app->renderer->camera.x = app->renderer->camera.y = 0;

	return ret;
}

// Delete assets
bool ModuleSceneGameOver::cleanUp()
{
	LOG("Unloading GameOver scene");

	app->textures->unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneGameOver::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0, 0, NULL);
	app->renderer->blit(sprite, 170, 100, &(countdown.getCurrentFrame()));

	if (!countdown.finished()){
		app->fade->fadeToBlack(this, app->scene_intro, 3.0f);
	}

	return UPDATE_CONTINUE;
}