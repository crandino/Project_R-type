//=================================
// include guard
#ifndef __MODULEPOWERUP_H__
#define __MODULEPOWERUP_H__
//=================================
// forward declared dependencies
class RibbonPowerUp;
class PowerUp;
//=================================
// included dependencies
#include "Module.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"

//=================================
// the actual class

enum powerup_types
{
	RIBBON_POWERUP
};

class ModulePowerUp : public Module
{

private:

	DList<PowerUp*> active;

public:

	// List of PowerUp textures
	SDL_Texture *ribbon_graphics;


	ModulePowerUp(Application *app, bool start_enabled = true);
	~ModulePowerUp();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

	void addPowerUp(powerup_types type, SDL_Texture *texture, float x, float y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

};

#endif //!__MODULEPOWERUP_H__