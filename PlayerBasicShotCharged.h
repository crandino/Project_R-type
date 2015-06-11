//=================================
// include guard
#ifndef __PLAYER_BASIC_SHOT_CHARGED_H__
#define __PLAYER_BASIC_SHOT_CHARGED_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class PlayerBasicShotCharged : public Explosions
{

public:

	PlayerBasicShotCharged(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Basic player shot explosion
		graphics = texture;
		anim.frames.pushBack({ 2, 13, 24, 22 });
		anim.frames.pushBack({ 27, 10, 34, 28 });
		anim.frames.pushBack({ 61, 7, 42, 34 });
		anim.frames.pushBack({ 104, 3, 48, 42 });
		anim.frames.pushBack({ 154, 0, 56, 48 });
		anim.speed = 0.4f;
		anim.loop = false;
		current_animation = &anim;
		type = CHARGED_EXPLOSION;
	}

	~PlayerBasicShotCharged()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__PLAYERBASICSHOTCHARGED_H__