//=================================
// include guard
#ifndef __APPLICATION_H__
#define __APPLICATION_H__
//=================================
// forward declared dependencies
class Module;
class ModuleWindow;
class ModuleRender;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleSceneSpace;
class ModulePlayer;
class ModuleParticles;
class ModuleSceneIntro;
class ModuleFadeToBlack;
//=================================
// included dependencies
#include "DList.h"
#include "Globals.h"
//=================================
// the actual class

class Application
{
private:

	DList<Module*> list_modules;
	void addModule(Module *module);

public:
	
	ModuleWindow *window;
	ModuleRender *renderer;
	ModuleTextures *textures;
	ModuleInput *input;
	ModuleAudio *audio;
	ModuleSceneSpace *scene;
	ModulePlayer *player;
	ModuleFadeToBlack *fade;
	ModuleSceneIntro *scene_intro;
	ModuleParticles *particles;
	
	Application();
	~Application();

	bool init();
	update_status update();
	bool cleanUp();
};

#endif // !__APPLICATION_H__
