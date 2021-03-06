/*************************************************
 * Leonardo Lana Violin Oliveira - NUSP: 9793735 *
 * Beatriz Figuereido Marouelli  - NUSP: 9793652 *
 *************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* Returns a LinkedList* with its head as a NULL value. */
LinkedList* construct_linkedlist();

/* Receives a LinkedList*. Prints it according to the specification. */
void print_linkedlist (LinkedList* l);

bool in_linkedlist (LinkedList* l, int id);

/* Receives an id, a lap, and a LinkedList*. Inserts a new node with the
 * given id and lap at the end of the LinkedList* */
void insert_linkedlist(int id, int lap, LinkedList* l);

/* Receives a LinkedList*. Frees every node in the LinkedList* and
 * the LinkedList* */
void destroy_linkedlist(LinkedList* l);


#endif
