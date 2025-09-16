#include "settings.h"

#if 0
int main(int argc, char *argv[]) {
    ///// INITIALIZATION /////


    SDL_Window* window = SDL_CreateWindow("Sorting Algorithms Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false); abort();
    }


    int* array = utils_createRandomIntArray(N);

    bool running = true;
    bool started = false;
    SDL_Event event;

    ///// VISUALIZER LOOP /////
    while (running && !started) {
        draw_title_screen(renderer);
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

    bubble_sort(renderer, array, N);
    //insertion_sort(renderer, arr, N);
    //selection_sort(renderer, arr, N);

    // Final display
    draw_bars(renderer, array, N, -1, -1);

    // No automatic quit
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
        SDL_Delay(20);
    }

    ///// FREE MEMORY /////
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    return 0;
}

#elif 1
int main(int argc, char *argv[]) {

    Logger* logger = logger_create(LOG_TO_FILE_Y, LOG_TO_STREAM_Y, LOG_LEVEL_VERBOSE);
    logger_log(logger, LOG_LEVEL_INFO, "Logger %d initialized %s", 1, "successfully");
    logger_log(logger, LOG_LEVEL_DEBUG, "This is a debug message: %f", 3.14159);
    logger_log(logger, LOG_LEVEL_ERROR, "This is an error message: %s", "file not found");
    logger_destroy(logger);
}

#endif