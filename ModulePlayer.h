//=================================
// include guard
#ifndef __MODULEPOINT2D_H__
#define __MODULEPOINT2D_H__
//=================================
// forward declared dependencies
enum WEAPON_TYPES;
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "Point2d.h"
//=================================
// the actual class

class ModulePlayer : public Module
{
public:

	// Texture and animations
	SDL_Texture *graphics;
	Animation *current_animation;
	Animation idle;
	Animation idle_to_upward;
	Animation upward_to_idle;
	Animation idle_to_downward;
	Animation downward_to_idle;
	Animation explosion;
	Animation charging_animation;
	DynArray<Animation*> animation_set;

	// Sounds
	unsigned int fx_charging;

	//Properties
	Point2d<int> position;
	Collider *collider;
	int speed;
	bool active;
	WEAPON_TYPES weapon_type;	
	unsigned int lifes;
	unsigned int player_points;

	// Weapon related
	Uint32 start_charging;
	Uint32 actual_charging;
	Uint32 end_charging;
	Uint32 last_ribbon_shot;
	Uint32 first_sound_moment;
	Uint32 charging_sound_duration;
	bool charged_shot;
	bool charging;
	bool first_charging_sound_played;


	ModulePlayer(Application *app, bool start_enabled = true);
	~ModulePlayer();

	bool start();
	update_status update();
	void shoot();
	void charge_basic_shot();
	void move();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

};

#endif // !__MODULEPOINT2D_H__