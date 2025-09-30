#include "settings.h"


App* app_init(int LOG_LEVEL){

    /// Logger initialization
    Logger* logger = logger_create(LOG_TO_FILE_Y, LOG_TO_STREAM_Y, LOG_LEVEL_DEBUG);
    if(!logger) {
        perror("app_init : Logger initialization failed\n");
        assert(false);
        abort();
    }
    logger_log(logger, LOG_LEVEL_INFO, "app_init : Logger initialized successfully with level %s", LOG_LEVELS_NAME[LOG_LEVEL]);
    logger_log(logger, LOG_LEVEL_INFO, "app_init : Starting all dependencies ");

    /// Utils initialization
    utils_initializer();

    /// SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logger_log(logger, LOG_LEVEL_FATAL,"app_init : SDL_Init Error: %s", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : SDL initialized successfully");


    /// SDL2 TTF initialization
    if(TTF_Init() == -1) {
        logger_log(logger, LOG_LEVEL_FATAL,"app_init : TTF_Init: %s", TTF_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : SDL TTF initialized successfully");

    /// Create Window
    SDL_Window* window = SDL_CreateWindow("Sorting Algorithms Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        logger_log(logger, LOG_LEVEL_FATAL,"app_init : Failed creating window %s", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Window created successfully");

    /// Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        logger_log(logger, LOG_LEVEL_FATAL,"app_init : Failed creating renderer %s", SDL_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Renderer created successfully");

    /// Load Font
    TTF_Font *font = TTF_OpenFont("./Porscha.ttf", 32);
    if (!font)
    {
        logger_log(logger, LOG_LEVEL_FATAL,"app_init : Failed to load font: %s", TTF_GetError());
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Font loaded successfully");

    Inputs* inputs = inputs_create();
    if(!inputs)
    {
        logger_log(logger, LOG_LEVEL_FATAL, "app_init : Inputs gestion creation failed");
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Inputs gestion created successfully");

    AppData *appData = calloc(1, sizeof(AppData));
    if(!appData)
    {
        logger_log(logger, LOG_LEVEL_FATAL, "app_init : Failed to create app data");
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : App data created successfully");

    Colors *colorSet = visual_createColorSet();
    if(!colorSet)
    {
        logger_log(logger, LOG_LEVEL_FATAL, "app_init : Failed to create color set");
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Color set created successfully");


    /// Create App

    App* app = calloc(1,sizeof(App));
    AssertNew(app);

    app->window   = window;
    app->renderer = renderer;
    app->font     = font;

    app->app_running  = true;
    app->sort_running = false;

    app->logger = logger;
    app->inputs = inputs;

    app->appData = NULL;

    return app;

}

void app_play(App* app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_play : App starting ");

    int state = -1;

    while(true)
    {
        ///// MENU LOOP /////
        state = app_settingsScreen(app);
        if(state == APP_SCREEN_QUIT) break;

        ///// SORTING LOOP /////
        state = app_visualizationScreen(app);
        if(state == APP_SCREEN_QUIT) break;
    }
}

int app_settingsScreen(App *app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Currently on settings screen ");

    int state = -1;

    while(true)
    {
        inputs_get(app);
        if(app->inputs->quit) return APP_SCREEN_QUIT;
        if(app->inputs->pass) return APP_SCREEN_PASS;

        visual_drawSettingsScreen(app);

        SDL_RenderPresent(app->renderer);
    }
}

int app_visualizationScreen(App *app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_visualizationScreen : App starting ");


    void* array1 = utils_createArray(app->logger, 100, sizeof(int), SORTED_RANDOM, utils_GenAndAssign_int);
    ThreadData data1 = {.ID = 1, .app = app, .nb_elements = 100, .array = array1,
            .data_size = sizeof(int), .compare_func = compare_int,
            .sorting_algorithm = test_sort1};

    void* array2 = utils_copyArray(app->logger, 100, sizeof(int), array1);
    ThreadData data2 = {.ID = 2, .app = app, .nb_elements = 100, .array = array2,
            .data_size = sizeof(int), .compare_func = compare_int,
            .sorting_algorithm = test_sort2};

    SDL_Thread *threadID1 = SDL_CreateThread(thread_func, "first thread", (void*)&data1);
    SDL_Thread *threadID2 = SDL_CreateThread(thread_func, "second thread", (void*)&data2);
    ///// APP LOOP /////

    while(!app->inputs->quit || !app->inputs->pass)
    {
        SDL_RenderClear(app->renderer);

        inputs_get(app);

        SDL_Delay(DELAY_MS);

        //Clear screen
//        SDL_SetRenderDrawColor( app->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
//        SDL_RenderClear( app->renderer );

        //Render prompt
//        gSplashTexture.render( 0, 0 );

        //Update screen
        SDL_RenderPresent( app->renderer );
    }

    utils_destroyArray(app->logger, 100, int_size, array1, NULL);
    utils_destroyArray(app->logger, 100, int_size, array2, NULL);

    if(app->inputs->quit) return APP_SCREEN_QUIT;
    else                  return APP_SCREEN_PASS;
}

void app_quit(App *app){
    logger_log(app->logger, LOG_LEVEL_INFO, "app_quit : App ending ");

    TTF_CloseFont(app->font);
    app->font = NULL;

    SDL_DestroyRenderer(app->renderer);
    app->renderer = NULL;

    SDL_DestroyWindow(app->window);
    app->window = NULL;

    logger_destroy(app->logger);
    app->logger = NULL;

    free(app->appData);
    app->appData = NULL;

    visual_destroyColorSet(app->colorSet);
    app->colorSet = NULL;

    free(app);

    TTF_Quit();
    SDL_Quit();

}