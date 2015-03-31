#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <Windows.h>
#include <stdio.h>

#define MIN(a,b) (a<b ? a : b)
#define MAX(a,b) (a>b ? a : b)
#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__)

void log(const char file[], int line, const char* format, ...);

template <class TYPE1>
void swap(TYPE1 &a, TYPE1 &b) {
	TYPE1 tmp;
	tmp = a;
	a = b;
	b = tmp;
}
#endif