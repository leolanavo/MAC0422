#include <../include/ep1/read_file.h>
#include <../include/ep1/types.h>

#define const int QUANTUM = 1

/* Has a process pointer to store the content of a node 
 * in the queue and a next to store which node is the 
 * next in the queue. */
typedef struct cell {
    process* p;
    struct cell* next;
} node;

/* Has two node pointers to indicate in which nodes the queue
 * begins and ends. */
typedef struct {
    node* first;
    node* last;
} rrqueue;

/* Receives an rrqueue pointer and moves the first node to the 
 * last position. */
void move_queue(rrqueue* q) {
    q->first = q->first->next;
    q->last = q->last->next;
}

/* Receives a rrqueue pointer and removes the first node of the 
 * queue. */
void remove_queue(rrqueue* q) {
    node* n = q->first;

    if (q->first == q->first->next)
        q->first = NULL;
    
    q->first = q->first->next;
    q->last = q->first;
    
    free(n);
}

/* Receives a rrqueue pointer and a process  pointer, and inserts 
 * the process pointer in the last position of the rrqueue pointer. */
void insert_queue(rrqueue* q, process* p) {
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

/* Receives an integer, which is the number of process to be staggered 
 * and a process double pointer, which is a list of all process. Returns 
 * a rrqueue pointer with all the process listed in the process double 
 * pointer. */
rrqueue* init_queue(int max, process** plist) {
    rrqueue* q = malloc(sizeof(rrqueue));
    q->first = NULL;
    q->last = NULL;

    for(int i = 0; i < max - 1; i++)
        insert_queue(q, plist[i]);   
}

int main () {
    return 0;
}
