#ifndef HEAP_H
#define HEAP_H

typedef struct {
	char *name;
	int times[4];
} process;


process* minPQ (process **p, int pr_total);

process delMin (process *p, int total);

#endif