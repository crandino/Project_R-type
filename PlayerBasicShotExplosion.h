//=================================
// include guard
#ifndef __PLAYER_BASIC_SHOT_EXPLOSION_H__
#define __PLAYER_BASIC_SHOT_EXPLOSION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class PlayerBasicShotExplosion : public Explosions
{

public:

	PlayerBasicShotExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Basic player shot explosion
		graphics = texture;
		anim.frames.pushBack({ 0, 3, 11, 11 });
		anim.frames.pushBack({ 12, 2, 14, 13 });
		anim.frames.pushBack({ 25, 0, 16, 16 });
		anim.speed = 0.4f;
		anim.loop = false;
		type = COMMON_EXPLOSION;
	}

	~PlayerBasicShotExplosion()
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

#endif //!__PLAYERBASICSHOTEXPLOSION_H__