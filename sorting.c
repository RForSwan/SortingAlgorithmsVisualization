#include "settings.h"

void test_sort1(App* app, const unsigned int nb_elements, const size_t size, void* array)
{
    insertion_sort(app->renderer, (int*)array, nb_elements);
}

void test_sort2(App* app, const unsigned int nb_elements, const size_t size, void* array)
{
    bubble_sort(app->renderer, (int*)array, nb_elements);
}

// Insertion Sort Visualization
void insertion_sort(SDL_Renderer *renderer, int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            draw_barsA(renderer, arr, n, j, j + 1);

            SDL_Delay(DELAY_MS);
        }
        arr[j + 1] = key;
        draw_barsA(renderer, arr, n, j + 1, i);

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
                    Gizmos = !Gizmos;
                    printf("Gizmos status: %d\n", Gizmos);
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    exit(0);
                }
            }
        }
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
            draw_barsB(renderer, arr, n, j, j + 1);

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
                        Gizmos = !Gizmos;
                        printf("Gizmos status: %d\n", Gizmos);
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        exit(0);
                    }

                }
            }
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
            draw_barsC(renderer, arr, n, i, j);
            SDL_Delay(DELAY_MS);
        }
        // minimum swap with first
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        draw_barsC(renderer, arr, n, i, min_idx);

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
                    Gizmos = !Gizmos;
                    printf("Gizmos status: %d\n", Gizmos);
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    exit(0);
                }
            }
        }
        SDL_Delay(DELAY_MS);
    }
}
