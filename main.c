#include "settings.h"

int DELAY_MS = 5;
int Gizmos = 0;

int main(int argc, char *argv[]) {
    utils_initializer();

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../Porscha.ttf", 32);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        // Handle error (exit or fallback)
    }
    SDL_Display* display = visual_CreateDisplay();
    if (!display) {
        return -1;
    }

    int* array = utils_createRandomIntArray(N);
    int* arrayB = utils_createRandomIntArray(N);
    int* arrayC = utils_createRandomIntArray(N);
    int* arrayD = utils_createRandomIntArray(N);

    bool running = true;
    bool started = false;
    SDL_Event event;

    // Play Screen
    while (running && !started) {
        draw_title_screen(display->renderer, font);
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
    insertion_sort(display->renderer, arrayB, N);
    selection_sort(display->renderer, arrayC, N);


    // Final display
    //draw_barsA(display->renderer, array, N, -1, -1);
    //draw_barsB(display->renderer, array, N, -1, -1);
    //draw_barsC(display->renderer, array, N, -1, -1);
    //draw_barsD(display->renderer, array, N, -1, -1);

    // No automatic quit
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
        draw_barsA(display->renderer, array, N, -1, -1);
        draw_barsB(display->renderer, arrayB, N, -1, -1);
        draw_barsC(display->renderer, arrayC, N, -1, -1);
        SDL_Delay(DELAY_MS);
    }

    visual_DestroyDisplay(display);
    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}
