#ifndef _UTILS_H_
#define _UTILS_H_

///// INCLUDES /////

#include "logger.h"

///// UTILS /////

void  utils_initializer();

int*  utils_createRandomIntArray(int size);

void utils_destroyArray(Logger* logger, const unsigned int nb_elements, const size_t size, void* array, void (*destroy_Type)(void*));

void* utils_createUniformRandomArray(Logger* logger, const unsigned int nb_elements, const size_t size, void (*randomType_GenAndAssign)(void*));

void  utils_random_GenAndAssign_int(void* element);
void  utils_random_GenAndAssign_float(void* element);

void* utils_createSortedArray(Logger* logger, const unsigned int nb_elements, const size_t size, bool isReversed, void (*sorted_GenAndAssign_Type)(void*, void*, bool));

void  utils_sorted_GenAndAssign_int(void* previous, void* element, bool isReversed);
void  utils_sorted_GenAndAssign_float(void* previous, void* element, bool isReversed);

#endif
