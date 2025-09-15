#include "settings.h"

SDL_Display* visual_CreateDisplay()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Display* display = calloc(1, sizeof(SDL_Display));

    display->window = SDL_CreateWindow("Bubble Sort Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!display->window){
        printf("Error creating SDL Window: %s\n", SDL_GetError());
        free(display);
        SDL_Quit();
        return NULL;
    }
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if(!display->renderer){
        printf("Error creating SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(display->window);
        free(display);
        SDL_Quit();
        return NULL;
    }
    return display;
}

void visual_DestroyDisplay(SDL_Display* display)
{
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    free(display);
    SDL_Quit();
}

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
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N;
        // Set lines at the bottom
        SDL_Rect bar = {k * BAR_WIDTH, WINDOW_HEIGHT - bar_height, BAR_WIDTH - 1, bar_height};
        SDL_RenderFillRect(renderer, &bar);
    }
    SDL_RenderPresent(renderer);
}