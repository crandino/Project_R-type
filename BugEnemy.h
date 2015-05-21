//=================================
// include guard
#ifndef __BUGENEMY_H__
#define __BUGENEMY_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Enemy.h"
#include <math.h>
//=================================
// the actual class

class BugEnemy : public Enemy
{

private:

	float angle;

public:

	int speed_value;
	DynArray<Point2d<int>> path;
	unsigned int path_position;

	BugEnemy(Application *app, SDL_Texture *texture) : Enemy(app)
	{
		//Bug frames
		anim.frames.pushBack({ 0, 0, 32, 32 });
		anim.frames.pushBack({ 32, 0, 32, 32 });
		anim.frames.pushBack({ 64, 0, 32, 32 });
		anim.frames.pushBack({ 96, 0, 32, 32 });
		anim.frames.pushBack({ 128, 0, 32, 32 });
		anim.frames.pushBack({ 160, 0, 32, 32 });
		anim.frames.pushBack({ 192, 0, 32, 32 });
		anim.frames.pushBack({ 224, 0, 32, 32 });
		anim.frames.pushBack({ 256, 0, 32, 32 });
		anim.frames.pushBack({ 288, 0, 32, 32 });
		anim.frames.pushBack({ 320, 0, 32, 32 });
		anim.frames.pushBack({ 352, 0, 32, 32 });
		anim.frames.pushBack({ 384, 0, 32, 32 });
		anim.frames.pushBack({ 416, 0, 32, 32 });
		anim.frames.pushBack({ 448, 0, 32, 32 });
		anim.frames.pushBack({ 480, 0, 32, 32 });

		path.pushBack({ 540 * SCALE_FACTOR, 35 * SCALE_FACTOR });
		path.pushBack({ 450 * SCALE_FACTOR, 30 * SCALE_FACTOR });
		path.pushBack({ 410 * SCALE_FACTOR, 35 * SCALE_FACTOR });
		path.pushBack({ 200 * SCALE_FACTOR, 300 * SCALE_FACTOR });

	
		path_position = 0;
		anim.speed = 0.0f;
		speed_value = 2 * SCALE_FACTOR;
		angle = 0;
		life = 50000; // In miliseconds
		graphics = texture;
	}

	~BugEnemy()
	{ }

	void orientTo(const Point2d<int> &position_destiny)
	{
		// https://www.mathsisfun.com/geometry/unit-circle.html
		// It might be helpul!

		float dx = position_destiny.x - position.x;
		float dy = position_destiny.y - position.y;
		
		//LOG("%d %d", position_destiny.x - position.x, position_destiny.y - position.y);		

		angle = atan(dy/dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}

		speed.x = (int)(cos(angle) * speed_value);
		speed.y = (int)(sin(angle) * speed_value);

		//LOG("%f - %f", speed.x, speed.y);
		//LOG("%f", angle * 180.0f / M_PI);
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

		/*LOG("X: %f %f", position.x, path[path_position].x);
		LOG("Y: %f %f", position.y, path[path_position].y);*/
		//LOG("%d", path_position);

		if (position.isClosedTo(path[path_position], 1 * SCALE_FACTOR ))
		{ 		
			if (path_position < path.getNumElements() - 1)
				path_position++;
			else
				speed.x = speed.y = 0;
		}
		else
		{
			orientTo(path[path_position]);			
		}		

		position.x += speed.x;
		position.y += speed.y;

		anim.current_frame = (int)( angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements()));

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__ENEMY_H__
