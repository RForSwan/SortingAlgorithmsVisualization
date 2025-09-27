#include "settings.h"


int thread_func(void* data)
{
    ThreadData threadData = *(ThreadData*) data;
    logger_log(threadData.app->logger, LOG_LEVEL_INFO, "thread_func : Thread nb %d is launched", threadData.ID);
    threadData.sorting_algorithm(threadData.app, threadData.nb_elements, threadData.data_size, threadData.array);

}