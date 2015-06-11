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
		current_animation = &anim;
		type = BASIC_PLAYER_SHOT_EXPLOSION;
	}

	~PlayerBasicShotExplosion()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__PLAYERBASICSHOTEXPLOSION_H__