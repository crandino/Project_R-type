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
		speed.x = -1.6 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		life = 12000; // In miliseconds
		attack_frequency = ((rand() % 3) + 3) * 1000;
		attacks = 0;
		graphics = texture;

		points = 200;
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
		float amplitude = 2;
		float frecuency = 0.0005f;

		position.x += speed.x;
		speed.y = (sin(frecuency * position.x) * amplitude) * SCALE_FACTOR;
		position.y += speed.y;

		// CRZ ----
		// Proposal for frequency attacking system, CRZ
		time_to_attack = (SDL_GetTicks() - born) - (attacks * attack_frequency);
		if (SDL_TICKS_PASSED(time_to_attack, attack_frequency) == true)
		{
			//shootAt(app->player->position);
			app->particles->addWeapon(BASIC_ENEMY_SHOT, position.x, position.y + 10 * SCALE_FACTOR, COLLIDER_ENEMY_SHOT);
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

};

#endif //!__ENEMY_H__
