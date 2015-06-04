// include guard
#ifndef __BASICENEMYSHOT_H__
#define __BASICENEMYSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
#include <math.h>
//=================================
// the actual class

class BasicEnemyShot : public Weapons
{

public:

	bool oriented;

	BasicEnemyShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		graphics = texture;
		anim.frames.pushBack({ 1, 1, 7, 6 });
		anim.frames.pushBack({ 10, 1, 7, 6 });
		anim.frames.pushBack({ 19, 1, 7, 6 });
		anim.frames.pushBack({ 27, 1, 7, 6 });
		anim.speed = 0.5f;
		life = 8000;
		type = BASIC_ENEMY_SHOT;
		oriented = false;
	}

	~BasicEnemyShot()
	{ }

	void orientTo(const Point2d<int> &destiny_position)
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
	}

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

		if (oriented == false)
		{
			orientTo(app->player->position);
			oriented = true;
		}

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

#endif //!__BASICENEMYSHOT_H__