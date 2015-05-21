//= == == == == == == == == == == == == == == == ==
// include guard
#ifndef __BLASTERENEMY_H__
#define __BLASTERENEMY_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Enemy.h"
//=================================
// the actual class

class BlasterEnemy : public Enemy
{

private:

	float angle;

public:

	BlasterEnemy(Application *app, SDL_Texture *texture) : Enemy(app)
	{
		//Bug frames
		anim.frames.pushBack({ 86, 19, 17, 15 });
		anim.frames.pushBack({ 69, 19, 17, 15 });
		anim.frames.pushBack({ 52, 19, 17, 15 });
		anim.frames.pushBack({ 35, 19, 17, 15 });
		anim.frames.pushBack({ 18, 19, 17, 15 });
		anim.frames.pushBack({ 1, 19, 17, 15 });
		anim.frames.pushBack({ 18, 2, 17, 15 });
		anim.frames.pushBack({ 35, 2, 17, 15 });
		anim.frames.pushBack({ 52, 2, 17, 15 });
		anim.frames.pushBack({ 69, 2, 17, 15 });
		anim.frames.pushBack({ 86, 2, 17, 15 });
		anim.speed = 0.0f;
		angle = 0;
		life = 50000; // In miliseconds
		graphics = texture;
	}

	~BlasterEnemy()
	{ }

	void orientTo(const Point2d<int> &position_destiny)
	{
		// https://www.mathsisfun.com/geometry/unit-circle.html
		// It might be helpul!

		float dx = position_destiny.x - position.x;
		float dy = position_destiny.y - position.y;

		//LOG("%d %d", position_destiny.x - position.x, position_destiny.y - position.y);		

		angle = atan(dy / dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}
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
		{
			if (anim.finished())
				ret = false;
		}

		orientTo(app->player->position);

		if (position.y < SCREEN_HEIGHT * SCALE_FACTOR)
		{
			if (angle > 180.0f && angle <= 270.0f)
				anim.current_frame = 6;
			else if (angle <= 365.9f && angle > 270.0f)
				anim.current_frame = 0;
			else
				anim.current_frame = (int)(angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements()));
		}
		else
		{
			if (angle < 180.0f && angle >= 90.0f)
				anim.current_frame = 7;
			else if (angle > 0.0f && angle < 90.0f)
				anim.current_frame = 12;
			else
				anim.current_frame = (int)((angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements())) + 6) ;
		}

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__BLASTERENEMY_H__