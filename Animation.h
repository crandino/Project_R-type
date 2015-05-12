//=================================
// include guard
#ifndef __ANIMATION_H__
#define __ANIMATION_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "DynArray.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class Animation 
{
private:

	float current_frame;
	int loops;

public:

	bool loop;
	float speed;
	DynArray<SDL_Rect> frames;
	
	Animation() : frames(5), speed(1.0f), current_frame(0), loop(true), loops(0)
	{ }

	Animation(const Animation& a) :	frames(a.frames), speed(a.speed), current_frame(0), loop(a.loop), loops(0)
	{ }

	SDL_Rect& getCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.getNumElements())
		{
			current_frame = (loop) ? 0.0f : frames.getNumElements() - 1;
			loops++;
		}
		return frames[(int)current_frame];
	}

	const SDL_Rect &peekCurrentFrame() const
	{
		return frames[(int)current_frame];
	}

	bool finished()
	{
		return loops > 0;
	}

	void reset()
	{
		loops = 0; // CRZ
		current_frame = 0;
	}

};


#endif // !__ANIMATION_H__