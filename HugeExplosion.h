//=================================
// include guard
#ifndef __HUGE_EXPLOSION_H__
#define __HUGE_EXPLOSION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class HugeExplosion : public Explosions
{

public:

	HugeExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Common explosion
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 64, 64 });
		anim.frames.pushBack({ 64, 0, 64, 64 });
		anim.frames.pushBack({ 128, 0, 64, 64 });
		anim.frames.pushBack({ 192, 0, 64, 64 });
		anim.frames.pushBack({ 256, 0, 64, 64 });
		anim.frames.pushBack({ 320, 0, 64, 64 });
		anim.frames.pushBack({ 384, 0, 64, 64 });
		anim.frames.pushBack({ 448, 0, 64, 64 });
		anim.frames.pushBack({ 512, 0, 64, 64 });
		anim.frames.pushBack({ 576, 0, 64, 64 });
		anim.speed = 0.4f;
		anim.loop = false;
		type = HUGE_EXPLOSION;
	}

	~HugeExplosion()
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

#endif //!__HUGEEXPLOSION_H__