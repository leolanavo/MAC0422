#ifndef TYPES_H
#define TYPES_H

/* This structure has the process name, and a array with
 * initial time, duration time, deadline time and remaining
 * time to complete the task. */
typedef struct {
    char* name;
    int times[4];
} process;

/* This is the priority queue structure, with queue and its size,
 * and the total number of processes int it.*/
typedef struct {
	process *min_pq;
	int size, pr_total;
} heap; 

/* This structure has a process pointer to store the content 
 * of a node in the queue and a next to store which node 
 * is the next in the queue. */
typedef struct cell {
    process* p;
    struct cell* next;
} node;

/* This structure has two node pointers to indicate in 
 * which nodes the queue begins and ends. */
typedef struct {
    node* first;
    node* last;
} rrqueue;

#endif
