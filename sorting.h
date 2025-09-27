#ifndef _SORTING_H_
#define _SORTING_H_

///// INCLUDES /////


///// SORTING ALGORITHMS /////

void test_sort1(App* app, const unsigned int nb_elements, const size_t size, void* array);
void test_sort2(App* app, const unsigned int nb_elements, const size_t size, void* array);

void insertion_sort(SDL_Renderer *renderer, int arr[], int n);
void bubble_sort(SDL_Renderer *renderer, int arr[], int n);
void selection_sort(SDL_Renderer *renderer, int arr[], int n);

#endif
