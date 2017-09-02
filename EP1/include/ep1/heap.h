#ifndef HEAP_H
#define HEAP_H

/* Receives a list of processes and the list size. 
 * Returns a priority queue with all the processes given. */
process* minPQ (process **p, int pr_total);

/* Receives the priority queue and its size. 
 * Returns the process with the least completion time left */
process delMin (process *p, int total);

#endif