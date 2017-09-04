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

void write_file (FILE *f, char *pr_name, double tf, double tr) {
	fprintf(f, "%s %lf %lf\n", pr_name, tf, tr);
}

//Shortest Job First
void SJF (FILE *trace_file, FILE *result) {
    int ret, nb_process;
    double tf, tr;
    pthread_t main_thread;
    process *p = NULL;
  
    process **plist = get_process(trace_file, &nb_process);
    heap *min_heap = init_heap(nb_process);
    
    struct timespec start, intI, intF;
    clock_gettime(CLOCK_REALTIME, &start);
    int index = 0;
    pthread_mutex_init(&lock, NULL);

    while (index < nb_process) {
        clock_gettime(CLOCK_REALTIME, &intI);

        for (int i = 0; i < 10 && index < nb_process; i++) {
            clock_gettime(CLOCK_REALTIME, &intF);
            if (sec(intF) - sec(intI) > 10.0) break;

            plist[index]->times[3] = plist[index]->times[1];
            
            insert_heap(min_heap, plist[index]);
            index++;
        }
        
        while (min_heap->pr_total > 0) {
            p = remove_heap(min_heap);        
            
            struct timespec threadI, threadF;
            clock_gettime(CLOCK_REALTIME, &threadI);
            
            ret = pthread_create(&main_thread, NULL, &processing, (void*)p);
            pthread_join(main_thread, NULL);
            
            clock_gettime(CLOCK_REALTIME, &threadF);
            
            tf = sec(threadF);
            tr = (start - sec(threadI)) - tf;
            write_file(result, p->name, tf, tr);
            
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
void Round_Robin (FILE *trace_file, FILE *result) {
    int ret, nb_process;
    pthread_t main_thread;
    process *p = NULL;
  
    process **plist = get_process(trace_file, &nb_process);
    rrqueue *q = init_rrqueue(nb_process);
    
    struct timespec start, intI, intF;
    clock_gettime(CLOCK_REALTIME, &start);
    int index = 0;
    pthread_mutex_init(&lock, NULL);

    while (index < nb_process) {
        for (int i = 0; index < nb_process; i++) {

            plist[index]->times[3] = plist[index]->times[1];
            
            insert_rrqueue(q, plist[index]);
            index++;
        }
        
        while (min_heap->pr_total > 0) {
            p = delMin(min_heap);        
            
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

//Each level of priority defines how much time the process receives 
void Priority (FILE *trace_file, FILE *result) {

}

int main (int argc, char **argv) {

    FILE* fl_input = fopen(argv[2], "r");
    FILE* fl_result = fopen(argv[3], "w"); 
 
    if (*argv[1] == '1') SJF(fl_input, fl_result);
    else if (*argv[1] == '2') Round_Robin(fl_input, fl_result);
    else Priority(fl_input, fl_result);

    return 0;
}
