#ifndef RRQUEUE_H
#define RRQUEUE_H

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void move_rrqueue(rrqueue* q);

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void remove_rrqueue(rrqueue* q);

/* Receives a rrqueue pointer and a process  pointer, and inserts 
 * the process pointer in the last position of the rrqueue pointer. */
void insert_rrqueue(rrqueue* q, process* p);

/* Returns an allocted rrqueue pointer. */
rrqueue* init_rrqueue();

#endif
