#include <stdlib.h>
#include "SDL2-2.0.3\include\SDL.h"
//#include <SDL.h>

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

int main(int argc, char** argv)
{
	
	return 0;
}