//=================================
// include guard
#ifndef __ENEMY_H__
#define __ENEMY_H__
//=================================
// forward declared dependencies

//=================================
// included dependencies

//=================================
// the actual class

class Enemy
{

public:

	Application *app;

	SDL_Texture *graphics;
	Point2d<int> position;
	Point2d<int> speed;
	Animation anim;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	unsigned int fx;
	Collider *collider;

	
	Enemy(Application *parent)
	{
		app = parent;
		fx = 0;
		born = 0;
		life = 0;
		fx_played = false;
		collider = NULL;
		position.setZero();
		speed.setZero();
	}

	virtual ~Enemy()
	{
		if (collider)
			collider->to_delete = true;
	}
	
	virtual bool update() { return true; }
	
};


#endif //!__ENEMY_H__