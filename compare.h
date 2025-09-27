#ifndef _COMPARE_H_
#define _COMPARE_H_

enum {
    COMPARE_ERROR   = -2,
    COMPARE_LESS    = -1,
    COMPARE_EQUAL   =  0,
    COMPARE_GREATER =  1,
};

/// @brief Compare two ints
/// @param logger used to enable logging
/// @param a first value
/// @param b second value
/// @return COMPARE_ERROR if failed to execute function
/// @return COMPARE_LESS if a is less than b
/// @return COMPARE_EQUAL if a is equal to b
/// @return COMPARE_GREATER if a is greater than b
int compare_int   (Logger* logger, const void* a, const void* b);

/// @brief Compare two floats
/// @param logger used to enable logging
/// @param a first value
/// @param b second value
/// @return COMPARE_ERROR if failed to execute function
/// @return COMPARE_LESS if a is less than b
/// @return COMPARE_EQUAL if a is equal to b
/// @return COMPARE_GREATER if a is greater than b
int compare_float (Logger* logger, const void* a, const void* b);

/// @brief Compare two strings
/// @param logger used to enable logging
/// @param a first value
/// @param b second value
/// @return COMPARE_ERROR if failed to execute function
/// @return COMPARE_LESS if a is less than b
/// @return COMPARE_EQUAL if a is equal to b
/// @return COMPARE_GREATER if a is greater than b
int compare_string(Logger* logger, const void* a, const void* b);

#endif