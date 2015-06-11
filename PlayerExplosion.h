//=================================
// include guard
#ifndef __PLAYER_EXPLOSION_H__
#define __PLAYER_EXPLOSION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class PlayerExplosion : public Explosions
{

public:

	PlayerExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		// explosion animation
		graphics = texture;
		anim.frames.pushBack({ 1, 343, 32, 28 });
		anim.frames.pushBack({ 35, 343, 32, 28 });
		anim.frames.pushBack({ 68, 343, 32, 28 });
		anim.frames.pushBack({ 101, 343, 32, 28 });
		anim.frames.pushBack({ 134, 343, 32, 28 });
		anim.frames.pushBack({ 167, 343, 32, 28 });
		anim.frames.pushBack({ 233, 343, 32, 28 });
		anim.speed = 0.4f;
		anim.loop = false;
		current_animation = &anim;
		type = PLAYER_EXPLOSION;
	}

	~PlayerExplosion()
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
			SDL_Rect r = current_animation->peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__RIBBONPOWERUP_H__