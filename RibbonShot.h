//=================================
// include guard
#ifndef __RIBBONSHOT_H__
#define __RIBBONSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
//=================================
// the actual class

class RibbonShot : public Weapons
{

public:

	Animation second_ribbon_shot;
	Animation* current_animation;

	RibbonShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		//Player ship shot with ribbon power-up
		//shot.fx = app->audio->loadFx("LOQUESEA");
		graphics = texture;
		anim.frames.pushBack({ 0, 0, 12, 56 });
		anim.frames.pushBack({ 12, 0, 18, 56 });
		anim.frames.pushBack({ 30, 0, 27, 56 });
		anim.frames.pushBack({ 57, 0, 37, 56 });
		anim.frames.pushBack({ 94, 0, 47, 56 });
		anim.frames.pushBack({ 141, 0, 55, 56 });
		anim.frames.pushBack({ 196, 0, 61, 56 });
		anim.frames.pushBack({ 257, 0, 64, 56 });
		anim.frames.pushBack({ 321, 0, 70, 56 });
		anim.frames.pushBack({ 391, 0, 81, 56 });
		anim.frames.pushBack({ 472, 0, 87, 56 });
		anim.frames.pushBack({ 559, 0, 92, 56 });
		anim.frames.pushBack({ 651, 0, 98, 56 });
		anim.frames.pushBack({ 749, 0, 101, 56 });
		anim.frames.pushBack({ 850, 0, 112, 56 });
		second_ribbon_shot.frames.pushBack({ 962, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1026, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1090, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1154, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1218, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1282, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1346, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1410, 12, 64, 32 });
		second_ribbon_shot.frames.pushBack({ 1474, 12, 64, 32 });
		anim.loop = false;
		second_ribbon_shot.loop = false;
		anim.speed = 0.5f;
		second_ribbon_shot.speed = 0.5f;
		speed.x = 0.5 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		speed.x = 0.5 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		/*life = 1500;
		second_ribbon_shot.life = 1500;*/
		type = RIBBON_SHOT;
		current_animation = &anim;
	}

	~RibbonShot()
	{ }

	bool update()
	{
		bool ret = true;

		
		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__RIBBONSHOT_H__

/*if (life > 0)
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
}*/