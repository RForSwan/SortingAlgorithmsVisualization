#ifndef _UTILS_H_
#define _UTILS_H_

///// INCLUDES /////

#include "logger.h"

///// UTILS /////

enum {
    SORTED_RANDOM,
    SORTED_INCREASING,
    SORTED_INCREASING_RANDOM,
    SORTED_DECREASING,
    SORTED_DECREASING_RANDOM,
    SORTED_PYRAMID,
    SORTED_PYRAMID_RANDOM,
    SORTED_NEARLY
};

#define NB_CHARACTERS 63
static const char characters[NB_CHARACTERS] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";

void  utils_initializer();

int*  utils_createRandomIntArray(int size);

void  utils_destroyArray(Logger* logger, const unsigned int nb_elements, const size_t size, void* array, void (*destroy_Type)(void*));
void* utils_copyArray(Logger* logger, const unsigned int nb_elements, const size_t size, const void* const originalArray);
void* utils_createArray(Logger* logger, const unsigned int nb_elements, const size_t size, int SortingType, void (*utils_GenAndAssign_Type)(void*, void*, int));

void  utils_GenAndAssign_int(void* previous, void* element, int SortingType);
void  utils_GenAndAssign_float(void* previous, void* element, int SortingType);
void  utils_GenAndAssign_string(void* previous, void* element, int SortingType);
void  utils_GenAndAssign_char(void* previous, void* element, int SortingType);

#endif
