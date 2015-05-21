// include guard
#ifndef __PATASHOT_H__
#define __PATASHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
#include <math.h>
//=================================
// the actual class

class PataShot : public Weapons
{

public:

	PataShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		//Pata-pata shot
		graphics = texture;
		anim.frames.pushBack({ 1, 1, 7, 6 });
		anim.frames.pushBack({ 10, 1, 7, 6 });
		anim.frames.pushBack({ 19, 1, 7, 6 });
		anim.frames.pushBack({ 27, 1, 7, 6 });
		anim.speed = 0.5f;
		speed.x = -2 * SCALE_FACTOR;
		life = 4000;
		type = PATA_SHOT;

		float dx = app->player->position.x - position.x;
		float dy = app->player->position.y - position.y;

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

		int speed_value = 1.5 * SCALE_FACTOR;

		speed.x = (int)(cos(angle) * speed_value);
		speed.y = (int)(sin(angle) * speed_value);
	}

	~PataShot()
	{ }

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

#endif //!__RIBBONPOWERUP_H__