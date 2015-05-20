//=================================
// include guard
#ifndef __POWERUP_H__
#define __POWERUP_H__
//=================================
// forward declared dependencies

//=================================
// included dependencies

//=================================
// the actual class

class PowerUp
{

public:

	Application *app;

	SDL_Texture *graphics;
	Point2d<float> position;
	Point2d<float> speed;
	Animation anim;
	Uint32 born;
	Uint32 life;
	Collider *collider;

	PowerUp(Application *parent) : app(parent), born(0), life(0), collider(NULL)
	{
		position.setZero();
		speed.setZero();
	}

	~PowerUp()
	{
		if (collider)
			collider->to_delete = true;
	}


	virtual bool update() { return true; }

};


#endif //!__POWERUP_H__