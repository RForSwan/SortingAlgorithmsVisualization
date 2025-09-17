#include "settings.h"

thrd_t* thread_create(Logger* logger, int nb_threads) {
    thrd_t* thread_array = calloc(NB_THREADS, sizeof(thrd_t));
    for(int i = 0; i < nb_threads; i++) {
        if (thrd_create(&thread_array[i], NULL, NULL) != thrd_success) {
            logger_log(logger, LOG_LEVEL_FATAL, "Creating thread %d", i);
            free(thread_array);
            return NULL;
        }
    }


    return thread_array;
}

void thread_destroy(thrd_t* threads, int nb_threads) {
    for(int i = 0; i < nb_threads; i++) {
        return;
    }
}

void thread_join(int thread_id) {

}

