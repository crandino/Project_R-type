//=================================
// include guard
#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__
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

struct Enemy
{

	SDL_Texture *graphics;
	Point2d<float> position;
	Point2d<float> speed;
	Animation anim;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	unsigned int fx;
	Collider *collider;

	// CRZ
	Uint32 time_to_attack;
	Uint32 attacks;
	Uint32 attack_frequency;
	
	Enemy();
	Enemy(const Enemy &e);
	~Enemy();
	bool update();
};


class ModuleEnemy : public Module
{

private:

	DList<Enemy*> active;

public:

	// List of enemies
	// Level 1
	Enemy pata_pata;

	// Level 2

	ModuleEnemy(Application *app, bool start_enabled = true);
	~ModuleEnemy();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);
	
	void addEnemy(const Enemy &e, float x, float y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);	
};

#endif //!__MODULEENEMY_H__ 