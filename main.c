#include "settings.h"


int main(int argc, char *argv[]) {
    utils_initializer();

    SDL_Display* display = visual_CreateDisplay();
    if (!display) {
        return -1;
    }

    int* array = utils_createRandomIntArray(N);

    bool running = true;
    bool started = false;
    SDL_Event event;

    // Play Screen
    while (running && !started) {
        draw_title_screen(display->renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                if (play_clicked(mx, my))
                    started = true;
            }
        }
        SDL_Delay(10);
    }


    bubble_sort(display->renderer, array, N);
    //insertion_sort(renderer, arr, N);
    //selection_sort(renderer, arr, N);




    // Final display
    draw_bars(display->renderer, array, N, -1, -1);

    // No automatic quit
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
        SDL_Delay(10);
    }

    visual_DestroyDisplay(display);

    return 0;
}
