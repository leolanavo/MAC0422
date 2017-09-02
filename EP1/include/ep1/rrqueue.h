#ifndef RRQUEUE_H
#define RRQUEUE_H

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void move_queue(rrqueue* q);

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void move_queue(rrqueue* q);

/* Receives a rrqueue pointer and a process  pointer, and inserts 
 * the process pointer in the last position of the rrqueue pointer. */
void insert_queue(rrqueue* q, process* p);

/* Receives an integer, which is the number of process to be staggered 
 * and a process double pointer, which is a list of all process. Returns 
 * a rrqueue pointer with all the process listed in the process double 
 * pointer. */
rrqueue* init_queue(int max, process** plist);

#endif
