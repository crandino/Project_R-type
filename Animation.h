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

	bool reverse;
	bool loop;
	float speed;
	DynArray<SDL_Rect> frames;

	Animation() : frames(5), speed(1.0f), current_frame(0), reverse(false), loop(true)
	{ }

	SDL_Rect& getCurrentFrame()
	{
		if (reverse != true)
			current_frame += speed;
		else
			current_frame -= speed;
		
		if (loop == true)
		{
			if (current_frame >= frames.getNumElements())
				current_frame = 0;
		}
		else
			if (current_frame >= frames.getNumElements())
				current_frame = frames.getNumElements() - 1.0f;

		return frames[(int)current_frame];
	}
};


#endif // !__ANIMATION_H__