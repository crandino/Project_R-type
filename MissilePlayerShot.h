// include guard
#ifndef __MISSILEPLAYERSHOT_H__
#define __MISSILEPLAYERSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
//=================================
// the actual class

class MissilePlayerShot : public Weapons
{

public:

	INT32 target_delay;
	bool targeting;

	MissilePlayerShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		//Pata-pata shot
		graphics = texture;
		anim.frames.pushBack({ 108, 12, 12, 12 });
		anim.speed = 0.5f;
		life = 10000;
		target_delay = 2000;
		targeting = false;
		type = MISSILE_PLAYER_SHOT;
		speed.x = 1 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
	}

	~MissilePlayerShot()
	{ }

	/*void orientTo(const Point2d<int> &destiny_position)
	{
		float dx = destiny_position.x - position.x;
		float dy = destiny_position.y - position.y;

		float angle = atan(dy / dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}

		int speed_value = 1.6 * SCALE_FACTOR;

		speed.x = (int)(cos(angle) * speed_value);
		speed.y = (int)(sin(angle) * speed_value);
	}*/

	bool update()
	{
		bool ret = true;

		if (life > 0)
		{
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (anim.finished())
				ret = false;

		if (SDL_GetTicks() - born > target_delay )
			targeting = true;
		
		if (targeting == true)
			speed.x = 10 * SCALE_FACTOR;			

		/*if (oriented == false)
		{
			orientTo(app->player->position);
			oriented = true;
		}*/

		position.x += speed.x;
		position.y += speed.y;

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__MISSILEPLAYERSHOT_H__