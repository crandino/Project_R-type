#include <stdio.h>
#include "SDL2-2.0.3\include\SDL.h"
//#include <SDL.h>

#include "Utilities.h"
#include "Application.h"

// pragma is an exclusive extension of Visual Studio,
// so it only works on here. 
#pragma comment( lib, "SDL2-2.0.3/lib/x86/SDL2.lib")
#pragma comment( lib, "SDL2-2.0.3/lib/x86/SDL2main.lib")

/* Setting up SDL configuration. On Project Properties 
Configuration Propertires/VC++ Directories:
	->Include directories: $(ProjectDir)SDL2-2.0.3\include
	->Library directories: $(ProjectDir)SDL2-2.0.3\lib\x86
Linker/Input/Additional Dependencies, include
	$(ProjectDir)SDL2-2.0.3/lib/x86/SDL2.lib
	$(ProjectDir)SDL2-2.0.3/lib/x86/SDL2main.lib
Linker/Input/System/Subsystem/ choose
	Windows (/SUBSYSTEM:WINDOWS)
*/

enum main_states {
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* app = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
			case MAIN_CREATION:
			{
				LOG("Application creation---------");
				app = new Application();
				state = MAIN_START;

				break;
			}		

			case MAIN_START:
			{
				LOG("Application init-------------");
				if (app->init() == false)
				{
					LOG("Application creation exits with error--");
					state = MAIN_EXIT;
				}
				else
					state = MAIN_UPDATE;

				break;
			}
			
			case MAIN_UPDATE:
			{
				int update_return = app->update();

				if (update_return == UPDATE_ERROR)
				{
					LOG("Application update exits with error---");
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
				LOG("Application Clean Up-------------");
				if (app->cleanUp() == false)
				{
					LOG("Application Clean Up exits with error---");
					state = MAIN_EXIT;
				}
				else
					main_return = EXIT_SUCCESS;

				state = MAIN_EXIT;

				break;
			}
		}
	}

	delete app;
	LOG("Sayonara, baby...");	
	return main_return;
}