#include "settings.h"

int DELAY_MS = 5;
int Gizmos = 0;

#if 1
int main(int argc, char *argv[]) {
    ///// INITIALIZATION /////
    app_init();

    SDL_Window* window = SDL_CreateWindow("Sorting Algorithms Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    /// Load Font
    TTF_Font *font = TTF_OpenFont("../PixelCaps.ttf", 32);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        // Handle error (exit or fallback)
    }

    int* array  = utils_createRandomIntArray(N);
    int* arrayB = utils_createRandomIntArray(N);
    int* arrayC = utils_createRandomIntArray(N);
    int* arrayD = utils_createRandomIntArray(N);

    bool running = true;
    bool started = false;
    SDL_Event event;

    // Play Screen
    while (running && !started) {
        draw_title_screen(renderer, font);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                for (int i = 0; i < 4; ++i) {
                    if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].w && my >= buttons[i].y && my <= buttons[i].y + buttons[i].h) {
                        printf("Button %d clicked!\n", i+1);
                        }
                }
                if (play_clicked(mx, my))
                    started = true;
            }
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
        SDL_Delay(10);
    }

    insertion_sort(renderer, array, N);
    bubble_sort(renderer, arrayB, N);
    selection_sort(renderer, arrayC, N);


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
        draw_barsA(renderer, array, N, -1, -1);
        draw_barsB(renderer, arrayB, N, -1, -1);
        draw_barsC(renderer, arrayC, N, -1, -1);
        SDL_Delay(DELAY_MS);
    }

    app_quit(font);

    return 0;
}

#elif 0
int main(int argc, char *argv[]) {

    Logger* logger = logger_create(LOG_TO_FILE_Y, LOG_TO_STREAM_Y, LOG_LEVEL_VERBOSE);
    logger_log(logger, LOG_LEVEL_INFO, "Logger %d initialized %s", 1, "successfully");
    logger_log(logger, LOG_LEVEL_DEBUG, "This is a debug message: %f", 3.14159);
    logger_log(logger, LOG_LEVEL_ERROR, "This is an error message: %s", "file not found");
    logger_destroy(logger);
}

#endif