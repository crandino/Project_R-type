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

	DynArray<Point2d<int>> *path1;
	DynArray<Point2d<int>> *path2;
	DynArray<Point2d<int>> *path3;
	DynArray<Point2d<int>> *path4;
	DynArray<Point2d<int>> *path5;
	DynArray<Point2d<int>> *path6;
	unsigned int path_position;

	DynArray<DynArray<Point2d<int>>*> path_set;
	unsigned int current_path;
	bool path_found;

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

		path1 = new DynArray<Point2d<int>>;
		path1->pushBack({ 600 * SCALE_FACTOR, 110 * SCALE_FACTOR });
		path1->pushBack({ 550 * SCALE_FACTOR, 35 * SCALE_FACTOR });
		path1->pushBack({ 450 * SCALE_FACTOR, 30 * SCALE_FACTOR });
		path1->pushBack({ 410 * SCALE_FACTOR, 35 * SCALE_FACTOR });
		path1->pushBack({ 150 * SCALE_FACTOR, 300 * SCALE_FACTOR });
		path_set.pushBack(path1);

		path2 = new DynArray<Point2d<int>>;
		path2->pushBack({ 1050 * SCALE_FACTOR, 110 * SCALE_FACTOR });
		path2->pushBack({ 1025 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 1000 * SCALE_FACTOR, 140 * SCALE_FACTOR });
		path2->pushBack({ 975 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 950 * SCALE_FACTOR, 110 * SCALE_FACTOR });
		path2->pushBack({ 925 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 900 * SCALE_FACTOR, 140 * SCALE_FACTOR });
		path2->pushBack({ 875 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 850 * SCALE_FACTOR, 110 * SCALE_FACTOR });
		path2->pushBack({ 825 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 800 * SCALE_FACTOR, 140 * SCALE_FACTOR });
		path2->pushBack({ 775 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 750 * SCALE_FACTOR, 110 * SCALE_FACTOR });
		path2->pushBack({ 725 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path2->pushBack({ 700 * SCALE_FACTOR, 140 * SCALE_FACTOR });
		path2->pushBack({ 675 * SCALE_FACTOR, 125 * SCALE_FACTOR });
		path_set.pushBack(path2);

		path3 = new DynArray<Point2d<int>>;
		path3->pushBack({ 1500 * SCALE_FACTOR, 80 * SCALE_FACTOR });
		path3->pushBack({ 1450 * SCALE_FACTOR, 100 * SCALE_FACTOR });
		path3->pushBack({ 1100 * SCALE_FACTOR, 100 * SCALE_FACTOR });
		path_set.pushBack(path3);

		path4 = new DynArray<Point2d<int>>;
		path4->pushBack({ 1960 * SCALE_FACTOR, 80 * SCALE_FACTOR });
		path4->pushBack({ 1940 * SCALE_FACTOR, 90 * SCALE_FACTOR });
		path4->pushBack({ 1920 * SCALE_FACTOR, 100 * SCALE_FACTOR });
		path4->pushBack({ 1500 * SCALE_FACTOR, 100 * SCALE_FACTOR });
		path_set.pushBack(path4);

		path5 = new DynArray<Point2d<int>>;
		path5->pushBack({ 2275 * SCALE_FACTOR, 170 * SCALE_FACTOR });
		path5->pushBack({ 2165 * SCALE_FACTOR, 120 * SCALE_FACTOR });
		path5->pushBack({ 2120 * SCALE_FACTOR, 80 * SCALE_FACTOR });
		path5->pushBack({ 2165 * SCALE_FACTOR, 40 * SCALE_FACTOR });
		path5->pushBack({ 2210 * SCALE_FACTOR, 80 * SCALE_FACTOR });
		path5->pushBack({ 2080 * SCALE_FACTOR, 160 * SCALE_FACTOR });
		path5->pushBack({ 1800 * SCALE_FACTOR, 160 * SCALE_FACTOR });
		path_set.pushBack(path5);

		path6 = new DynArray<Point2d<int>>;
		path6->pushBack({ 3490 * SCALE_FACTOR, 70 * SCALE_FACTOR });
		path6->pushBack({ 3410 * SCALE_FACTOR, 180 * SCALE_FACTOR });
		path6->pushBack({ 3320 * SCALE_FACTOR, 180 * SCALE_FACTOR });
		path6->pushBack({ 3240 * SCALE_FACTOR, 140 * SCALE_FACTOR });
		path6->pushBack({ 3100 * SCALE_FACTOR, 30 * SCALE_FACTOR });
		path_set.pushBack(path6);

		path_found = false;
		current_path = 0;
	
		path_position = 0;
		anim.speed = 0.0f;
		speed_value = 2 * SCALE_FACTOR;
		angle = 0;
		life = 50000; // In miliseconds
		graphics = texture;

		points = 200;
	}

	~BugEnemy()
	{
		for (unsigned int i = 0; i < path_set.getNumElements(); i++)
		{
			delete path_set[i];
		}
	}

	bool findPath()
	{
		DynArray<Point2d<int>> *tmp;
		for (unsigned int i = 0; i < path_set.getNumElements(); i++)
		{
			tmp = path_set[i];
			if ( (*tmp)[0].x <= position.x)
				current_path = i;
		}
		return true;
	}

	void orientTo(const Point2d<int> &position_destiny)
	{
		// https://www.mathsisfun.com/geometry/unit-circle.html
		// It might be helpfull!

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
	}

	bool update()
	{
		bool ret = true;

		if (path_found != true)
			path_found = findPath();

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

		if (position.isClosedTo((*path_set[current_path])[path_position], 1 * SCALE_FACTOR ))
		{ 		
			if (path_position < (*path_set[current_path]).getNumElements() - 1)
				path_position++;
			else
				speed.x = speed.y = 0;
		}
		else
		{
			orientTo((*path_set[current_path])[path_position]);
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
