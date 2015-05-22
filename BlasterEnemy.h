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
	Uint32 time_to_attack;
	Uint32 attacks;
	Uint32 attack_frequency;

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
		anim.frames.pushBack({ 1, 2, 17, 15 });
		anim.frames.pushBack({ 18, 2, 17, 15 });
		anim.frames.pushBack({ 35, 2, 17, 15 });
		anim.frames.pushBack({ 52, 2, 17, 15 });
		anim.frames.pushBack({ 69, 2, 17, 15 });
		anim.frames.pushBack({ 86, 2, 17, 15 });
		anim.speed = 0.0f;
		angle = 0;
		life = 50000; // In miliseconds
		graphics = texture;

		attacks = 0;
		attack_frequency = attack_frequency = ((rand() % 3) + 3) * 1000;
	
	}

	~BlasterEnemy()
	{ }

	void orientTo(const Point2d<int> &position_destiny)
	{
		// https://www.mathsisfun.com/geometry/unit-circle.html
		// It might be helpul!

		float dx = position_destiny.x - position.x;
		float dy = position_destiny.y - position.y;

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

		if (position.y < (SCREEN_HEIGHT * SCALE_FACTOR) / 2)
		{
			if (angle >= M_PI && angle <= M_PI * 3 / 2)
				anim.current_frame = 5;		
			else if (angle < M_PI * 2 && angle > M_PI * 3 / 2)
				anim.current_frame = 0;
			else
				anim.current_frame = (int)(angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements()));
		}
		else
		{
			if (angle <= M_PI && angle >= M_PI / 2)
				anim.current_frame = 6;
			else if (angle >= 0.0f && angle < M_PI / 2)
				anim.current_frame = 11;
			else
				anim.current_frame = (int)(angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements()));
		}

		time_to_attack = (SDL_GetTicks() - born) - (attacks * attack_frequency);
		if (SDL_TICKS_PASSED(time_to_attack, attack_frequency) == true)
		{
			app->particles->addWeapon(PATA_SHOT, position.x + 4 * SCALE_FACTOR, position.y, COLLIDER_ENEMY_SHOT);
			attacks++;
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