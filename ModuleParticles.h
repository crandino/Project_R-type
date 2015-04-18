//=================================
// include guard
#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "ModuleCollision.h" 
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"
//=================================
// the actual class

struct Particle
{
	Animation anim;
	SDL_Texture *graphics;
	Collider *collider;
	unsigned int fx;
	Point2d<int> position;
	Point2d<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;

	Particle();
	Particle(const Particle &p);
	~Particle();
	bool update();
};

class ModuleParticles : public Module
{

private:

	SDL_Texture *graphics;
	DList<Particle*> active;

public:

	//Elements
	Particle shot;

	ModuleParticles(Application *app, bool start_enabled = true);
	~ModuleParticles();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

	void addParticle(const Particle &particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
};

#endif //!__MODULEPARTICLES_H__