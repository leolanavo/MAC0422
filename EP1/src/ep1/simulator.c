#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "heap.h"


//Shortest Job First
void SJF (char *trace_file, char *result) {
	int ret;
	pthread_t main_thread;
	process p;

	process **pr = LANA_FUNC(trace_file);
	process *heap = minPQ (pr, pr_total);

	free(pr);

	while (pr_total > 0) {
		p = delMin(heap, pr_total);
		ret = pthread_create(&main_thread, NULL, processing, (void*)p);
	}
}

//Each process is given a time interval (QUANTUM)
void Round_Robin (char *trace_file, char *result) {

}

//Each level of priority defines how much time the process receives 
void Priority (char *trace_file, char *result) {

}

void* processing (process p) {

}

int main (int argc, char **argv) {
	
	if (*argv[1] == 1) SJF(argv[2], argv[3]);
	else if (*argv[1] == 2) Round_Robin(argv[2], argv[3]);
	else Priority(argv[2], argv[3]);

	return 0;
}