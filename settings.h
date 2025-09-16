#ifndef _SETTINGS_H_
#define _SETTINGS_H_

///// INCLUDES /////

#include "libraries.h"

///// SETTINGS /////

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
#define N 100
#define BAR_WIDTH (WINDOW_WIDTH / N)
extern int DELAY_MS;
extern int Gizmos;

// Play Button
#define BUTTON_WIDTH 200
#define OPTION_BUTTON_WIDTH 300
#define BUTTON_HEIGHT 80
#define MARGIN 0

#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }

#endif // _SETTINGS_H_