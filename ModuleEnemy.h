//=================================
// include guard
#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__
//=================================
// forward declared dependencies
class PataEnemy;
class Enemy;
//=================================
// included dependencies
#include "Module.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"

//=================================
// the actual class

enum enemy_types
{
	PATA_ENEMY,
	BUG_ENEMY
};

class ModuleEnemy : public Module
{

private:

	DList<Enemy*> active;
	
public:

	// List of enemy textures
	// Level 1
	SDL_Texture *pata_graphics;
	SDL_Texture *bug_graphics;

	// Level 2

	ModuleEnemy(Application *app, bool start_enabled = true);
	~ModuleEnemy();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);
	
	void addEnemy(enemy_types type, SDL_Texture *texture, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

};

#endif //!__MODULEENEMY_H__ 