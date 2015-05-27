//=================================
// include guard
#ifndef __BASICPLAYERSHOT_H__
#define __BASICPLAYERSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
//=================================
// the actual class

class BasicPlayerShot : public Weapons
{

public:

	BasicPlayerShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		//Player ship shot
		//shot.fx = app->audio->loadFx("LOQUESEA");
		graphics = texture;
		anim.frames.pushBack({ 215, 85, 14, 12 });
		anim.frames.pushBack({ 233, 85, 11, 12 });
		anim.frames.pushBack({ 249, 85, 15, 12 });
		anim.loop = false;
		anim.speed = 0.5f;
		speed.x = 10 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 750;
		type = BASIC_PLAYER_SHOT;
	}

	~BasicPlayerShot()
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