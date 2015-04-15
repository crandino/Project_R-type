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
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleParticles.h"
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
	scene = new ModuleSceneSpace(this, false);
	player = new ModulePlayer(this, false);
	scene_intro = new ModuleSceneIntro(this, true);
	particles = new ModuleParticles(this);
	fade = new ModuleFadeToBlack(this);

	// Main modules
	addModule(window);
	addModule(renderer);
	addModule(textures);
	addModule(input);
	addModule(audio);

	// Scenes
	addModule(scene);
	addModule(scene_intro);

	// Characters
	addModule(player);

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
	delete scene;
	delete player;
	delete scene_intro;
	delete particles;
	delete fade;
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