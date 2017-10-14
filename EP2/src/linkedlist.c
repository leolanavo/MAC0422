#include <stdio.h>
#include <stdlib.h>

#include "types.h"

/* Returns a LinkedList* with its head as a NULL value. */
LinkedList* construct_linkedlist() {
    LinkedList* l = malloc(sizeof(LinkedList));
    l->head = NULL;
    l->size = 0;
    return l;
}

/* Receives a LinkedList*. Prints it according to the specification. */
void print_linkedlist (LinkedList* l) {
    printf(RED "Ciclistas quebrados" RESET "\n");
    node* aux;
    aux = l->head;
    while (aux != NULL) {
        printf(RED"\tO ciclista %d quebrou na volta %u"RESET"\n", aux->id, aux->lap);
        aux = aux->next;
    }
}

bool in_linkedlist (LinkedList* l, int id) {

    if (l->head != NULL) {
        node* aux = l->head;
        while (aux != NULL) {
            if (aux->id == id){
                return true;
            }

            aux = aux->next;
        }
    }

    return false;
}

/* Receives an id, a lap, and a LinkedList*. Inserts a new node with the
 * given id and lap at the end of the LinkedList* */
void insert_linkedlist(int id, int lap, LinkedList* l) {
    node* n = malloc(sizeof(node));
    n->id = id;
    n->lap = lap;
    n->check = false;
    n->next = NULL;

    if (l->head == NULL)
        l->head = n;

    else {
        node* aux = l->head;
        while (aux != NULL) aux = aux->next;
        aux = n;
    }
}

/* Receives a LinkedList*. Frees every node in the LinkedList* and
 * the LinkedList* */
void destroy_linkedlist(LinkedList* l) {
    node* aux;
    while (l->head != NULL) {
        aux = l->head;
        l->head = l->head->next;
        free(aux);
    }
    free(l);
}
