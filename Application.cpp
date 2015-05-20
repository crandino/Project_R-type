//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleInterface.h"
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModulePowerUp.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneWin.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
//=================================
// the actual class

Application::Application()
{
	window = new ModuleWindow(this);
	renderer = new ModuleRender(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	game_interface = new ModuleInterface(this, false);
	scene = new ModuleSceneSpace(this, false);
	player = new ModulePlayer(this, false);
	enemy = new ModuleEnemy(this, false);
	powerup = new ModulePowerUp(this, false);
	scene_intro = new ModuleSceneIntro(this, true);
	scene_over = new ModuleSceneGameOver(this, false);
	scene_win = new ModuleSceneWin(this, false);
	particles = new ModuleParticles(this, false);
	collision = new ModuleCollision(this, false);
	fade = new ModuleFadeToBlack(this);

	// Main modules
	addModule(window);
	addModule(renderer);
	addModule(textures);
	addModule(input);
	addModule(audio);

	addModule(game_interface);

	// Scenes
	addModule(scene_intro);
	addModule(scene);
	addModule(scene_over);
	addModule(scene_win);

	// Collisions
	addModule(collision);

	// Characters
	addModule(player);
	addModule(enemy);
	addModule(powerup);

	// Miscellaneous
	addModule(particles);
	addModule(fade);
}

Application::~Application()
{
	delete window;
	delete renderer;
	delete textures;
	delete input;
	delete audio;
	delete game_interface;
	delete scene;
	delete player;
	delete enemy;
	delete powerup;
	delete scene_intro;
	delete scene_over;
	delete scene_win;
	delete particles;
	delete fade;
	delete collision;
}

bool Application::init()
{
	bool ret = true;

	// We call init() for all modules
	doubleNode<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->init();
		item = item->next;
	}

	// After all initialization, we start each module
	LOG("Application Start -----------------");
	item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		if (item->data->isEnabled())
			ret = item->data->start();
		item = item->next;
	}
	
	return ret;
}

// Update is split into 3: preUpdate, update and postUpdate.
update_status Application::update()
{
	update_status ret = UPDATE_CONTINUE;
	doubleNode<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->isEnabled())
			ret = item->data->preUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->isEnabled())
			ret = item->data->update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{ 
		if (item->data->isEnabled())
			ret = item->data->postUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::cleanUp()
{
	bool ret = true;
	doubleNode<Module*>* item = list_modules.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->cleanUp();
		item = item->previous;
	}

	return ret;
}

void Application::addModule(Module *module)
{
	list_modules.add(module);
}