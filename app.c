#include "settings.h"

void app_init(){
    /// Utils initialization
    utils_initializer();

    /// SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    /// SDL2 TTF initialization
    if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        assert(false);
        abort();
    }
}

void app_quit(){

}