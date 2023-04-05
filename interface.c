#include "interface.h"
#include "scheduler.h"

// Interface implementation
void init_scheduler(int thread_count) {
    // TODO: Implement this
    thread_head = (threadControl*)malloc(sizeof(threadControl));
    thread_tail = (threadControl*)malloc(sizeof(threadControl));
    inscheduler = 0;
    global_time = 0;
    totalthreads = thread_count;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    
}

int cpu_me(float current_time, int tid, int remaining_time) {
    // TODO: Implement this
    if (remaining_time == 0){
        return global_time;
    }
    pthread_mutex_lock(&mut);
    int t;
    pthread_cond_t *c;
    srtf_add(current_time,tid,remaining_time);
    if (inscheduler == totalthreads){
        t = choose();
        pthread_cond_t *cn = getlock(t);
        pthread_cond_signal(cn);
        //wake(t);
    }
    while (inscheduler < totalthreads || choose() != tid){
        c = getlock(tid);
        pthread_cond_wait(c, &mut);
    }
    if (global_time == 0){
        global_time = (int) current_time;
    }
    if (remaining_time > 0){
        global_time += 1;
    }
    pthread_mutex_unlock(&mut);
    int out = global_time;
    return out;
}

int io_me(float current_time, int tid, int device_id) {
    // TODO: Implement this
    return 0;
}

void end_me(int tid) {
    int a = rem(tid);
    totalthreads -= 1;
    inscheduler -= 1;
    if(totalthreads == 0){
        return;
    }
    int t = choose();
    wake(t);
    return;
    // TODO: Implement this
}
