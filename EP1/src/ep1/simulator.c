#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sched.h>
#include <sys/time.h>
#include <float.h>
#include "../../include/ep1/types.h"
#include "../../include/ep1/heap.h"
#include "../../include/ep1/read_file.h"
#include "../../include/ep1/rrqueue.h"

#define SIZE_LOT 10
#define QUANTUM 5.0
pthread_mutex_t lock;

void* processing (void *args) {
    pthread_mutex_lock(&lock);
    arg_thread* argv = (arg_thread*) args;

    if (argv->details == 1) {
    	fprintf(stderr, "The current process is: %s\n",argv->p->name);
    	fprintf(stderr, "The current CPU being used is: %d\n",sched_getcpu());
    	printf("\n");
    }


    struct timespec ts = argv->ts;
    
    nanosleep(&ts, NULL);
    
    pthread_mutex_unlock(&lock);
    return argv;
}

struct timespec convert_ts (double dt) {
    struct timespec ts;
    ts.tv_sec = floor(dt);
    ts.tv_nsec = (dt - ts.tv_sec)*1e9;
    return ts;
}

double sec (struct timespec ts) {
    return round((ts.tv_sec + (ts.tv_nsec * 1e-9))*10)/10;
}

void write_file (FILE *f, char *pr_name, double tf, double tr) {
	fprintf(f, "%s %.1lf %.1lf\n", pr_name, tf, tr);
}

//Shortest Job First
void SJF (FILE *trace_file, FILE *result, int details) {
    int ret, nb_process;
    double tf, tr;
    pthread_t main_thread;
  
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
            
            else if (sec(intF) - sec(start) <= plist[index]->times[0]) {
                plist[index]->times[3] = plist[index]->times[1];
                insert_heap(min_heap, plist[index]);
                index++; 
                i++;
            }
        }
        
        while (min_heap->pr_total > 0) {
            arg_thread* argv = malloc(sizeof(arg_thread));

            argv->p = remove_heap(min_heap);
            argv->ts = convert_ts(argv->p->times[3]);
            argv->details = details;

            struct timespec threadI, threadF;
            clock_gettime(CLOCK_REALTIME, &threadI);
            
            ret = pthread_create(&main_thread, NULL, &processing, (void*)argv);
            pthread_join(main_thread, NULL);
            
            clock_gettime(CLOCK_REALTIME, &threadF);
            
            tf = sec(threadF) - sec(start);
            tr = tf - (sec(threadI) - sec(start));
            write_file(result, argv->p->name, tf, tr);

            
            if (ret == -1) {
                perror("pthread_create exited with failure");
                exit(-1);
            }
            
            free(argv);
        }
    }
    pthread_mutex_destroy(&lock);    
}

//Each process is given a time interval (QUANTUM)
void Round_Robin (FILE *trace_file, FILE *result, int details) {
    int ret, nb_process, index, int_index, isWorth, context;
    double tf, tr, rel_runtime, abs_runtime, end, begin, start_time;
    pthread_t main_thread;
    struct timespec start, intI, intF, cur;
  
    process **plist = get_process(trace_file, &nb_process);
    rrqueue *q = init_rrqueue();
    
    index = int_index = context = 0;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    start_time = sec(start);


    while (index < nb_process) {
        isWorth = 1;

        clock_gettime(CLOCK_REALTIME, &intI);
        begin = sec(intI) - start_time;
        end = begin;

        rel_runtime = end - begin;
        while(index < nb_process && rel_runtime < 10.0 && isWorth) {
            abs_runtime = end;
            if (abs_runtime >= plist[index]->times[0]) {
                plist[index]->times[0] = abs_runtime;
                plist[index]->times[3] = plist[index]->times[1];
                insert_rrqueue(q, plist[index]);
                index++;
            }
            else if (index < nb_process) {
                if (plist[index]->times[0] - begin > 10) {
                    isWorth = 0;
                }
            }
            clock_gettime(CLOCK_REALTIME, &intF);
            end = sec(intF) - start_time;
            rel_runtime = end - begin;
        }
        printf("%.1lf\n", abs_runtime);
        int qsize = index - int_index;
        while (index != int_index && qsize) {
            arg_thread* argv = malloc(sizeof(arg_thread));

            argv->p = q->first->p;
            
            argv->ts = argv->p->times[3] < QUANTUM? 
                convert_ts(argv->p->times[3]) : convert_ts(QUANTUM);
            
            argv->details = details;

            ret = pthread_create(&main_thread, NULL, &processing, (void*)argv);
            pthread_join(main_thread, NULL);
            
            if (ret == -1) {
                perror("pthread_create exited with failure");
                exit(-1);
            }
 
            clock_gettime(CLOCK_REALTIME, &cur);

            q->first->p->times[3] -= QUANTUM;

            if (q->first->p->times[3] <= 0) {
                tf = sec(cur) - start_time;
                printf("t0 do %s: %.1lf\n", q->first->p->name, q->first->p->times[0]);
                tr = tf - q->first->p->times[0];
                write_file(result, q->first->p->name, tf, tr);
                remove_rrqueue(q);
                int_index++;
            }
            else {
                move_rrqueue(q);
                context++;
            }
            qsize--;
        }
    }
    pthread_mutex_destroy(&lock);    
}

//Each level of priority defines how much time the process receives 
void Priority (FILE *trace_file, FILE *result, int details) {
    int ret, nb_process, index, int_index, isWorth, context, hsize;
    double tf, tr, rel_runtime, abs_runtime, end, begin, start_time;
    pthread_t main_thread;
    struct timespec start, intI, intF, cur;
  
    process **plist = get_process(trace_file, &nb_process);
    heap* min_heap = init_heap(nb_process);
    
    index = int_index = context = 0;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    start_time = sec(start);

    while (index < nb_process) {
        isWorth = 1;

        clock_gettime(CLOCK_REALTIME, &intI);
        begin = sec(intI) - start_time;
        end = begin;

        rel_runtime = end - begin;
        while(index < nb_process && rel_runtime < 10.0 && isWorth) {
            abs_runtime = end;
            if (abs_runtime >= plist[index]->times[0]) {
                plist[index]->times[0] = abs_runtime;
                plist[index]->times[3] = plist[index]->times[2] 
                    - abs_runtime - plist[index]->times[1];
                insert_heap(q, plist[index]);
                index++;
            }
            else if (index < nb_process) {
                if (plist[index]->times[0] - begin > 10) {
                    isWorth = 0;
                }
            }
            clock_gettime(CLOCK_REALTIME, &intF);
            end = sec(intF) - start_time;
            rel_runtime = end - begin;
        }

        hsize = index - int_index;
        while (index != int_index && hsize) {
            arg_thread* argv = malloc(sizeof(arg_thread));

            argv->p = remove_heap(heap);

            argv->ts = argv->p->times[1] < hsize*QUANTUM? 
                convert_ts(argv->p->times[1]) :
                convert_ts(hsize * QUANTUM);

            argv->details = details;

            ret = pthread_create(&main_thread, NULL, &processing, (void*)argv);
            pthread_join(main_thread, NULL);

            if (ret == -1) {
                perror("pthread_create exited with failure");
                exit(-1);
            }
 
            argv->p->times[1] -= (hsize) * QUANTUM;

            clock_gettime(CLOCK_REALTIME, &cur);

            if (q->first->p->times[1] <= 0) {
                tf = sec(cur) - start_time;
                printf("t0 do %s: %.1lf\n", q->first->p->name, q->first->p->times[0]);
                tr = tf - q->first->p->times[0];
                write_file(result, q->first->p->name, tf, tr);
                int_index++;
            }
            else {
                move_rrqueue(q);
                context++;
                argv->p->times[3] = DBL_MAX;
                insert_heap(h, argv->p)
            }
            hsize--;
        }

        hsize = index - int_index;
        clock_gettime(CLOCK_REALTIME, &intF);
        end = sec(intF) - start_time;

        for (int i = index - int_index; i < 0; i--) {
            min_heap->min_pq[i]->times[3] = min_heap->min_pq[i]->times[2] 
                - abs_runtime - min_heap->min_pq[i]->times[1];
            
        }
    }
    pthread_mutex_destroy(&lock);    

}

int main (int argc, char **argv) {

    FILE* fl_input = fopen(argv[2], "r");
    FILE* fl_result = fopen(argv[3], "w");
    int d;

    if (argc == 5 && *argv[4] == 'd') d = 1;
    else d = 0;
 
    if (*argv[1] == '1') SJF(fl_input, fl_result, d);
    else if (*argv[1] == '2') Round_Robin(fl_input, fl_result, d);
    else Priority(fl_input, fl_result, d);

    return 0;
}
