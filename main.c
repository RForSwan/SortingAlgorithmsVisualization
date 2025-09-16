#include "settings.h"

int DELAY_MS = 5;
int Gizmos = 0;

#if 0
int main(int argc, char *argv[]) {
    ///// INITIALIZATION /////
    App* app = app_init(LOG_LEVEL_VERBOSE);

    int* arrayA = utils_createRandomIntArray(N);
    int* arrayB = utils_createRandomIntArray(N);
    int* arrayC = utils_createRandomIntArray(N);
    int* arrayD = utils_createRandomIntArray(N);


    // Play Screen
    while (app->app_running && !app->sort_running) {
        draw_title_screen(app->renderer, app->font);
        while (SDL_PollEvent(&app->event)) {
            if (app->event.type == SDL_QUIT)
                app->app_running = false;
            if (app->event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = app->event.button.x;
                int my = app->event.button.y;
                if (play_clicked(mx, my))
                    app->sort_running = true;
            }
            if (app->event.type == SDL_KEYDOWN) {
                printf("Key pressed: %s\n", SDL_GetKeyName(app->event.key.keysym.sym));
                if (app->event.key.keysym.sym == SDLK_p) {
                    DELAY_MS += 2;
                    printf("Delay Increase: %d ms\n", DELAY_MS);
                }
                if (app->event.key.keysym.sym == SDLK_m) {
                    DELAY_MS -= 2;
                    printf("Delay Decrease: %d ms\n", DELAY_MS);
                }
                if (app->event.key.keysym.sym == SDLK_g) {
                    Gizmos = !Gizmos;
                    printf("Gizmos status: %d\n", Gizmos);
                }
            }
        }
        SDL_Delay(10);
    }

    insertion_sort(app->renderer, arrayA, N);
    bubble_sort   (app->renderer, arrayB, N);
    selection_sort(app->renderer, arrayC, N);


    // Final display
    //draw_barsA(display->renderer, array, N, -1, -1);
    //draw_barsB(display->renderer, array, N, -1, -1);
    //draw_barsC(display->renderer, array, N, -1, -1);
    //draw_barsD(display->renderer, array, N, -1, -1);

    // No automatic quit
    while (app->app_running) {
        while (SDL_PollEvent(&app->event)) {
            if (app->event.type == SDL_QUIT)
                app->app_running = false;
        }
        draw_barsA(app->renderer, arrayA, N, -1, -1);
        draw_barsB(app->renderer, arrayB, N, -1, -1);
        draw_barsC(app->renderer, arrayC, N, -1, -1);
        SDL_Delay(DELAY_MS);
    }

    app_quit(app);

    return 0;
}

#elif 1
int main(int argc, char *argv[]) {
    printf("Hello, World!\n");
    return 42;
}

#endif