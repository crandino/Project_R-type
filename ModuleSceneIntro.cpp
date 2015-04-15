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
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{ }

// Load assets
bool ModuleSceneIntro::start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	graphics = app->textures->load("Images/rtype_intro.png");
	app->audio->playMusic("Music/Intro.ogg", 0.0f);
	fx = app->audio->loadFx("Sounds/Coin.ogg");
	app->renderer->camera.x = app->renderer->camera.y = 0;

	return ret;
}

// Delete assets
bool ModuleSceneIntro::cleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0, 0, NULL);

	if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		app->audio->playFx(fx);
		app->fade->fadeToBlack(this, app->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}

