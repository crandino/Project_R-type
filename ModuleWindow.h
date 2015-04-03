//=================================
// include guard
#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__
//=================================
// forward declared dependencies
//class Application;
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleWindow : public Module
{

public:

	//The window we'll be rendering to
	SDL_Window *window;
	//The surface contained by the window
	SDL_Surface *screen_surface;

	ModuleWindow(Application*);
	virtual ~ModuleWindow();

	bool init();
	bool cleanUp();

};

#endif // !__MODULEWINDOW_H__
