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

enum POWERUP_TYPES
{
	NONE_POWERUP,
	BASIC_POWERUP, 
	RIBBON_POWERUP,
	MISSILE_POWERUP
};

class ModulePowerUp : public Module
{

private:

	DList<PowerUp*> active;

public:

	// List of PowerUp textures
	SDL_Texture *basic_graphics;
	SDL_Texture *ribbon_graphics;
	SDL_Texture *missile_graphics;
	unsigned int fx_power_up;

	ModulePowerUp(Application *app, bool start_enabled = true);
	~ModulePowerUp();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

	void addPowerUp(POWERUP_TYPES type, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);


};

#endif //!__MODULEPOWERUP_H__