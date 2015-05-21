//=================================
// include guard
#ifndef __WEAPONS_H__
#define __WEAPONS_H__
//=================================
// forward declared dependencies
class ModulleCollision;
enum WEAPON_TYPES;
//=================================
// included dependencies
#include "ModuleParticles.h"
//=================================
// the actual class

class Weapons
{

public:

	Application *app;

	SDL_Texture *graphics;
	Point2d<int> position;
	Point2d<int> speed;
	Animation anim;
	Animation* current_animation;
	Uint32 born;
	Uint32 life;
	Collider *collider;
	bool fx_played;
	WEAPON_TYPES type;
	unsigned int fx;

	Weapons(Application *parent) : app(parent), born(0), life(0), collider(NULL)
	{
		type = NONE_WEAPON;
		position.setZero();
		speed.setZero();
	}

	virtual ~Weapons()
	{
		if (collider)
			collider->to_delete = true;
	}

	virtual bool update() { return true; }

};

#endif //!__WEAPONS_H__