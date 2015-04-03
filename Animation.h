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

public:

	float speed;
	DynArray<SDL_Rect> frames;

	Animation() : frames(5), speed(1.0f), current_frame(0)
	{ }

	SDL_Rect& getCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.getNumElements())
			current_frame = 0;

		return frames[(int)current_frame];
	}
};


#endif // !__ANIMATION_H__