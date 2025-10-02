#include "settings.h"

void test_sort1(App *app, const unsigned int nb_elements, const size_t size, void* array, int (*compare_func)(Logger* logger, const void* data_a, const void* data_b))
{
    void *key = calloc(1, size);
    for(int i = 1; i < nb_elements && app->threadsRun; i++)
    {
        memcpy(key, array + size * i,size);
        int j = i -1;

        while(j >= 0 && compare_func(app->logger, array + size * j, key) == COMPARE_GREATER && app->threadsRun)
        {
            memcpy(array + (size * (j + 1)), array + size * j, size);
            j--;
            draw_barsA(app, (int*)array, nb_elements, j, j + 1);
            SDL_Delay(DELAY_MS);
        }
        memcpy(array + size * (j + 1), key, size);
        draw_barsA(app, (int*)array, nb_elements, j + 1, i);

        SDL_Delay(DELAY_MS);
    }
    free(key);
}


void test_sort2(App *app, const unsigned int nb_elements, const size_t size, void* array, int (*compare_func)(Logger* logger, const void* data_a, const void* data_b))
{
    void *temp = calloc(1, size);
    for (int i = 0; i < nb_elements - 1 && app->threadsRun; i++) {
        for (int j = 0; j < nb_elements - i - 1 && app->threadsRun; j++) {
            if (compare_func(app->logger, array + size * j, array + size * (j + 1)) == COMPARE_GREATER) {
                // Swap
                memcpy(temp, array + size * j, size);
                memcpy(array + size * j, array + size * (j + 1), size);
                memcpy(array + size * (j + 1), temp, size);
            }
            draw_barsB(app, (int*)array, nb_elements, j, j + 1);
            SDL_Delay(DELAY_MS);
        }
    }
    free(temp);
}

// Insertion Sort Visualization
void insertion_sort(App *app, int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            draw_barsA(app, arr, n, j, j + 1);
            if(!app->threadsRun) return;
            SDL_Delay(DELAY_MS);
        }
        arr[j + 1] = key;
        draw_barsA(app, arr, n, j + 1, i);
        if(!app->threadsRun) return;
        SDL_Delay(DELAY_MS);
    }
}
// Bubble Sort Visualization
void bubble_sort(App *app, int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            draw_barsB(app, arr, n, j, j + 1);
            if(!app->threadsRun) return;
            SDL_Delay(DELAY_MS);
        }
    }
}
// Selection Sort Visualization
void selection_sort(App *app, int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
            draw_barsC(app, arr, n, i, j);
            SDL_Delay(DELAY_MS);
        }
        // minimum swap with first
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        draw_barsC(app, arr, n, i, min_idx);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                printf("Key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                if (event.key.keysym.sym == SDLK_p) {
                    DELAY_MS += 2;
                    printf("Delay Increase: %d ms\n", DELAY_MS);
                }
                if (event.key.keysym.sym == SDLK_m) {
                    DELAY_MS -= 2;
                    printf("Delay Decrease: %d ms\n", DELAY_MS);
                }
                if (event.key.keysym.sym == SDLK_g) {
                    app->inputs->gizmos = !app->inputs->gizmos;
                    printf("Gizmos status: %d\n", app->inputs->gizmos);
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    exit(0);
                }
            }
        }
        SDL_Delay(DELAY_MS);
    }
}
