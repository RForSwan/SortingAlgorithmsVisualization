#include "settings.h"



App* app_init(int LOG_LEVEL){
    /// Utils initialization
    utils_initializer();

    /// Logger initialization
    Logger* logger = logger_create(LOG_TO_FILE_Y, LOG_TO_STREAM_Y, LOG_LEVEL_DEBUG);
    logger_log(logger, LOG_LEVEL_INFO, "Logger initialized successfully");


    /// SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logger_log(logger, LOG_LEVEL_FATAL,"SDL_Init Error: %s\n", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "SDL initialized successfully");


    /// SDL2 TTF initialization
    if(TTF_Init() == -1) {
        logger_log(logger, LOG_LEVEL_FATAL,"TTF_Init: %s\n", TTF_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "SDL TTF initialized successfully");

    /// Create Window
    SDL_Window* window = SDL_CreateWindow("Sorting Algorithms Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        logger_log(logger, LOG_LEVEL_FATAL,"ERROR - Create window %s\n", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "Window created successfully");

    /// Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        logger_log(logger, LOG_LEVEL_FATAL,"ERROR - Create renderer %s\n", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "Renderer created successfully");

    /// Load Font
    TTF_Font *font = TTF_OpenFont("../PixelCaps.ttf", 32);
    TTF_Font *smallfont = TTF_OpenFont("../PixelCaps.ttf", 16);
    if (!font) {
        logger_log(logger, LOG_LEVEL_FATAL,"Failed to load font: %s\n", TTF_GetError());
        assert(false);
        abort();
    }
    if (!smallfont) {
        logger_log(logger, LOG_LEVEL_FATAL,"Failed to load smallfont: %s\n", TTF_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "Font loaded successfully");

    App* app = calloc(1,sizeof(App));
    AssertNew(app);

    app->window   = window;
    app->renderer = renderer;
    app->font     = font;
    app->smallfont= smallfont;

    app->app_running  = true;
    app->sort_running = false;

    app->logger = logger;

    return app;

}

void app_quit(App* app){

    TTF_CloseFont(app->font);
    app->font = NULL;

    SDL_DestroyRenderer(app->renderer);
    app->renderer = NULL;

    SDL_DestroyWindow(app->window);
    app->window = NULL;

    free(app);

    TTF_Quit();
    SDL_Quit();

}