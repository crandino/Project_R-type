//=================================
// included dependencies
#include "ModuleInput.h"
// macros
#define MAX_KEYS 300
//=================================
// the actual code

ModuleInput::ModuleInput(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
}

// Destructor
ModuleInput::~ModuleInput() 
{
	delete keyboard;
}

// Called before render is available
bool ModuleInput::init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::preUpdate()
{
	//SDL_PumpEvents() gathers all the pending input
	//information from devices and places it in the 
	//event queue.Without calls to SDL_PumpEvents()
	//no events would ever be placed on the queue.
	SDL_PumpEvents();

	//Returns a pointer to an array of key states.A value
	//of 1 means that the key is pressed and a value of 0 
	//means that it is not.Indexes into this array are 
	//obtained by using SDL_Scancode values.
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::cleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}