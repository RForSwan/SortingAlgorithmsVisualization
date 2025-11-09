#include "settings.h"

static void app_drawTopbar(App *app)
{
    if (!app) return;

    // Topbar background
    SDL_Rect topbar = {.x = 0, .y = 0, .w = WINDOW_WIDTH, .h = TOP_BAR_HEIGHT};
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 40, 40, 40, 255);
    SDL_RenderFillRect(app->renderer, &topbar);
    SDL_mutexV(app->rendererUse);

    // Time string
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buf[32];
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);

    // Project name
    const char *project_name = "SortingAlgorithmsVisualization";

    // Render time (left)
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surf_time = TTF_RenderText_Blended(app->font, time_buf, textColor);
    if (surf_time) {
        SDL_Texture *tex_time;
        SDL_mutexP(app->rendererUse);
        tex_time = SDL_CreateTextureFromSurface(app->renderer, surf_time);
        SDL_mutexV(app->rendererUse);
        if (tex_time) {
            int tw, th;
            SDL_QueryTexture(tex_time, NULL, NULL, &tw, &th);
            SDL_Rect dest_time = {.x = 10, .y = (TOP_BAR_HEIGHT - th) / 2, .w = tw, .h = th};
            SDL_mutexP(app->rendererUse);
            SDL_RenderCopy(app->renderer, tex_time, NULL, &dest_time);
            SDL_mutexV(app->rendererUse);
            SDL_DestroyTexture(tex_time);
        }
        SDL_FreeSurface(surf_time);
    }

    // Render project name (center)
    SDL_Surface *surf_proj = TTF_RenderText_Blended(app->font, project_name, textColor);
    if (surf_proj) {
        SDL_Texture *tex_proj;
        SDL_mutexP(app->rendererUse);
        tex_proj = SDL_CreateTextureFromSurface(app->renderer, surf_proj);
        SDL_mutexV(app->rendererUse);
        if (tex_proj) {
            int tw, th;
            SDL_QueryTexture(tex_proj, NULL, NULL, &tw, &th);
            SDL_Rect dest_proj = {.x = (WINDOW_WIDTH - tw) / 2, .y = (TOP_BAR_HEIGHT - th) / 2, .w = tw, .h = th};
            SDL_mutexP(app->rendererUse);
            SDL_RenderCopy(app->renderer, tex_proj, NULL, &dest_proj);
            SDL_mutexV(app->rendererUse);
            SDL_DestroyTexture(tex_proj);
        }
        SDL_FreeSurface(surf_proj);
    }

    // README small button (right)
    SDL_Rect readme_rect = {.x = WINDOW_WIDTH - 110, .y = 10, .w = 100, .h = TOP_BAR_HEIGHT - 20};
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 70, 70, 70, 255);
    SDL_RenderFillRect(app->renderer, &readme_rect);
    rectangleRGBA(app->renderer, readme_rect.x, readme_rect.y, readme_rect.x + readme_rect.w, readme_rect.y + readme_rect.h, 255, 255, 255, 255);
    SDL_mutexV(app->rendererUse);

    SDL_Surface *surf_readme = TTF_RenderText_Blended(app->font, "README", textColor);
    if (surf_readme) {
        SDL_Texture *tex_readme;
        SDL_mutexP(app->rendererUse);
        tex_readme = SDL_CreateTextureFromSurface(app->renderer, surf_readme);

        SDL_mutexV(app->rendererUse);
        if (tex_readme) {
            int tw, th;
            SDL_QueryTexture(tex_readme, NULL, NULL, &tw, &th);
            SDL_Rect dest_readme = {.x = readme_rect.x + (readme_rect.w - tw) / 2, .y = readme_rect.y + (readme_rect.h - th) / 2, .w = tw, .h = th};
            SDL_mutexP(app->rendererUse);
            SDL_RenderCopy(app->renderer, tex_readme, NULL, &dest_readme);
            SDL_mutexV(app->rendererUse);
            SDL_DestroyTexture(tex_readme);
        }
        SDL_FreeSurface(surf_readme);
    }
}

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
    TTF_Font *font = TTF_OpenFont("./H.H. Samuel-font-defharo.ttf", 26);
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

    SDL_mutex *rendererUse = SDL_CreateMutex();
    if(!rendererUse)
    {
        logger_log(logger, LOG_LEVEL_FATAL, "app_init : Failed to create mutex");
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Mutex created successfully");

    if (SDL_WasInit(SDL_INIT_AUDIO) == 0) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            logger_log(logger, LOG_LEVEL_ERROR, "app_init : SDL_InitSubSystem(SDL_INIT_AUDIO) failed: %s", SDL_GetError());
        }
    }

    int mix_flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(mix_flags) & mix_flags) != mix_flags) {
        logger_log(logger, LOG_LEVEL_WARNING, "app_init : Mix_Init warning: %s", Mix_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        logger_log(logger, LOG_LEVEL_ERROR, "app_init : Mix_OpenAudio failed: %s", Mix_GetError());
    } else {
        logger_log(logger, LOG_LEVEL_INFO, "app_init : Audio device opened successfully");
        Mix_AllocateChannels(16);
    }


    /// Create App

    App* app = calloc(1,sizeof(App));
    AssertNew(app);

    utils_set_randomness(app->selected_randomness);
    app->window   = window;
    app->renderer = renderer;
    app->font     = font;

    app->app_running  = true;
    app->sort_running = false;

    app->logger = logger;
    app->inputs = inputs;

    app->appData = NULL;

    app->lightMode = true;
    app->colorSet = colorSet;

    app->threadsRun = true;

    app->rendererUse = rendererUse;

    app->button_sound = sound_load_effect("./buttonsound.wav");
    if (!sound_init()) {
        logger_log(app->logger, LOG_LEVEL_WARNING, "app_init : sound_init failed, continuing without audio");
        app->button_sound = NULL;
    } else {
        app->button_sound = sound_load_effect("./buttonsound.wav");
        if (!app->button_sound) {
            logger_log(app->logger, LOG_LEVEL_WARNING, "app_init : could not load button sound");
        }
    }

    app->SortA_time = 0.0;
    app->SortB_time = 0.0;
    app->sortTime_mutex = SDL_CreateMutex();
    if(!app->sortTime_mutex)
    {
        logger_log(logger, LOG_LEVEL_FATAL, "app_init : Failed to create sort time mutex");
        assert(false);
        abort();
    }
    else logger_log(logger, LOG_LEVEL_INFO, "app_init : Sort time mutex created successfully");

    return app;

}

void app_play(App* app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_play : App starting ");

    int state = -1;

    app->selected_nb_elements = 32; // Default value

    while(true)
    {
        ///// MENU LOOP /////
        state = app_settingsScreen(app);
        if(state == APP_SCREEN_QUIT) break;

        inputs_clear(app);


        ///// SORTING LOOP /////
        state = app_visualizationScreen(app);
        if(state == APP_SCREEN_QUIT) break;

        inputs_clear(app);
    }
}

int app_settingsScreen(App *app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Currently on settings screen ");

    int state = -1;

    SDL_Rect buttons_r[NB_BUTTONS_SETTINGS] =
            {
                    {.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2,  .y = (WINDOW_HEIGHT - BUTTON_HEIGHT) - MARGIN, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT},
                    {.x = 60, .y = 300,                       .w = OPTION_BUTTON_WIDTH, .h = BUTTON_HEIGHT},
                    {.x = 60, .y = 350 + (BUTTON_HEIGHT) * 1, .w = OPTION_BUTTON_WIDTH, .h = BUTTON_HEIGHT},
                    {.x = 60, .y = 400 + (BUTTON_HEIGHT) * 2, .w = OPTION_BUTTON_WIDTH, .h = BUTTON_HEIGHT},
                    {.x = 60, .y = 450 + (BUTTON_HEIGHT) * 3, .w = OPTION_BUTTON_WIDTH, .h = BUTTON_HEIGHT},
            };
    // Button buttons[NB_BUTTONS_SETTINGS] =
    //         {
    //                 {.rect = buttons_r[0], .label = "Play", .hovered = false, .pressed = false},
    //                 {.rect = buttons_r[1], .label = "1",    .hovered = false, .pressed = false},
    //                 {.rect = buttons_r[2], .label = "2",    .hovered = false, .pressed = false},
    //                 {.rect = buttons_r[3], .label = "3",    .hovered = false, .pressed = false},
    //                 {.rect = buttons_r[4], .label = "4",    .hovered = false, .pressed = false},
    //         };

    static const char *selector_options[3] = {"Option 1", "Option 2", "Option 3"};
    static int selector_idx[1] = {0}; // for the others buttons
    static char label_buffers[6][64]; // 0 = size & 1..3 = others


    while(true)
    {
        inputs_clear(app);
        SDL_RenderClear(app->renderer);

        for (int s = 0; s < 3; ++s) {
            snprintf(label_buffers[s+1], sizeof(label_buffers[s+1]), "< %s >", selector_options[selector_idx[s] % 3 ]);
        }
        snprintf(label_buffers[0], sizeof(label_buffers[0]), "Size: %d", selector_sizes[selector_size_idx]);
        snprintf(label_buffers[2], sizeof(label_buffers[2]), "Rand : %d", selector_rand[selector_rand_idx]);

        // Update selector labels
        // for (int s = 0; s < 4; ++s) {
        //     snprintf(label_buffers[s], sizeof(label_buffers[s]), "< %s >", selector_options[ selector_idx[s] % 3 ]);
        // }


        // Buttons: index 0 = Play, 1 = Size, 2..4 = other selectors
        Button buttons[NB_BUTTONS_SETTINGS] =
        {
            {.rect = buttons_r[0], .label = "Play", .hovered = false, .pressed = false},
            {.rect = buttons_r[1], .label = label_buffers[0], .hovered = false, .pressed = false},
            {.rect = buttons_r[2], .label = label_buffers[1], .hovered = false, .pressed = false},
            {.rect = buttons_r[3], .label = label_buffers[2], .hovered = false, .pressed = false},
            {.rect = buttons_r[4], .label = label_buffers[3], .hovered = false, .pressed = false},
        };

        inputs_get(app, buttons, NB_BUTTONS_SETTINGS);

        // Readme button detection (top-right)
        SDL_Rect readme_rect = {.x = WINDOW_WIDTH - 110, .y = 10, .w = 100, .h = TOP_BAR_HEIGHT - 20};
        if (app->inputs->clicked &&
            app->inputs->mouseX >= readme_rect.x && app->inputs->mouseX <= readme_rect.x + readme_rect.w &&
            app->inputs->mouseY >= readme_rect.y && app->inputs->mouseY <= readme_rect.y + readme_rect.h)
        {
            logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : README clicked, opening file");
            if (app->button_sound) sound_play_effect(app->button_sound, 0);
            // Open README with system default
            system("xdg-open README.md >/dev/null 2>&1 &");
            // consume the click to avoid also toggling selectors
            app->inputs->clicked = false;
            for(int i=0;i<NB_BUTTONS_SETTINGS;i++) buttons[i].pressed = false;
        }

        // Process selector buttons: cycle forward on click
        /*for(int i = 1; i < NB_BUTTONS_SETTINGS; i++)
        {
            if(buttons[i].pressed)
            {
                if (app->button_sound) sound_play_effect(app->button_sound, 0);
                // i-1 maps to selector_idx array
                int sel = i - 1;
                selector_idx[sel] = (selector_idx[sel] + 1) % 3;
                // small log
                logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Selector %d changed to %s", sel+1, selector_options[selector_idx[sel]]);
            }
        }*/
        if(buttons[1].pressed)
        {
            if (app->button_sound) sound_play_effect(app->button_sound, 0);
            selector_size_idx = (selector_size_idx + 1) % (sizeof(selector_sizes)/sizeof(selector_sizes[0]));
            app->selected_nb_elements = selector_sizes[selector_size_idx];
            logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Selected size changed to %d", app->selected_nb_elements);
        }
        // Process other selector buttons
        if (buttons[2].pressed)
        {
            if (app->button_sound) sound_play_effect(app->button_sound, 0);
            selector_type_idx = (selector_type_idx + 1) % (sizeof(selector_types) / sizeof(selector_types[0]));
            app->selected_data_type = selector_types[selector_type_idx];
            logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Selected data type changed to %d", app->selected_data_type);
        }
        if (buttons[3].pressed)
        {
            if (app->button_sound) sound_play_effect(app->button_sound, 0);
            selector_rand_idx = (selector_rand_idx + 1) % (sizeof(selector_rand) / sizeof(selector_rand[0]));
            app->selected_randomness = selector_rand[selector_rand_idx];
            utils_set_randomness(app->selected_randomness);
            logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Selected randomness changed to %d", app->selected_randomness);
        }
        for(int i = 4; i < NB_BUTTONS_SETTINGS; i++)
        {
            if(buttons[i].pressed)
            {
                if (app->button_sound) sound_play_effect(app->button_sound, 0);
                int sel = i - 2; // map button 2->sel0, 3->sel1, 4->sel2
                selector_idx[sel] = (selector_idx[sel] + 1) % 3;
                logger_log(app->logger, LOG_LEVEL_INFO, "app_settingsScreen : Selector %d changed to %s", sel+1, selector_options[selector_idx[sel]]);
            }
        }

        if(app->inputs->quit) return APP_SCREEN_QUIT;
        if(buttons[0].pressed) return APP_SCREEN_PASS;

        visual_drawSettingsScreen(app, buttons);
        if (app->inputs && app->inputs->gizmos) {
            visual_draw_gizmos_for_buttons(app, buttons, NB_BUTTONS_SETTINGS);
        }
        app_drawTopbar(app);

        SDL_Delay(DELAY_MS);

        SDL_RenderPresent(app->renderer);
    }
}

int app_visualizationScreen(App *app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_visualizationScreen : App starting ");

    app->threadsRun = true;

    // void* array1 = utils_createArray(app->logger, selected_nb_elements, sizeof(int), SORTED_RANDOM, utils_GenAndAssign_int);
    // ThreadData data1 = {.ID = 0, .app = app, .nb_elements = selected_nb_elements, .array = array1,
    //         .data_size = sizeof(int), .compare_func = compare_int,
    //         .sorting_algorithm = test_sort1};

    // void* array2 = utils_copyArray(app->logger, selected_nb_elements, sizeof(int), array1);
    // ThreadData data2 = {.ID = 1, .app = app, .nb_elements = selected_nb_elements, .array = array2,
    //         .data_size = sizeof(int), .compare_func = compare_int,
    //         .sorting_algorithm = test_sort2};
    utils_set_randomness(app->selected_randomness);

    void* array1 = utils_createArray(app->logger, app->selected_nb_elements, sizeof(int), SORTED_RANDOM, utils_GenAndAssign_int);
    ThreadData *data1 = calloc(1, sizeof(ThreadData));
    AssertNew(data1);
    data1->ID = 0;
    data1->app = app;
    data1->nb_elements = app->selected_nb_elements;
    data1->array = array1;
    data1->data_size = sizeof(int);
    data1->compare_func = compare_int;
    data1->sorting_algorithm = test_sort1;

    void* array2 = utils_copyArray(app->logger, app->selected_nb_elements, sizeof(int), array1);
    ThreadData *data2 = calloc(1, sizeof(ThreadData));
    AssertNew(data2);
    data2->ID = 1;
    data2->app = app;
    data2->nb_elements = app->selected_nb_elements;
    data2->array = array2;
    data2->data_size = sizeof(int);
    data2->compare_func = compare_int;
    data2->sorting_algorithm = test_sort2;


    SDL_Thread *threadID1 = SDL_CreateThread(thread_func, "first thread", (void*)data1);
    SDL_Thread *threadID2 = SDL_CreateThread(thread_func, "second thread", (void*)data2);


    ///// APP LOOP /////

    while(!app->inputs->quit && !app->inputs->pass)
    {
        inputs_clear(app);
        //SDL_RenderClear(app->renderer);

        inputs_get(app, NULL, 0);

        if (app->inputs->basktosettings) {
            logger_log(app->logger, LOG_LEVEL_INFO, "app_visualizationScreen : Back-to-settings requested, stopping sorts");
            break;
        }

        visual_drawVisualizationScreen(app, NULL);
        SDL_Delay(DELAY_MS);

        SDL_RenderPresent(app->renderer);
    }

    app->threadsRun = false;

    int threadReturn1 = 0, threadReturn2 = 0;
    if (threadID1) SDL_WaitThread(threadID1, &threadReturn1);
    if (threadID2) SDL_WaitThread(threadID2, &threadReturn2);
    SDL_Delay(DELAY_MS*10);

    utils_destroyArray(app->logger, app->selected_nb_elements, int_size, array1, NULL);
    utils_destroyArray(app->logger, app->selected_nb_elements, int_size, array2, NULL);
    free(data1);
    free(data2);

    if (app->inputs) app->inputs->basktosettings = false;

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

    free(app->appData);
    app->appData = NULL;

    visual_destroyColorSet(app->colorSet);
    app->colorSet = NULL;

    inputs_destroy(app->inputs);
    app->inputs = NULL;

    logger_destroy(app->logger);
    app->logger = NULL;


    free(app);
    if (app->button_sound) {
        sound_free_effect(app->button_sound);
        app->button_sound = NULL;
    }
    sound_clean();
    TTF_Quit();
    SDL_Quit();

}
