//=================================
// include guard
#ifndef __PLAYER_MISSILE_SHOT_EXPLOSION_H__
#define __PLAYER_MISSILE_SHOT_EXPLOSION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
//=================================
// the actual class

class PlayerMissileShotExplosion : public Explosions
{

public:

	PlayerMissileShotExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Basic player shot explosion
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 18, 30 });
		anim.frames.pushBack({ 18, 0, 27, 30 });
		anim.frames.pushBack({ 45, 0, 32, 30 });
		anim.frames.pushBack({ 77, 0, 32, 30 });
		anim.frames.pushBack({ 109, 0, 32, 30 });
		anim.frames.pushBack({ 141, 0, 32, 30 });
		anim.speed = 0.3f;
		anim.loop = false;
		current_animation = &anim;
		type = MISSILE_PLAYER_SHOT_EXPLOSION;
	}

	~PlayerMissileShotExplosion()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		return ret;
	}

};

#endif //!__PLAYER_MISSILESHOTEXPLOSION_H__