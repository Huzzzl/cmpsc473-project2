#include "scheduler.h"

// TODO: Add your function definitions here.
int srtf_add(float current_time, int tid, int remaining_time){
    pthread_cond_t *c = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
    pthread_cond_t con = PTHREAD_COND_INITIALIZER;
    c = &con;
    threadControl *temp = thread_head;
    threadControl *current = (threadControl*)malloc(sizeof(threadControl)); //thread control to be added
    current->current_time = current_time;
    current->tid = tid;
    current->remaining_time = remaining_time;
    current->cond = c;
    if(inscheduler == totalthreads){ //update
        while (temp){
            if (temp->tid == tid){
                temp->current_time = current_time;
                temp->remaining_time = remaining_time;
                temp->cond = c;
                return 0;
            }
            if (temp == thread_tail){
                return -1;
            }
            temp = temp->next;
        }
    }
    if(thread_head->next == NULL){// link is empty
        thread_head = current; 
        thread_tail = current;
        thread_head->next = thread_tail;
        inscheduler += 1;
        return 0;
    }
    else{
        /*threadControl *temp = thread_head;
        /*threadControl *prev = thread_head;
        if ((thread_head->current_time > current->current_time)||(thread_head->current_time == current->current_time && thread_head->remaining_time > current->remaining_time) ||
        (thread_head->current_time == current->current_time && thread_head->remaining_time == current->remaining_time && thread_head->tid > current->tid)){ //before head
            current->next = thread_head;
            thread_head = current;
            return;
        }
        while(temp){ //before temp
            if ((temp->current_time > current->current_time)||(temp->current_time == current->current_time && temp->remaining_time > current->remaining_time) ||
        (temp->current_time == current->current_time && temp->remaining_time == current->remaining_time && temp->tid > current->tid)){
                prev->next = current;
                current->next = temp;
                return;
            }
            if (temp == thread_tail){
                break;
            }
            temp = temp->next;
            prev = prev->next;
        }*/
        //not in link 
        thread_tail->next = current;
        thread_tail = current;
        inscheduler += 1;
        return 0;
    }
}


/*int gettime(int tid){ //get time for the choosen thread in link, return -1 when fail
    threadControl *temp = thread_head -> next;
    threadControl *prev = thread_head;
    int out = -1;
    if (thread_head->tid == tid){
        out = (int) thread_head->current_time + 1;
        return out;
    }
    while (temp){
        if (temp->tid == tid){
            out = (int) temp->current_time + 1;
            return out;
        }
        if(temp == thread_tail){
            break;
        }
        temp = temp->next;
    }
    return out;
}*/

int choose(void){
    threadControl *temp = thread_head;
    threadControl *choosen = thread_head;
    int min = (int)thread_head->current_time;
    while(temp){
        if ((int)temp->current_time < min){
            min = (int)temp->current_time;
        }
        if ((temp->current_time <= global_time && temp->remaining_time < choosen->remaining_time ) ||
        (temp->current_time <= global_time && temp->remaining_time == choosen->remaining_time && temp->tid < choosen->tid)){
            choosen = temp;
        }
        if (temp == thread_tail){
            break;
        }
        temp = temp->next;
    }
    if (choosen == thread_head && choosen->current_time > global_time){
        global_time = min;
        temp = thread_head;
        choosen = thread_head;
        while(temp){
            if ((int)temp->current_time < min){
                min = (int)temp->current_time;
            }
            if ((temp->current_time <= global_time && temp->remaining_time < choosen->remaining_time ) ||
            (temp->current_time <= global_time && temp->remaining_time == choosen->remaining_time && temp->tid < choosen->tid)){
                choosen = temp;
            }
            if (temp == thread_tail){
                break;
            }
            temp = temp->next;
        }
    }
    return choosen->tid;
}
/*int choose2(int tid){
    threadControl *temp = thread_head;
    threadControl *choosen = thread_head;
    if(thread_head->tid == tid){
        temp = temp->next;
        choosen = choosen->next;
    }
    while(temp){
        if ((temp->current_time <= global_time && temp->remaining_time < choosen->remaining_time && temp->tid != tid) ||
        (temp->current_time <= global_time && temp->remaining_time == choosen->remaining_time && temp->tid < choosen->tid && temp->tid != tid)){
            choosen = temp;
        }
        if (temp == thread_tail){
            break;
        }
        temp = temp->next;
    }
    return choosen->tid;
}*/

int wake(int tid){
    threadControl *temp = thread_head;
    while(temp){
        if(temp->tid == tid){
            pthread_cond_signal(temp->cond);
            return 0;
        }
        if (temp == thread_tail){
            break;
        }
        temp = temp->next;
    }
    return -1;
}

pthread_cond_t *getlock(int tid){
    threadControl *temp = thread_head;
    while(temp){
    if(temp->tid == tid){
            return temp->cond;
        }
        if (temp == thread_tail){
            break;
        }
        temp = temp->next;
    }
    return temp->cond;
}

int rem(int tid){
    threadControl *temp = thread_head->next;
    threadControl *prev = thread_head;
    if (prev->tid == tid){
        thread_head = thread_head->next;
        return 0;
    }
    while(temp){
        if(temp->tid == tid){
            prev->next = temp->next;
            return 0;
        }
        if (temp == thread_tail){
            break;
        }
        temp = temp->next;
        prev = prev->next;
    }
    return -1;

}