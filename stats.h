#ifndef _STATS_H_
#define _STATS_H_

///// INCLUDES /////


///// STATS /////

typedef struct Stats_s{
    time_t executionTime;
    int nb_memoryAccess;
    int nb_comparisons;
}Stats;

#endif
