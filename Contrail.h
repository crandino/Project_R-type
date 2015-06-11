//=================================
// include guard
#ifndef __CONTRAIL_H__
#define __CONTRAIL_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Explosions.h"
#include "Application.h"
#include "ModuleSceneSpace.h"
//=================================
// the actual class

class Contrail : public Explosions
{

public:

	Contrail(Application *app, SDL_Texture *texture) : Explosions(app)
	{
		// explosion animation
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 16, 16 });
		anim.frames.pushBack({ 16, 0, 22, 16 });
		anim.frames.pushBack({ 38, 0, 29, 16 });
		anim.frames.pushBack({ 67, 0, 23, 16 });
		anim.speed = 0.4f;
		anim.loop = false;
		current_animation = &anim;

		speed.x = app->scene->scroll_speed;
		type = CONTRAIL;
	}

	~Contrail()
	{ }

	bool update()
	{
		bool ret = true;

		if (anim.finished())
			ret = false;

		position.x += speed.x;
		position.y += speed.y;

		return ret;
	}

};

#endif //!__CONTRAIL_H__