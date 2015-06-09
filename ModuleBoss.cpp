//=================================
// included dependencies
#include "Application.h"
#include "ModuleBoss.h"
#include "ModuleInput.h"
//=================================
// the actual code

ModuleBoss::ModuleBoss(Application *app, bool start_enabled) :
Module(app, start_enabled)
{ }

ModuleBoss::~ModuleBoss()
{ }

bool ModuleBoss::start()
{ 
	enable();
	return true;
}
//
//bool ModuleBoss::cleanUp()
//{ }
//
update_status ModuleBoss::update()
{ 
	LOG("YEAH");
	return UPDATE_CONTINUE;
}
//
//void ModuleBoss::onCollision(Collider *col1, Collider *col2)
//{ }