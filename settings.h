#ifndef _SETTINGS_H_
#define _SETTINGS_H_

/// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <threads.h>
#include <unistd.h>

/// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

/// Headers
#include "sorting.h"
#include "stats.h"
#include "utils.h"
#include "visual.h"
#include "app.h"
#include "logger.h"
#include "thread.h"

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