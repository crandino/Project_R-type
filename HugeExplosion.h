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
		//Explosion animation
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
		current_animation = &anim;

		type = HUGE_EXPLOSION;
	}

	~HugeExplosion()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__HUGEEXPLOSION_H__