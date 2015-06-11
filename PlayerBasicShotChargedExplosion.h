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

class PlayerBasicShotChargedExplosion : public Explosions
{

public:

	PlayerBasicShotChargedExplosion(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		//Explosion animation
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 56, 48 });
		anim.frames.pushBack({ 56, 0, 56, 48 });
		anim.frames.pushBack({ 112, 0, 56, 48 });
		anim.frames.pushBack({ 168, 0, 56, 48 });
		anim.frames.pushBack({ 224, 0, 56, 48 });
		anim.speed = 0.4f;
		anim.loop = false;
		current_animation = &anim;
		type = CHARGED_EXPLOSION;
	}

	~PlayerBasicShotChargedExplosion()
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