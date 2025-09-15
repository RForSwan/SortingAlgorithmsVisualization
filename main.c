#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define N 100
#define BAR_WIDTH (WINDOW_WIDTH / N)
#define DELAY_MS 1

// Play Button
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80


void draw_title_screen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black bg
    SDL_RenderClear(renderer);

    // Play button
    SDL_Rect button = {(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_RenderFillRect(renderer, &button);

    // Button Border
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    SDL_RenderDrawRect(renderer, &button);

    SDL_RenderPresent(renderer);

}

// Check for mouse click in button
int play_clicked(int x, int y)
{
    int bx = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
    int by = (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2;
    return x >= bx && x <= bx + BUTTON_WIDTH && y >= by && y <= by + BUTTON_HEIGHT;
}

void draw_bars(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, 0, color_value - 255, 0, color_value - 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N;
        // Set lines at the bottom
        SDL_Rect bar = {k * BAR_WIDTH, WINDOW_HEIGHT - bar_height, BAR_WIDTH - 1, bar_height};
        SDL_RenderFillRect(renderer, &bar);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bubble Sort Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
