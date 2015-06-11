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

	CHARGED_EXPLOSION,
	COMMON_EXPLOSION,
	HUGE_EXPLOSION,
	PLAYER_EXPLOSION,
	CONTRAIL,
	BASIC_PLAYER_SHOT_EXPLOSION,
	MISSILE_PLAYER_SHOT_EXPLOSION,
	BOSS_HIT
};

class ModuleParticles : public Module
{

private:

	//Texture shots
	SDL_Texture *basic_player_shot;
	SDL_Texture *missile_player_shot;
	SDL_Texture *missile_propulsion;
	SDL_Texture *basic_enemy_shot;
	SDL_Texture *ribbon_player_shot;
	SDL_Texture *boss_weapon;

	//Texture explosions
	SDL_Texture *basic_player_shot_explosion;
	SDL_Texture *missile_player_shot_explosion;
	SDL_Texture *player_explosion;
	SDL_Texture *contrail;
	SDL_Texture *common_explosion;
	SDL_Texture *huge_explosion;
	SDL_Texture *charged_explosion;
	SDL_Texture *boss_hit;

	DList<Explosions*> active_explosions;

public:
	
	DList<Weapons*> active_weapons;
	unsigned int fx_shot_explosion;
	Uint32 last_ribbon_shot;
	Uint32 last_missile_shot;
	Uint32 ribbon_delay;
	Uint32 missile_delay;
	UINT32 missile_counter;


	ModuleParticles(Application *app, bool start_enabled = true);
	~ModuleParticles();

	bool start();
	update_status update();
	update_status postUpdate();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

	void addWeapon(WEAPON_TYPES type , int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void addExplosion(EXPLOSION_TYPES type, int x, int y, Uint32 delay = 0);
};

#endif //!__MODULEPARTICLES_H__