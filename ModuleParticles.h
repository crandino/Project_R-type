//=================================
// include guard
#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"
//=================================
// the actual class

struct Particle
{
	Animation anim;
	unsigned int fx;
	Point2d<int> position;
	Point2d<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;

	Particle();
	Particle(const Particle &p);
	bool update();
};

class ModuleParticles : public Module
{

private:

	SDL_Texture *graphics;
	DList<Particle*> active;

public:

	//Particle explosion;
	Particle shot;

	ModuleParticles(Application *app, bool start_enabled = true);
	~ModuleParticles();

	bool start();
	update_status update();
	bool cleanUp();

	void addParticle(const Particle &particle, int x, int y, Uint32 delay = 0);
};

#endif //!__MODULEPARTICLES_H__