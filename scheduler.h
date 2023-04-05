/*
 * Utilize "scheduler.h" and "scheduler.c" for all the utility functions students
 * intend to use for "interface.c".
 */
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>

#include "interface.h"



#endif
int global_time;
int inscheduler;
int totalthreads;
pthread_mutex_t mut;



typedef struct threadControler {
    float current_time;
    int tid;
    int remaining_time;
    pthread_cond_t *cond;
    struct threadControler *next;
}threadControl;

threadControl *thread_head;
threadControl *thread_tail;

extern int srtf_add(float current_time, int tid, int remaining_time);
//extern int gettime(int tid);
extern int choose(void);
//extern int choose2(int tid);
extern int wake(int tid);
extern pthread_cond_t* getlock(int tid);
extern int rem(int tid);