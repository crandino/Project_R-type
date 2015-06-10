//=================================
// include guard
#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__
//=================================
// forward declared dependencies
class Weapons;
class Explosions;
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"
#include "ModuleCollision.h"
//=================================
// the actual class

enum WEAPON_TYPES
{
	NONE_WEAPON,

	BASIC_PLAYER_SHOT,
	RIBBON_PLAYER_SHOT,
	MISSILE_PLAYER_SHOT,
	BASIC_ENEMY_SHOT,
	BOSS_WEAPON
	
};

enum EXPLOSION_TYPES
{
	NONE_EXPLOSION,

	COMMON_EXPLOSION,
	HUGE_EXPLOSION,
	PLAYER_EXPLOSION,
	BASIC_PLAYER_SHOT_EXPLOSION
};

class ModuleParticles : public Module
{

private:

	SDL_Texture *basic_player_shot;
	SDL_Texture *missile_player_shot;
	SDL_Texture *basic_enemy_shot;
	SDL_Texture *ribbon_player_shot;
	SDL_Texture *boss_weapon;

	SDL_Texture *basic_player_shot_explosion;
	SDL_Texture *player_explosion;
	SDL_Texture *common_explosion;
	SDL_Texture *huge_explosion;

	DList<Explosions*> active_explosions;

public:
	
	DList<Weapons*> active_weapons;
	unsigned int fx_shot_explosion;

	ModuleParticles(Application *app, bool start_enabled = true);
	~ModuleParticles();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

	void addWeapon(WEAPON_TYPES type , int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void addExplosion(EXPLOSION_TYPES type, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
};

#endif //!__MODULEPARTICLES_H__