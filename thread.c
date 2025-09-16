#include "setting.h"

void* thread_function(void* arg) {
    // Cast the argument to the appropriate type
    int* thread_id = (int*)arg;

    // Perform thread-specific tasks
    printf("Thread %d is running\n", *thread_id);

    // Simulate some work with sleep
    sleep(1);

    printf("Thread %d is done\n", *thread_id);
    return NULL;
}