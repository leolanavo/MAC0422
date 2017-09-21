/* Implements three schedulers SJF, RR and Priority. */

#define _GNU_SOURCE

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
#include "../../include/ep1/write_file.h"

#define SIZE_LOT 10
#define QUANTUM 5.0
#define TIME_LIMIT 5.0

//ID of which escalonator
#define SJFID 1
#define RRID 2
#define PRID 3

pthread_mutex_t lock;

/* Receives a void* which has a process, a timespec and a flag.
 * Consumes the time specified in the timespec variable, and prints
 * th necessary info if the flag is different from zero. */
void* processing (void *args) {
    pthread_mutex_lock(&lock);
    arg_thread* argv = (arg_thread*) args;
    int cpu = sched_getcpu();

    if (argv->details) {
    	fprintf(stderr, "The current process is: %s\n",argv->p->name);
    	fprintf(stderr, "The current CPU being used is: %d\n",cpu);
    	printf("\n");
    }

    struct timespec ts = argv->ts;    
    nanosleep(&ts, NULL);

    if (argv->details) {
    	fprintf(stderr, "The process freeing the CPU is: %s\n",argv->p->name);
    	fprintf(stderr, "CPU being freed is: %d\n",cpu);
    	printf("\n");
    }
    
    pthread_mutex_unlock(&lock);
    return argv;
}

/* Receives a double.  Returns the double structered as a timespec. */
struct timespec convert_ts (double dt) {
    struct timespec ts;
    ts.tv_sec = floor(dt);
    ts.tv_nsec = (dt - ts.tv_sec)*1e9;
    return ts;
}

/* Receives a timespec struct. Returns the timespec 
 * converted into a double with one decimal place of precision*/
double sec (struct timespec ts) {
    return round((ts.tv_sec + (ts.tv_nsec * 1e-9))*10)/10;
}

/* Receives a process pointer, a void pointer (which is a data structere), 
 * an id (identifies the scheduler), and a double (the runtime of the
 * scheduling). Inserts the process in the structere and calculates its 
 * priority according to the scheduler. */
void insert_process(process* p, void* s, int id, double abs_runtime) {
    p->times[3] = id == PRID? 
        p->times[2] - abs_runtime - p->times[1] : p->times[1];

    if (id == SJFID || id == PRID)
        insert_heap((heap*) s, p);
    else
        insert_rrqueue((rrqueue*) s, p);  
}

arg_thread* construct_argv(int id, void* s, double exec_time, int details) {
    arg_thread* argv = malloc(sizeof(arg_thread));
    
    argv->p = id == RRID? ((rrqueue*)s)->first->p : remove_heap((heap*) s);

    argv->ts = argv->p->times[1] < exec_time? 
        convert_ts(argv->p->times[1]) : convert_ts(exec_time);
    
    argv->details = details;
    return argv;
}

/* Receives a process pointer array, a void pointer, an int, the starting time
 * of the scheduler, the number of process in the array, the index of the array,
 * the line of the file, and a flag.
 *
 * Makes a loop of 10 seconds, or less in the case of SJF, and inseserts the
 * process which already entered the CPU in the structere.
 * 
 * Prints the necessary information with the flag is non-zero.
 * 
 * NOTE: in the variable names, int stands for interval. 
 * NOTE2: the arguments are the same from insert_process function. */
void insert_loop(process** plist, void* s, int id, double start_time, int nb_process,
                int* index, int* tr_line, int details) {
    
    int i = 0;
    struct timespec intI, intF;
    double abs_runtime, int_runtime, begin, end;
    
    clock_gettime(CLOCK_REALTIME, &intI);
    begin = sec(intI) - start_time;
    end = begin;
    int_runtime = end - begin;

    while (*(index) < nb_process && int_runtime < TIME_LIMIT) {
        abs_runtime = end;

        if (id == SJFID && i >= SIZE_LOT) return;

        if (abs_runtime >= plist[*(index)]->times[0]) {
            insert_process(plist[*(index)], s, id, abs_runtime);

            if (details) {
                trace_line(plist[*(index)]->name, *(tr_line), abs_runtime);
                *(tr_line) = *(tr_line) + 1;
            }

            *(index) = *(index) + 1;
            i++;
        }
        clock_gettime(CLOCK_REALTIME, &intF);
        end = sec(intF) - start_time;
        int_runtime = end - begin;
    }
}

/* Receives an arg_thread pointer, which has process pointer, a timespec
 * and a flag. Execute a thread using the processing function 
 * and the arg_thread as argument for processing. */
void exec_thread(arg_thread* argv) {
    int ret;
    pthread_t main_thread;
    ret = pthread_create(&main_thread, NULL, &processing, (void*)argv);
    pthread_join(main_thread, NULL);
    
    if (ret == -1) {
        perror("pthread_create exited with failure");
        exit(-1);
    }
}

/* Receives the input file, the output file and a flag.
 * Implements the Shortest Job First scheduler using a heap.*/
void SJF (FILE *trace_file, FILE *result, int details) {
    int nb_process, tr_line, rs_line, read_index;
    double tf, tr, start_time;
    struct timespec start, threadI, threadF;
  	
  	tr_line = rs_line = 1;
    read_index = 0;
    
    process **plist = get_process(trace_file, &nb_process);
    heap *min_heap = init_heap(nb_process);
    
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    start_time = sec(start);

    while (read_index < nb_process) {
        insert_loop(plist, (void*) min_heap, SJFID, start_time, 
                    nb_process, &read_index, &tr_line, details);
        
        while (min_heap->pr_total > 0) {
            arg_thread* argv = construct_argv(SJFID, (void*) min_heap, DBL_MAX, details);

            clock_gettime(CLOCK_REALTIME, &threadI);
            exec_thread(argv);
            clock_gettime(CLOCK_REALTIME, &threadF);
            
            tf = sec(threadF) - start_time;
            tr = tf - argv->p->times[0];
            
            if (details) {
            	result_line(argv->p->name, rs_line);
            	rs_line++;		            	
            }

            write_file(result, argv->p, tf, tr);
            free(argv);
        }
    }

    write_file_context(result, 0);
    pthread_mutex_destroy(&lock);    
}

/* Receives the input file, the output file and a flag.
 * Implements the Round Robin scheduler using a queue.*/
void Round_Robin (FILE *trace_file, FILE *result, int details) {
    int nb_process, read_index, exec_index, context, tr_line, rs_line;
    double tf, tr, start_time;
    struct timespec start, cur_time;
  
    process **plist = get_process(trace_file, &nb_process);
    rrqueue *q = init_rrqueue();
    
    tr_line = rs_line = 1;
    read_index = exec_index = context = 0;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    start_time = sec(start);

    while (exec_index < nb_process) {
        
        if (read_index < nb_process)
            insert_loop(plist, (void*)q, RRID, start_time, 
                        nb_process, &read_index, &tr_line, details);

        int qsize = read_index - exec_index;
        while (qsize) {

            arg_thread* argv = construct_argv(RRID, (void*) q, QUANTUM, details);
            exec_thread(argv); 
            q->first->p->times[1] -= QUANTUM;

            clock_gettime(CLOCK_REALTIME, &cur_time);
            if (q->first->p->times[1] <= 0) {
                tf = sec(cur_time) - start_time;
                tr = tf - q->first->p->times[0];

                if (details) {
            		result_line(argv->p->name, rs_line);
            		rs_line++;		            	
            	}

                write_file(result, q->first->p, tf, tr);
                remove_rrqueue(q);
                exec_index++;
            }
            else {
                move_rrqueue(q);
                context++;
                if (details) context_change(context);
            }
            qsize--;
        }
    }

    write_file_context(result, context);
    pthread_mutex_destroy(&lock);    
}

/* Receives the input file, the output file and a flag.
 * Implements the Priority scheduler using a heap. */
void Priority (FILE *trace_file, FILE *result, int details) {
    int nb_process, read_index, exec_index, context, hsize, tr_line, rs_line;
    double tf, tr, abs_runtime, start_time;
    struct timespec start, cur_time;
  
    process **plist = get_process(trace_file, &nb_process);
    heap* min_heap = init_heap(nb_process);
    
    read_index = exec_index = context = 0;
    abs_runtime = 0;
    tr_line = rs_line = 1;
    pthread_mutex_init(&lock, NULL);

    clock_gettime(CLOCK_REALTIME, &start);
    start_time = sec(start);

    while (exec_index < nb_process) {
        if(read_index < nb_process)
            insert_loop(plist, (void*)min_heap, PRID, start_time, 
                        nb_process, &read_index, &tr_line, details);

        hsize = read_index - exec_index;
        while (hsize) {
            arg_thread* argv = construct_argv(PRID, (void*) min_heap, hsize*QUANTUM, details);
            exec_thread(argv);
            argv->p->times[1] -= (hsize) * QUANTUM;

            clock_gettime(CLOCK_REALTIME, &cur_time);
            if (argv->p->times[1] <= 0) {
                tf = sec(cur_time) - start_time;
                tr = tf - argv->p->times[0];

                if (details) {
            		result_line(argv->p->name, rs_line);
            		rs_line++;		            	
            	}

                write_file(result, argv->p, tf, tr);
                exec_index++;
            }
            else {
                context++;
                if (details) context_change(context);

                argv->p->times[3] = DBL_MAX;
                insert_heap(min_heap, argv->p);
            }
            hsize--;
        }

        hsize = read_index - exec_index;
        clock_gettime(CLOCK_REALTIME, &cur_time);
        abs_runtime = sec(cur_time) - start_time;

        for (int i = read_index - exec_index; i < 0; i--) {
            min_heap->min_pq[i]->times[3] = min_heap->min_pq[i]->times[2] 
                - abs_runtime - min_heap->min_pq[i]->times[1];
            
        }
    }

    write_file_context(result, context);
    pthread_mutex_destroy(&lock);    
}

int main (int argc, char **argv) {
    FILE* fl_input = fopen(argv[2], "r");
    FILE* fl_result = fopen(argv[3], "w");
    int d;

    if (argc == 5 && *argv[4] == 'd') d = 1;
    else d = 0;
 
    int id = atoi(argv[1]);
    if (id == SJFID) SJF(fl_input, fl_result, d);
    else if (id == RRID) Round_Robin(fl_input, fl_result, d);
    else Priority(fl_input, fl_result, d);

    return 0;
}
