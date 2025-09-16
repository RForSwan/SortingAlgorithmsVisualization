#ifndef _APP_H_
#define _APP_H_

///// INCLUDES /////

#include "libraries.h"

///// APP /////

typedef struct App_s{
    SDL_Window*   window;
    SDL_Renderer* renderer;
    TTF_Font*     font;

    bool app_running;
    bool sort_running;

    SDL_Event event;

    Logger* logger;
}App;

App* app_init(int LOG_LEVEL);
void app_quit(App* app);

#endif