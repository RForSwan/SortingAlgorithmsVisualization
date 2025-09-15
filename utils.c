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