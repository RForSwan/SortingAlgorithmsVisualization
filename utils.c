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


void utils_random_GenAndAssign_int(void* element)
{

}

void utils_random_GenAndAssign_float(void* element)
{

}

void* utils_createSortedArray(Logger* logger, const unsigned int nb_elements, const size_t size, int SortingType, void (*sorted_GenAndAssign_Type)(void*, void*, int))
{
    void* array = calloc(nb_elements, size);

    if(!array)
    {
        logger_log(logger, LOG_LEVEL_ERROR, "utils_createSortedArray : Failed allocating memory");
        return NULL;
    }

    if(SortingType == SORTED_RANDOM)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            sorted_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_INCREASING)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            sorted_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_DECREASING)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            sorted_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_PYRAMID)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            sorted_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), i< nb_elements/2 ? SORTED_INCREASING : SORTED_DECREASING);
        }
    }
    else if ( SortingType == SORTED_NEARLY)
    {
        return NULL;
    }
    else
    {
        logger_log(logger, LOG_LEVEL_ERROR, "utils_createSortedArray : Unknown SortingType %d", SortingType);
        free(array);
        return NULL;
    }


    return array;
}

void utils_sorted_GenAndAssign_int(void* previous, void* element, int SortingType)
{
    int min = 0, max = 100, step = 1;
    if (SortingType == SORTED_RANDOM)
    {
        *(int*)element = rand() % max + min + 1;
    }
    else if (SortingType == SORTED_INCREASING)
    {
        if(previous == NULL) *(int*)element = min;
        else                 *(int*)element = (*(int*)previous) + step;
    }
    else if (SortingType == SORTED_DECREASING)
    {
        if(previous == NULL) *(int*)element = max;
        else                 *(int*)element = (*(int*)previous) - step;
    }
}

void utils_sorted_GenAndAssign_float(void* previous, void* element, int SortingType )
{
    float min = 0, max = 100, step = 0.1f;
    if (SortingType == SORTED_RANDOM)
    {
        *(float*)element = (float)rand()/(float)(RAND_MAX/max);
    }
    else if (SortingType == SORTED_INCREASING)
    {
        if(previous == NULL) *(float*)element = min;
        else                 *(float*)element = (*(int*)previous) + step;
    }
    else if (SortingType == SORTED_DECREASING)
    {
        if(previous == NULL) *(float*)element = max;
        else                 *(float*)element = (*(int*)previous) - step;
    }
}