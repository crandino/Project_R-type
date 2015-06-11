//=================================
// include guard
#ifndef __BASICPOWERUP_H__
#define __BASICPOWERUP_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "PowerUp.h"
#include <math.h>
//=================================
// the actual class

class BasicPowerUp : public PowerUp
{

public:

	BasicPowerUp(Application *app, SDL_Texture *texture) : PowerUp(app)
	{
		//Animation frames
		anim.frames.pushBack({ 0, 0, 20, 18 });
		anim.frames.pushBack({ 20, 0, 20, 18 });
		anim.frames.pushBack({ 40, 0, 20, 18 });
		anim.frames.pushBack({ 60, 0, 20, 18 });
		anim.frames.pushBack({ 80, 0, 20, 18 });
		anim.frames.pushBack({ 60, 0, 20, 18 });
		anim.frames.pushBack({ 40, 0, 20, 18 });
		anim.frames.pushBack({ 20, 0, 20, 18 });
		anim.speed = 0.1f;
		speed.x = 0 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 100000; // In miliseconds
		graphics = texture;
		type = BASIC_POWERUP;
	}

	~BasicPowerUp()
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

#endif //!__BASICPOWERUP_H__