//=================================
// include guard
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//=================================
// included dependencies
#include <Windows.h>
#include <stdio.h>

// Game Configuration
#define TITLE "R-TYPE"
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 256
#define SCREEN_SIZE 2
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true

// Scaling factor to avoid floats...
#define SCALE_FACTOR 100

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#endif // !__GLOBALS_H__
