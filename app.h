#ifndef _APP_H_
#define _APP_H_

///// INCLUDES /////



///// APP /////

typedef struct Logger_s Logger;
typedef struct Inputs_s Inputs;
typedef struct Colors_s Colors;

enum
{
    APP_SORT_DATATYPE_INT,
    APP_SORT_DATATYPE_FLOAT,
    APP_SORT_DATATYPE_CHAR,
    APP_SORT_DATATYPE_STRING,
    APP_SORT_DATATYPE_STRUCT
};

enum
{
    APP_SORT_SORTTYPE_INSERTION,
    APP_SORT_SORTTYPE_BUBBLE,
    APP_SORT_SORTTYPE_SELECTION
};

typedef int DataType;
typedef size_t DataSize;
typedef int SortType;
static const int selector_sizes[] = {32, 64, 96};
static int selector_size_idx = 0; // Set default to 128
// static int selected_nb_elements = 32;

typedef struct AppData_s
{
    SortType thread1_sortType;
    SortType thread2_sortType;
    SortType thread3_sortType;
    SortType thread4_sortType;

    DataType arrayType;
    DataSize dataSize;
    unsigned int arraySize;

    unsigned int delay;

}AppData;

/// @brief Structure with all the general data
typedef struct App_s
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    TTF_Font     *font;

    bool app_running;
    bool sort_running;

    Logger *logger;
    Inputs *inputs;

    AppData *appData;

    /// @brief Light mode if true, Dark mode otherwise
    bool lightMode;
    Colors *colorSet;

    bool threadsRun;

    SDL_mutex* rendererUse;

    Mix_Chunk *button_sound;
    bool button_played;

    int selected_nb_elements;

    int threads_active;
    bool hold_final_frame;

    double SortA_time;
    double SortB_time;
    SDL_mutex *sortTime_mutex;
    Uint64 SortA_ticks_start;
    Uint64 SortB_ticks_start;
    bool   SortA_running;
    bool   SortB_running;

}App;

enum {
    APP_SCREEN_CONTINUE,
    APP_SCREEN_PASS,
    APP_SCREEN_QUIT
};


App* app_init(int LOG_LEVEL);
void app_play(App* app);
void app_quit(App* app);

int app_settingsScreen(App *app);
int app_visualizationScreen(App *app);

#endif