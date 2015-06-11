//=================================
// include guard
#ifndef __MODULECOLLISION_H__
#define __MODULECOLLISION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "DList.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,

	COLLIDER_WALL, 
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,
	COLLIDER_RIBBON_SHOT,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module *callback;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module *callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{ }

	void setPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool checkCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module
{

private:

	DList<Collider*> colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
	bool god_mode;
	SDL_Texture *god;

public:

	ModuleCollision(Application *app, bool start_enabled = true);
	~ModuleCollision();

	bool start();
	update_status preUpdate();
	update_status update();
	bool cleanUp();

	Collider* addCollider(SDL_Rect rect, COLLIDER_TYPE type, bool positions_scaled = true, Module *callback = NULL);
	void drawDebug(Collider *col);
};

#endif //!__MODULECOLLISION_H__