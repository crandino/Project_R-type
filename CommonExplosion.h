//=================================
// include guard
#ifndef __COMMON_EXPLOSION_H__
#define __COMMON_EXPLOSION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class CommonExplosion : public Explosions
{

public:

	CommonExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Common explosion
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 34, 32 });
		anim.frames.pushBack({ 34, 0, 34, 32 });
		anim.frames.pushBack({ 68, 0, 34, 32 });
		anim.frames.pushBack({ 102, 0, 34, 32 });
		anim.frames.pushBack({ 136, 0, 34, 32 });
		anim.frames.pushBack({ 170, 0, 34, 32 });
		anim.speed = 0.4f;
		anim.loop = false;
		current_animation = &anim;
		type = COMMON_EXPLOSION;
	}

	~CommonExplosion()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__COMMONEXPLOSION_H__