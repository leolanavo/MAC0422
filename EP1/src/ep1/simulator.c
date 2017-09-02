#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../include/ep1/types.h"
#include "../../include/ep1/heap.h"
#include "../../include/ep1/read_file.h"

//Shortest Job First
void SJF (FILE *trace_file, char *result) {
	int ret, nb_process;
	pthread_t main_thread;
	process p;

	process **pr = get_process(trace_file, &nb_process);
	process *heap = minPQ (pr, pr_total);

	free(pr);

	while (pr_total > 0) {
		p = delMin(heap, pr_total);
		ret = pthread_create(&main_thread, NULL, processing, (void*)p);
	}
}

//Each process is given a time interval (QUANTUM)
void Round_Robin (FILE *trace_file, char *result) {

}

//Each level of priority defines how much time the process receives 
void Priority (FILE *trace_file, char *result) {

}

void* processing (process p) {

}

int main (int argc, char **argv) {

	FILE* fl_name = fopen (argv[2]);
	
	if (*argv[1] == 1) SJF(fl_name, argv[3]);
	else if (*argv[1] == 2) Round_Robin(fl_name, argv[3]);
	else Priority(fl_name, argv[3]);

	return 0;
}
