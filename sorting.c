#include "settings.h"


// Insertion Sort Visualization
void insertion_sort(SDL_Renderer *renderer, int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            draw_bars(renderer, arr, n, j, j + 1);
            SDL_Delay(DELAY_MS);
        }
        arr[j + 1] = key;
        draw_bars(renderer, arr, n, j + 1, i);
        SDL_Delay(DELAY_MS);
    }
}
// Bubble Sort Visualization
void bubble_sort(SDL_Renderer *renderer, int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            draw_bars(renderer, arr, n, j, j + 1);
            SDL_Delay(DELAY_MS);
        }
    }
}
// Selection Sort Visualization
void selection_sort(SDL_Renderer *renderer, int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
            draw_bars(renderer, arr, n, i, j);
            SDL_Delay(DELAY_MS);
        }
        // minimum swap with first
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        draw_bars(renderer, arr, n, i, min_idx);
        SDL_Delay(DELAY_MS);
    }
}
