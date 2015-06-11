//=================================
// include guard
#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "Point2d.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

struct Boss
{
	Point2d<int> position;
	Animation anim;
	Collider *col;
};

struct Alien : Boss
{
	int life;
	unsigned int points;
	unsigned int dead_time;

	Alien() : Boss()
	{
		anim.frames.pushBack({ 636, 1964, 32, 32 });
		anim.frames.pushBack({ 603, 1964, 32, 32 });
		anim.frames.pushBack({ 570, 1964, 32, 32 });
		anim.frames.pushBack({ 603, 1964, 32, 32 });
		anim.frames.pushBack({ 636, 1964, 32, 32 });
		anim.frames.pushBack({ 636, 1964, 32, 32 });
		anim.frames.pushBack({ 636, 1964, 32, 32 });
		anim.speed = 0.05f;
	}
};

struct Dobkeratops : Boss
{
	Collider *col_dob_head1;
	Collider *col_dob_head2;
	Collider *col_dob_head3;
	Collider *col_dob_body1;
	Collider *col_dob_body2;
	Collider *col_dob_tail;

	Dobkeratops() : Boss()
	{
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 189, 2, 155, 204 });
		anim.frames.pushBack({  27, 2, 155, 204 });
		anim.frames.pushBack({ 189, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.speed = 0.035f;
	}
};

struct Antenna1 : Boss
{
	Antenna1() : Boss()
	{
		anim.frames.pushBack({ 177, 1926, 192, 34 });
		anim.loop = false;
	}
};

struct Antenna2 : Boss
{
	Antenna2() : Boss()
	{
		anim.frames.pushBack({ 265, 1982, 104, 57 });
		anim.loop = false;
	}
};

struct Antenna3 : Boss
{
	Antenna3() : Boss()
	{
		anim.frames.pushBack({ 265, 2054, 104, 36 });
		anim.loop = false;
	}
};

struct Antenna4 : Boss
{
	Antenna4() : Boss()
	{
		anim.frames.pushBack({ 177, 2102, 192, 32 });
		anim.loop = false;
	}
};

class ModuleBoss : public Module
{

public:

	bool wait_to_shoot;

	SDL_Texture *dobkeratops_texture;

	// Parts of Dobkeratops:
	Alien *alien;
	Dobkeratops *dobkeratops;
	Antenna1 *antenna1;
	Antenna2 *antenna2;
	Antenna3 *antenna3;
	Antenna4 *antenna4;

	DList<Boss*> boss_parts;

	unsigned int stop_scrolling_position;
	bool faded;

	ModuleBoss(Application *app, bool start_enabled = true);
	~ModuleBoss();

	bool start();
	update_status update();
	//bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

};

#endif // !__MODULEBOSS_H__