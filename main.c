#include "settings.h"
#include "sorting.h"
#include "stats.h"
#include "utils.h"
#include "visual.h"


int main(int argc, char *argv[]) {


    int arr[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % N + 1;

    int running = 1;
    int started = 0;
    SDL_Event event;

    // Play Screen
    while (running && !started) {
        draw_title_screen(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                if (play_clicked(mx, my))
                    started = 1;
            }
        }
        SDL_Delay(10);
    }

    // Bubble Sort Visualization
    for (int i = 0; i < N - 1 && running; i++) {
        for (int j = 0; j < N - i - 1 && running; j++) {
            // Check for quit
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    running = 0;
            }
            draw_bars(renderer, arr, N, j, j + 1);
            SDL_Delay(DELAY_MS);

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                draw_bars(renderer, arr, N, j, j + 1);
                SDL_Delay(DELAY_MS);
            }
        }
    }

    // Final display
    draw_bars(renderer, arr, N, -1, -1);

    // No automatic quit
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
