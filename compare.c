#include "settings.h"



int compare_int(Logger* logger, const void* a, const void* b)
{
    if(!a || !b) {
        logger_log(logger, LOG_LEVEL_ERROR, "compare_int : NULL pointer");
        return COMPARE_ERROR;
    }

    int int_a = *(int*)a, int_b = *(int*)b;

    if      (int_a < int_b)  return COMPARE_LESS;
    else if (int_a == int_b) return COMPARE_EQUAL;
    else                     return COMPARE_GREATER;
}

int compare_float(Logger* logger, const void* a, const void* b)
{
    if(!a || !b) {
        logger_log(logger, LOG_LEVEL_ERROR, "compare_float : NULL pointer");
        return COMPARE_ERROR;
    }

    float float_a = *(float*)a, float_b = *(float*)b;

    if      (float_a < float_b)  return COMPARE_LESS;
    else if (float_a == float_b) return COMPARE_EQUAL;
    else                         return COMPARE_GREATER;
}

int compare_string(Logger* logger, const void* a, const void* b)
{
    if(!a || !b) {
        logger_log(logger, LOG_LEVEL_ERROR, "compare_string : NULL pointer");
        return COMPARE_ERROR;
    }

    char *string_a = (char*)a, *string_b = (char*)b;

    int res = strcmp(string_a, string_b);
    if      (res < 0)  return COMPARE_LESS;
    else if (res == 0) return COMPARE_EQUAL;
    else               return COMPARE_GREATER;
}