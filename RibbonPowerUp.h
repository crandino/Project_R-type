//=================================
// include guard
#ifndef __RIBBONPOWERUP_H__
#define __RIBBONPOWERUP_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "PowerUp.h"
#include <math.h>
//=================================
// the actual class

class RibbonPowerUp : public PowerUp
{

public:

	RibbonPowerUp(Application *app, SDL_Texture *texture) : PowerUp(app)
	{
		//Ribbon frames
		anim.frames.pushBack({ 0, 0, 19, 17 });
		anim.frames.pushBack({ 20, 0, 19, 17 });
		anim.frames.pushBack({ 40, 0, 19, 17 });
		anim.frames.pushBack({ 60, 0, 19, 17 });
		anim.frames.pushBack({ 80, 0, 19, 17 });
		anim.speed = 0.1f;
		speed.x = 0 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 28000; // In miliseconds
		graphics = texture;
		powerup_type = RIBBON_POWERUP;
	}

	~RibbonPowerUp()
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

#endif //!__RIBBONPOWERUP_H__