//=================================
// include guard
#ifndef __BOSSHIT_H__
#define __BOSSHIT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class BossHit : public Explosions
{

public:

	BossHit(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Hit animation
		graphics = texture;
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 189, 2, 155, 204 });
		anim.frames.pushBack({ 27, 2, 155, 204 });
		anim.frames.pushBack({ 189, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.frames.pushBack({ 351, 2, 155, 204 });
		anim.speed = 2.0f;
		anim.loop = false;
		current_animation = &anim;

		type = HUGE_EXPLOSION;
	}

	~BossHit()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__BOSSHIT_H__