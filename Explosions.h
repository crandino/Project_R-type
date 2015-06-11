//=================================
// include guard
#ifndef __EXPLOSIONS_H__
#define __EXPLOSIONS_H__
//=================================
// forward declared dependencies
class ModuleCollision;
enum EXPLOSION_TYPES;
//=================================
// included dependencies
#include "ModuleParticles.h"
//=================================
// the actual class

class Explosions
{

public:

	Application *app;

	SDL_Texture *graphics;
	Point2d<int> position;
	Point2d<int> speed;
	Animation anim;
	Animation *current_animation;
	Uint32 born;
	Uint32 life;
	Collider *collider;
	bool fx_played;
	EXPLOSION_TYPES type;
	unsigned int fx;

	Explosions(Application *parent) 
	{
		graphics = NULL;
		app = parent;
		born = 0;
		life = 0;
		collider = NULL;
		type = NONE_EXPLOSION;
		position.setZero();
		speed.setZero();
	}

	virtual ~Explosions()
	{
		if (collider)
			collider->to_delete = true;
	}

	virtual bool update() { return true; }

};

#endif //!__POWERUP_H__