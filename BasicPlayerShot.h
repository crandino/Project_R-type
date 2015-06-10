//=================================
// include guard
#ifndef __BASICPLAYERSHOT_H__
#define __BASICPLAYERSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
//=================================
// the actual class

class BasicPlayerShot : public Weapons
{

public:
	Animation anim_1;
	Animation anim_2;
	Animation anim_3;
	Animation anim_4;
	Animation anim_5;

	BasicPlayerShot(Application *app, SDL_Texture *texture) : Weapons(app)
	{
		//Player ship shot
		graphics = texture;
		switch (chooseShot())
		{
		case(0) :
			anim.frames.pushBack({ 215, 85, 14, 12 });
			anim.frames.pushBack({ 233, 85, 11, 12 });
			anim.frames.pushBack({ 249, 85, 15, 12 });
			break;
		case(1) :
			anim_1.frames.pushBack({ 232, 103, 16, 12 });
			anim_1.frames.pushBack({ 249, 103, 16, 8 });
			break;
		case(2) :
			anim_2.frames.pushBack({ 200, 121, 32, 10 });
			anim_2.frames.pushBack({ 233, 121, 32, 12 });
			break;
		case(3) :
			anim_3.frames.pushBack({ 168, 137, 48, 12 });
			anim_3.frames.pushBack({ 217, 137, 48, 14 });
			break;
		case(4) :
			anim_4.frames.pushBack({ 136, 154, 64, 14 });
			anim_4.frames.pushBack({ 201, 154, 64, 14 });
			break;
		case(5) :
			anim_5.frames.pushBack({ 104, 171, 80, 14 });
			anim_5.frames.pushBack({ 185, 171, 80, 16 });
			break;
		}
		
		anim.loop = false;
		anim_1.loop = anim_2.loop = anim_3.loop = anim_4.loop = anim_5.loop = true;
		anim.speed = anim_1.speed = anim_2.speed = anim_3.speed = anim_4.speed = anim_5.speed = 0.5f;
		speed.x = 10 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 750;
		type = BASIC_PLAYER_SHOT;
	}

	~BasicPlayerShot()
	{ }

	unsigned int chooseShot()
	{
		unsigned int force_shot = 0;
		Uint32 interval = (app->player->end_charging - app->player->start_charging);

		if (interval < 200)
		{
			current_animation = &anim;
			force_shot = 0;
		}
		else if (interval < 400)
		{
			current_animation = &anim_1;
			force_shot = 1;
		}
		else if (interval < 600)
		{
			current_animation = &anim_2;
			force_shot = 2;
		}
		else if (interval < 800)
		{
			current_animation = &anim_3;
			force_shot = 3;
		}
		else if (interval < 1000)
		{
			current_animation = &anim_4;
			force_shot = 4;
		}
		else
		{
			current_animation = &anim_5;
			force_shot = 5;
		}

		return force_shot;
	}

	bool update()
	{
		bool ret = true;

		if (life > 0)
		{
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (current_animation->finished())
				ret = false;

		position.x += speed.x;
		position.y += speed.y;

		if (collider != NULL)
		{
			SDL_Rect r = current_animation->peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__RIBBONPOWERUP_H__