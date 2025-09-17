#ifndef _UTILS_H_
#define _UTILS_H_

///// INCLUDES /////

#include "logger.h"

///// UTILS /////

enum {
    SORTED_RANDOM,
    SORTED_INCREASING,
    SORTED_DECREASING,
    SORTED_PYRAMID,
    SORTED_NEARLY
};

void  utils_initializer();

int*  utils_createRandomIntArray(int size);

void utils_destroyArray(Logger* logger, const unsigned int nb_elements, const size_t size, void* array, void (*destroy_Type)(void*));

void* utils_createSortedArray(Logger* logger, const unsigned int nb_elements, const size_t size, int SortingType, void (*sorted_GenAndAssign_Type)(void*, void*, int));

void  utils_sorted_GenAndAssign_int(void* previous, void* element, int SortingType);
void  utils_sorted_GenAndAssign_float(void* previous, void* element, int SortingType);

#endif
