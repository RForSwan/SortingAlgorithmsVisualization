#include "settings.h"


// int thread_func(void* data)
// {
//     ThreadData threadData = *(ThreadData*) data;
//     logger_log(threadData.app->logger, LOG_LEVEL_INFO, "thread_func : Thread nb %d is launched", threadData.ID);
//     threadData.sorting_algorithm(threadData.app, threadData.nb_elements, threadData.data_size, threadData.array, threadData.compare_func);
//
// }

int thread_func(void* data)
{
    if (data == NULL) {
        // Rien à faire si pas d'info
        return -1;
    }

    ThreadData *threadData = (ThreadData*)data;
    App *app = threadData->app;

    // Log de lancement
    if (threadData->app && threadData->app->logger) {
        logger_log(threadData->app->logger, LOG_LEVEL_INFO, "thread_func : Thread nb %d is launched", threadData->ID);
    }

    // Protection basique : vérifier pointeurs nécessaires
    if (!threadData->sorting_algorithm || !threadData->app || !threadData->array) {
        if (threadData->app && threadData->app->logger)
            logger_log(threadData->app->logger, LOG_LEVEL_ERROR, "thread_func : invalid thread parameters");
        // On libère la structure si elle a été mallocée par le créateur (convention)
        free(threadData);
        return -1;
    }

    // set start tick + running flag
    Uint64 t0 = SDL_GetPerformanceCounter();
    if (app->sortTime_mutex) SDL_mutexP(app->sortTime_mutex);
    if (threadData->ID == 0) {
        app->SortA_running = true;
        app->SortA_ticks_start = t0;
    } else if (threadData->ID == 1) {
        app->SortB_running = true;
        app->SortB_ticks_start = t0;
    }
    if (app->sortTime_mutex) SDL_mutexV(app->sortTime_mutex);


    // Appel de l'algorithme (bloquant jusqu'à la fin)
    threadData->sorting_algorithm(threadData->app,
                                  threadData->nb_elements,
                                  threadData->data_size,
                                  threadData->array,
                                  threadData->compare_func);

    // compute and store final elapsed, clear running
    Uint64 t1 = SDL_GetPerformanceCounter();
    double elapsed_ms = (double)(t1 - t0) * 1 / (double)SDL_GetPerformanceFrequency(); // 1000 FOR MS

    if (app->sortTime_mutex) SDL_mutexP(app->sortTime_mutex);
    if (threadData->ID == 0) {
        app->SortA_time = elapsed_ms;
        app->SortA_running = false;
    } else if (threadData->ID == 1) {
        app->SortB_time = elapsed_ms;
        app->SortB_running = false;
    }
    if (app->sortTime_mutex) SDL_mutexV(app->sortTime_mutex);

    if (threadData->nb_elements > 0 && threadData->array != NULL && app != NULL) {
        int *int_array = (int*)threadData->array;
        if (threadData->ID == 0) {
            visual_replay_sorted(app, int_array, threadData->nb_elements, draw_barsA);
        } else if (threadData->ID == 1) {
            visual_replay_sorted(app, int_array, threadData->nb_elements, draw_barsB);
        } else {
            visual_replay_sorted(app, int_array, threadData->nb_elements, draw_barsC);
        }
    }

    // Libération de la structure ThreadData (convention : créateur a fait malloc)
    //  free(threadData);

    return 0;
}