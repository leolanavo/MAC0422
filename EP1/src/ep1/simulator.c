#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../include/ep1/types.h"
#include "../../include/ep1/heap.h"
#include "../../include/ep1/read_file.h"

void* processing (void *process) {
	return process;
}

//Shortest Job First
void SJF (FILE *trace_file, char *result) {
	int ret, nb_process;
	pthread_t main_thread;
	process *p = NULL;

	process **pr = get_process(trace_file, &nb_process);
	heap min_heap = minPQ (nb_process);

	while (min_heap.pr_total > 0) {
		*p = delMin(min_heap);
		ret = pthread_create(&main_thread, NULL, &processing, (void*)p);
	}
}

//Each process is given a time interval (QUANTUM)
void Round_Robin (FILE *trace_file, char *result) {

}

//Each level of priority defines how much time the process receives 
void Priority (FILE *trace_file, char *result) {

}

int main (int argc, char **argv) {

	FILE* fl_name = fopen (argv[2], "r");
	
	if (*argv[1] == 1) SJF(fl_name, argv[3]);
	else if (*argv[1] == 2) Round_Robin(fl_name, argv[3]);
	else Priority(fl_name, argv[3]);

	return 0;
}
