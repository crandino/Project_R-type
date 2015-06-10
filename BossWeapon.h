//=================================
// include guard
#ifndef __BOSSWEAPON_H__
#define __BOSSWEAPON_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
#include <math.h>
//=================================
// the actual class

enum DIRECTION
{
	NONE,

	UP,
	DOWN,
	STRAIGHT
};


class BossWeapon : public Weapons
{
public:

	bool dir_set;
	INT32 dir_delay;

	BossWeapon(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		// Ray weapon of Dobkeratops
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 21, 20 });
		anim.frames.pushBack({ 23, 0, 21, 20 });
		anim.frames.pushBack({ 47, 0, 21, 20 });
		anim.frames.pushBack({ 71, 0, 21, 20 });		
		anim.speed = 0.2f;
		speed.x = -3 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 2000;

		type = BOSS_WEAPON;
		dir = NONE;
		dir_set = false;
		dir_delay = 650;
	}

	~BossWeapon()
	{ }

	bool update()
	{
		bool ret = true;

		if (SDL_GetTicks() > born)
		{
			int max_speed = 90;
			float speed_incr = 1.2f;

			if (SDL_GetTicks() - born > dir_delay)
			{
				if (dir == UP)
				{
					if (speed.y > -max_speed)
						speed.y *= speed_incr;
					else
						speed.y = -max_speed;
				}

				if (dir == DOWN)
				{
					if (speed.y < max_speed)
						speed.y *= speed_incr;
					else
						speed.y = max_speed;
				}		
				position.y += speed.y;
			}
 			position.x += speed.x;

			if (dir == NONE && SDL_GetTicks() - born > dir_delay)
			{
				if (app->player->position.y < position.y - 25 * SCALE_FACTOR)
				{
					dir = UP;
					speed.y = -0.05f * SCALE_FACTOR;
				}
				else if (app->player->position.y > position.y + 25 * SCALE_FACTOR)
				{
					dir = DOWN;
					speed.y = 0.05f * SCALE_FACTOR;
				}
				else
				{
					dir = STRAIGHT;
				}

				doubleNode<Weapons*> *item_weapon = app->particles->active_weapons.getFirst();
				while (item_weapon != NULL)
				{
					if (item_weapon->data->type == BOSS_WEAPON)
					{
						item_weapon->data->dir = dir;
						item_weapon->data->speed.y = speed.y;
					}
					item_weapon = item_weapon->next;
				}
			}
		}

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__BOSSWEAPON_H__