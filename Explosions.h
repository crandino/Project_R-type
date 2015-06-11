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
	bool fx_played;
	EXPLOSION_TYPES type;
	unsigned int fx;

	Explosions(Application *parent) 
	{
		graphics = NULL;
		app = parent;
		born = 0;
		type = NONE_EXPLOSION;
		position.setZero();
		speed.setZero();
	}

	virtual ~Explosions()
	{ }

	virtual bool update() { return true; }

};

#endif //!__POWERUP_H__