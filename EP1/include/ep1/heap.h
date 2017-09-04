#ifndef HEAP_H
#define HEAP_H

/* Receives a list of processes and the list size. 
 * Returns a priority queue with all the processes given. */
heap* init_heap (int size);

/* Receives the priority queue structure heap and the process
 * that will be added. */
void insert_heap (heap *h, process *entry);

/* Receives the priority queue and its size. 
 * Returns the process with the least completion time left */
process* remove_heap (heap *h);

#endif
