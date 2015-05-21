//=================================
// included dependencies
#include "Globals.h"
#include "Application.h"
// Due to a problem with SDL:
//"  Error1 error LNK2005: _main already defined in
//   SDL2main.lib(SDL_windows_main.obj)  "
// I also include...
#include "SDL\include\SDL.h"

// pragma is an exclusive extension of Visual Studio,
// so it only works on here. 
#pragma comment( lib, "SDL/lib/x86/SDL2.lib")
#pragma comment( lib, "SDL/lib/x86/SDL2main.lib")

// --------------- Dr Memory ---------------	
// Arguments -visual_studio -- "$(TargetPath)"
// Directory $(SolutionDir)/

// ------------- SDL Config --------------------------

/* Setting up SDL configuration. On Project Properties
Configuration Propertires/VC++ Directories:
->Include directories: $(ProjectDir)SDL\include
->Library directories: $(ProjectDir)SDL\lib\x86
Linker/Input/Additional Dependencies, include
$(ProjectDir)SDL/lib/x86/SDL2.lib
$(ProjectDir)SDL/lib/x86/SDL2main.lib
Linker/Input/System/Subsystem/ choose
Windows (/SUBSYSTEM:WINDOWS)
*/

// ------------- Include rules ------------------------

/*If, for example, class A uses class B, then class B is one of class A's
dependencies. Whether it can be forward declared or needs to be included
depends on how B is used within A:

-do nothing if : A makes no references at all to B
-do nothing if : The only reference to B is in a friend declaration
-forward declare B if : A contains a B pointer or reference : B* myb;
-forward declare B if: one or more functions has a B object / pointer / reference
as a parementer, or as a return type : B MyFunction(B myb);
-#include "b.h" if: B is a parent class of A
-#include "b.h" if : A contains a B object : B myb;*/

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


int main(int argc, char** argv)
{

	int i = 10;
	if (i < 100) { LOG("Primer if"); }
	else if (i < 1000) { LOG("Segundo if"); }
	else { LOG("Tercero..."); }

	LOG("Starting game '%s'...", TITLE);
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application *app = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{

		case MAIN_CREATION:
		{
			LOG("----------Application Creation----------");
			app = new Application();
			state = MAIN_START;
			break;
		}

		case MAIN_START:
		{
			LOG("------------Application Init------------");
			if (app->init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				LOG("----------Application Update----------");
				state = MAIN_UPDATE;
			}
			break;
		}

		case MAIN_UPDATE:
		{
			int update_return = app->update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}
			
			if (update_return == UPDATE_STOP)
			{
				state = MAIN_FINISH;
			}
			break;
		}

		case MAIN_FINISH:
		{
			LOG("-----------Application CleanUp------------");
			if (app->cleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else			
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;
			break;
		}

		}
	}

	delete app;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}