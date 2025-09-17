#ifndef _THREAD_H_
#define _THREAD_H_

///// INCLUDES /////


///// THREADS /////

#define NB_THREADS 4


thrd_t* thread_create(Logger* logger, int nb_threads);


#endif