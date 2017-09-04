#include <stdlib.h>
#include "../../include/ep1/read_file.h"
#include "../../include/ep1/types.h"

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void move_rrqueue(rrqueue* q) {
    q->first = q->first->next;
    q->last = q->last->next;
}

/* Receives a rrqueue pointer and removes the first node of the 
 * queue. */
void remove_rrqueue(rrqueue* q) {
    node* n = q->first;

    if (q->first == q->first->next)
        q->first = NULL;
    
    q->first = q->first->next;
    q->last->next = q->first;
    
    free(n);
}

/* Receives a rrqueue pointer and a process  pointer, and inserts 
 * the process pointer in the last position of the rrqueue pointer. */
void insert_rrqueue(rrqueue* q, process* p) {
    node* c = malloc(sizeof(node));
    c->p = p;
    c->p->times[3] = p->times[1];

    if (q->first == NULL && q->last == NULL) {
        q->first = c;
        q->last = c;
        q->first->next = c;
    }
    else {
        q->last->next = c;
        q->last = c;
    }
    q->last->next = q->first;
}

/* Returns a allocted rrqueue pointer */
rrqueue* init_rrqueue() {
    rrqueue* q = malloc(sizeof(rrqueue));
    q->first = NULL;
    q->last = NULL;
    return q;
}
