#ifndef _THREAD_H_
#define _THREAD_H_

///// INCLUDES /////


///// THREADS /////

#define NB_THREADS 4

typedef unsigned int ThreadID;

typedef struct ThreadData_s
{
    ThreadID ID;

    App *app;

    /// @brief number of elements inside the array
    const unsigned int nb_elements;

    /// @brief array to sort
    void* array;

    /// @brief size of the individual data inside the array
    const size_t data_size;

    /// @brief function used to compare
    /// @param logger
    /// @param data_a
    /// @param data_b
    int (*compare_func)(Logger* logger, const void* data_a, const void* data_b);

    void (*sorting_algorithm)(App* app, const unsigned int nb_elements, const size_t size, void* array, int (*compare_func)(Logger* logger, const void* data_a, const void* data_b));

} ThreadData;

int thread_func(void* data);


#endif