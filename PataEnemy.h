//=================================
// include guard
#ifndef __PATAENEMY_H__
#define __PATAENEMY_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Enemy.h"
#include <math.h>
//=================================
// the actual class

class PataEnemy : public Enemy
{

public:

	// CRZ
	Uint32 time_to_attack;
	Uint32 attacks;
	Uint32 attack_frequency;

	PataEnemy(Application *app, SDL_Texture *texture) : Enemy(app)
	{
		//Pata-pata frames
		anim.frames.pushBack({ 5, 6, 21, 24 });
		anim.frames.pushBack({ 38, 6, 21, 24 });
		anim.frames.pushBack({ 71, 6, 21, 24 });
		anim.frames.pushBack({ 104, 6, 21, 24 });
		anim.frames.pushBack({ 137, 6, 21, 24 });
		anim.frames.pushBack({ 170, 6, 21, 24 });
		anim.frames.pushBack({ 203, 6, 21, 24 });
		anim.frames.pushBack({ 236, 6, 21, 24 });
		anim.speed = 0.3f;
		speed.x = -1 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 12000; // In miliseconds
		attack_frequency = (rand() % 5 + 5) * 1000; // In miliseconds
		attacks = 0;
		graphics = texture;
	}

	~PataEnemy()
	{ }

	bool update()
	{
		bool ret = true;

		if (life > 0)
		{
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (anim.finished())
				ret = false;

		// These variables control the oscillation of Pata.
		int amplitude = 1;
		float frecuency = 0.001f;

		position.x += speed.x;
		speed.y = (sin(frecuency * position.x) * amplitude) * SCALE_FACTOR;
		position.y += speed.y;

		// CRZ ----
		// Proposal for frequency attacking system, CRZ
		time_to_attack = (SDL_GetTicks() - born) - (attacks * attack_frequency);
		if (SDL_TICKS_PASSED(time_to_attack, attack_frequency) == true)
		{
			shootAt(app->player->position);
			attacks++;
		}
		// ---- CRZ

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

	void shootAt(const Point2d<int> &destiny_position)
	{
		float dx = destiny_position.x - position.x;
		float dy = destiny_position.y - position.y;

		float angle = atan(dy / dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}

		int speed_value = 1.5 * SCALE_FACTOR;

		app->particles->pata_shot.speed.x = (int)(cos(angle) * speed_value);
		app->particles->pata_shot.speed.y = (int)(sin(angle) * speed_value);

		app->particles->addParticle(app->particles->pata_shot, position.x, position.y + 10 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT);

	}

};

#endif //!__ENEMY_H__
