//=================================
// include guard
#ifndef __MODULEINTERFACE_H__
#define __MODULEINTERFACE_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleInterface : public Module
{
public:

	//Interface parts
	SDL_Texture *img_life;                // Life icon
	SDL_Texture *img_beam;				  // Beam name
	SDL_Texture *img_p1;                  // Player1 icon
	SDL_Texture *img_hi;                  // Hi- name
	SDL_Texture *img_numbers_interface;   // Numbers for score
	SDL_Texture *img_bar;                 // Beam bar
	SDL_Texture *charge_beam;             // Beam rectangle for charging

	Animation numbers_points;
	unsigned int position_interface;

	ModuleInterface(Application *app, bool start_enabled = true);
	~ModuleInterface();

	bool start();
	update_status update();
	bool cleanUp();

	void print_score(unsigned int pos);

};

#endif // !__MODULEINTERFACE_H__