#ifndef _SETTINGS_H_
#define _SETTINGS_H_

///// INCLUDES /////
/// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

/// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/// Headers
#include "sorting.h"
#include "stats.h"
#include "utils.h"
#include "visual.h"
#include "app.h"
#include "logger.h"


///// SETTINGS /////

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
#define N 100
#define BAR_WIDTH (WINDOW_WIDTH / N)
#define DELAY_MS 0.01

// Play Button
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80

#define AssertNew(ptr) { if (ptr == NULL) { assert(false); abort(); } }

#endif // _SETTINGS_H_