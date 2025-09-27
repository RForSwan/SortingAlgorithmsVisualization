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

void* utils_copyArray(Logger* logger, const unsigned int nb_elements, const size_t size, const void* const originalArray){
    logger_log(logger, LOG_LEVEL_INFO, "utils_copyArray, copying array at %p",originalArray);
    void* newArray = calloc(nb_elements, size);
    for(int i = 0; i < nb_elements; i++)
    {
        memcpy(newArray + (i * size), originalArray + (i * size), size);
    }
    return newArray;
}


void* utils_createArray(Logger* logger, const unsigned int nb_elements, const size_t size, int SortingType, void (*utils_GenAndAssign_Type)(void*, void*, int))
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
            utils_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_INCREASING || SortingType == SORTED_INCREASING_RANDOM)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            utils_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_DECREASING || SortingType == SORTED_DECREASING_RANDOM)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            utils_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), SortingType);
        }
    }
    else if (SortingType == SORTED_PYRAMID || SortingType == SORTED_PYRAMID_RANDOM)
    {
        for(int i = 0; i < nb_elements; i++)
        {
            utils_GenAndAssign_Type(i==0 ? NULL : array + ((i - 1) * size), array + (i * size), i < (nb_elements / 2 + 1) ? SORTED_INCREASING : SORTED_DECREASING);
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

void utils_GenAndAssign_int(void* previous, void* element, int SortingType)
{
    int min = 0, max = 100, step = 1, rand_range = 10;
    if (SortingType == SORTED_RANDOM)
    {
        *(int*)element = rand() % max + min;
    }
    else if (SortingType == SORTED_INCREASING)
    {
        if(previous == NULL) *(int*)element = min;
        else                 *(int*)element = (*(int*)previous) + step;
    }
    else if (SortingType == SORTED_INCREASING_RANDOM)
    {
        if(previous == NULL) *(int*)element = min;
        else                 *(int*)element = (*(int*)previous) + (rand() % rand_range);
    }
    else if (SortingType == SORTED_DECREASING)
    {
        if(previous == NULL) *(int*)element = max;
        else                 *(int*)element = (*(int*)previous) - step;
    }
    else if (SortingType == SORTED_DECREASING_RANDOM)
    {
        if(previous == NULL) *(int*)element = max;
        else                 *(int*)element = (*(int*)previous) - (rand() % rand_range);
    }
}

void utils_GenAndAssign_float(void* previous, void* element, int SortingType )
{
    float min = 0, max = 100, step = 0.1f, rand_range = 1;
    if (SortingType == SORTED_RANDOM)
    {
        *(float*)element = (float)rand()/(float)(RAND_MAX/max);
    }
    else if (SortingType == SORTED_INCREASING)
    {
        if(previous == NULL) *(float*)element = min;
        else                 *(float*)element = (*(float*)previous) + step;
    }
    else if (SortingType == SORTED_INCREASING_RANDOM)
    {
        if(previous == NULL) *(float*)element = min;
        else                 *(float*)element = (*(float*)previous) + ((float)rand() / (float)(RAND_MAX / rand_range));
    }
    else if (SortingType == SORTED_DECREASING)
    {
        if(previous == NULL) *(float*)element = max;
        else                 *(float*)element = (*(float*)previous) - step;
    }
    else if (SortingType == SORTED_DECREASING_RANDOM)
    {
        if(previous == NULL) *(float*)element = max;
        else                 *(float*)element = (*(float*)previous) - ((float)rand() / (float)(RAND_MAX / rand_range));
    }
}

void utils_GenAndAssign_char(void* previous, void* element, int SortingType){
    int min = 0, max = NB_CHARACTERS, step = 1, rand_range = 2;
    if (SortingType == SORTED_RANDOM)
    {
        *(int*)element = characters[rand() % max + min];
    }
    else if (SortingType == SORTED_INCREASING)
    {
        if(previous == NULL) *(int*)element = min;
        else                 *(int*)element = (*(int*)previous) + step;
    }
    else if (SortingType == SORTED_INCREASING_RANDOM)
    {
        if(previous == NULL) *(int*)element = min;
        else                 *(int*)element = (*(int*)previous) + (rand() % rand_range);
    }
    else if (SortingType == SORTED_DECREASING)
    {
        if(previous == NULL) *(int*)element = max;
        else                 *(int*)element = (*(int*)previous) - step;
    }
    else if (SortingType == SORTED_DECREASING_RANDOM)
    {
        if(previous == NULL) *(int*)element = max;
        else                 *(int*)element = (*(int*)previous) - (rand() % rand_range);
    }
}

void utils_GenAndAssign_string(void* previous, void* element, int SortingType)
{
    int length = 10;
    if (SortingType == SORTED_RANDOM)
    {
        char* cast_element = (char*)calloc(length, sizeof(char));
        for(int i=0; i<length; i++)
        {
            cast_element[i] = characters[rand() % NB_CHARACTERS];
        }
        // cast_element[length-1] = '\0';
        *(char**)element = cast_element;

    }
    else if (SortingType == SORTED_INCREASING)
    {
        return;
    }
    else if (SortingType == SORTED_DECREASING)
    {
        return;
    }
}