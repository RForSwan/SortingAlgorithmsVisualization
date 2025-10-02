#ifndef _SORTING_H_
#define _SORTING_H_

///// INCLUDES /////


///// SORTING ALGORITHMS /////

void test_sort1(App* app, const unsigned int nb_elements, const size_t size, void* array, int (*compare_func)(Logger* logger, const void* data_a, const void* data_b));
void test_sort2(App* app, const unsigned int nb_elements, const size_t size, void* array, int (*compare_func)(Logger* logger, const void* data_a, const void* data_b));

void insertion_sort(App *app, int arr[], int n);
void bubble_sort(App *app, int arr[], int n);
void selection_sort(App *app, int arr[], int n);

#endif
