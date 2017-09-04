#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "../../include/ep1/types.h"
#include "../../include/ep1/heap.h"
#include "../../include/ep1/read_file.h"
#include "../../include/ep1/rrqueue.h"

#define SIZE_LOT 10
#define QUANTUM 5
pthread_mutex_t lock;

void* processing (void *pr) {
    pthread_mutex_lock(&lock);
    
    struct timespec ts;
    process *p = (process*) pr;
    
    double dt = p->times[1];
    ts.tv_sec = floor(dt);
    ts.tv_nsec = (dt - ts.tv_sec)*1e9;
    
    nanosleep(&ts, NULL);
    
    pthread_mutex_unlock(&lock);
    return pr;
}

double sec (struct timespec ts) {
    return round((ts.tv_sec + (ts.tv_nsec * 1e-9))*10)/10;
}

//Shortest Job First
void SJF (FILE *trace_file, char *result) {
    int ret, nb_process;
    pthread_t main_thread;
    process *p = NULL;
  
    process **plist = get_process(trace_file, &nb_process);
    heap *min_heap = init_heap(nb_process);
    
    struct timespec start, intI, intF;
    int index = 0;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    while (index < nb_process) {
        clock_gettime(CLOCK_REALTIME, &intI);

        for (int i = 0; i < 10 && index < nb_process;) {
            clock_gettime(CLOCK_REALTIME, &intF);
            if (sec(intF) - sec(intI) > 10.0) break;
            
            if (sec(intF) - sec(start) >= plist[index]->times[0]) {
                plist[index]->times[3] = plist[index]->times[1];
                insert_heap(min_heap, plist[index]);
                index++; 
                i++;
            }
        }
        
        while (min_heap->pr_total > 0) {
            p = remove_heap(min_heap);        
            
            struct timespec threadI, threadF;
            clock_gettime(CLOCK_REALTIME, &threadI);
            
            ret = pthread_create(&main_thread, NULL, &processing, (void*)p);
            pthread_join(main_thread, NULL);
            
            clock_gettime(CLOCK_REALTIME, &threadF);
            printf("%lf | %lf\n", sec(threadF), sec(threadI));
            
            if (ret == -1) {
                perror("pthread_create exited with failure");
                exit(-1);
            }
            
            free(p);
        }
    }
    pthread_mutex_destroy(&lock);    
}

//Each process is given a time interval (QUANTUM)
void Round_Robin (FILE *trace_file, char *result) {
    int ret, nb_process;
    pthread_t main_thread;
    process *p = NULL;
  
    process **plist = get_process(trace_file, &nb_process);
    rrqueue *q = init_rrqueue();
    
    struct timespec start, end, cur;
    int index = 0, int_index = 0;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    while (index < nb_process) {
        
        clock_gettime(CLOCK_REALTIME, &cur);
        double runtime = sec(cur) - sec(start);
        int isWorth = 1;

        while(index < nb_process && runtime > 10.0 && isWorth) {
            if (runtime >= plist[index]->times[0]) {
                plist[index]->times[0] = runtime;
                plist[index]->times[3] = plist[index]->times[1];
                insert_rrqueue(q, plist[index]);
                index++;
            }
            else if (index < nb_process) {
                if (plist[index]->times[0] - runtime > 10) {
                    isWorth = 0;
                }
            }
        }

        while (index != int_index) {
            //execução da thread
 
            if (ret == -1) {
                perror("pthread_create exited with failure");
                exit(-1);
            }
 
            clock_gettime(CLOCK_REALTIME, &cur);
            q->first->p->times[3] -= QUANTUM;
 
            if (q->first->p->times[3] <= 0) {
                q->first->p->times[4] = sec(cur) - sec(start);
                q->first->p->times[3] = q->first->p->times[4] - q->first->p->times[0];
                //fprintf
                remove_rrqueue(q);
                nb_process--;
                int_index++;
            }
            else {
                move_rrqueue(q);
            }
        }
    }
    pthread_mutex_destroy(&lock);    
}

//Each level of priority defines how much time the process receives 
void Priority (FILE *trace_file, char *result) {

}

int main (int argc, char **argv) {

    FILE* fl_name = fopen (argv[2], "r");
 
    if (*argv[1] == '1') SJF(fl_name, argv[3]);
    else if (*argv[1] == '2') Round_Robin(fl_name, argv[3]);
    else Priority(fl_name, argv[3]);

    return 0;
}
