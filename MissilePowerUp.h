//=================================
// include guard
#ifndef __MISSILEPOWERUP_H__
#define __MISSILEPOWERUP_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "PowerUp.h"
#include <math.h>
//=================================
// the actual class

class MissilePowerUp : public PowerUp
{

public:

	MissilePowerUp(Application *app, SDL_Texture *texture) : PowerUp(app)
	{
		//Animation frames
		anim.frames.pushBack({ 6, 3, 21, 18 });
		anim.frames.pushBack({ 38, 3, 21, 18 });
		anim.frames.pushBack({ 70, 3, 21, 18 });
		anim.frames.pushBack({ 102, 3, 21, 18 });
		anim.frames.pushBack({ 134, 3, 21, 18 });
		anim.speed = 0.1f;
		speed.x = 0 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 100000; // In miliseconds
		graphics = texture;
		type = MISSILE_POWERUP;
	}

	~MissilePowerUp()
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

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__MISSILEPOWERUP_H__