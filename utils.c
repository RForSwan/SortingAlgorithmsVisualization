#include "settings.h"

void utils_initializer()
{
    srand(time(NULL));
}

int* utils_createRandomIntArray(int size)
{
    int* array = calloc(size, sizeof(int));
    for(int i=0; i<size; i++){
        array[i] = rand() % size + 1;
    }
    return array;
}

void utils_destroyArray(Logger* logger, const unsigned int nb_elements, const size_t size, void* array, void (*destroy_Type)(void*))
{
    if(!array)
    {
        logger_log(logger, LOG_LEVEL_WARNING, "utils_destroyArray : Array is NULL, nothing to free");
        return;
    }

    if(destroy_Type)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            destroy_Type(array + (i * size));
        }
    }
    free(array);

    logger_log(logger, LOG_LEVEL_INFO, "utils_destroyArray : Array freed successfully");
}

void* utils_createUniformRandomArray(Logger* logger, const unsigned int nb_elements, const size_t size, void (*random_GenAndAssign_Type)(void*))
{
    void* array = calloc(nb_elements, size);

    if(!array)
    {
        logger_log(logger, LOG_LEVEL_ERROR, "utils_createUniformRandomArray : Failed allocating memory");
        return NULL;
    }

    for(int i = 0; i < nb_elements; i++)
    {
        random_GenAndAssign_Type(array + (i * size));
    }

    return array;
}

void utils_random_GenAndAssign_int(void* element)
{
    *(int*)element = rand() % 100 + 1;
}

void utils_random_GenAndAssign_float(void* element)
{
    *(float*)element = (float)(rand() % 100 + 1) / 10.0f;
}

void* utils_createSortedArray(Logger* logger, const unsigned int nb_elements, const size_t size, void (*sorted_GenAndAssign_Type)(void*, void*))
{
    void* array = calloc(nb_elements, size);

    if(!array)
    {
        logger_log(logger, LOG_LEVEL_ERROR, "utils_createSortedArray : Failed allocating memory");
        return NULL;
    }

    for(int i = 0; i < nb_elements; i++)
    {
        sorted_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size));
    }

    return array;
}

void utils_sorted_GenAndAssign_int(void* previous, void* element)
{
    if(previous == NULL) *(int*)element = 1;
    else *(int*)element = (*(int*)previous) + 1;
}

void utils_sorted_GenAndAssign_float(void* previous, void* element)
{
    if(previous == NULL) *(float*)element = 0.1f;
    else *(float*)element = (*(float*)previous) + 0.1f;
}