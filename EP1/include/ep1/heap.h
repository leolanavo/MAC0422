#ifndef HEAP_H
#define HEAP_H

/* Receives a list of processes and the list size. 
 * Returns a priority queue with all the processes given. */
heap minPQ (int size);

/* Receives the priority queue and its size. 
 * Returns the process with the least completion time left */
process delMin (heap h);

/* Receives the priority queue structure heap and the process
 * that will be added. */
void insert (heap h, process entry);

#endif