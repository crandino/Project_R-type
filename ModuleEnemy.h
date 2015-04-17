//=================================
// include guard
#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__
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

struct Enemy
{
	SDL_Texture *graphics;
	Point2d<int> position;
	Point2d<int> speed;
	Animation anim;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	unsigned int fx;

	Enemy();
	Enemy(const Enemy &e);
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

	void addEnemy(const Enemy &e, int x, int y, Uint32 delay = 0);	
};

#endif //!__MODULEENEMY_H__ 