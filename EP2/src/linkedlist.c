#include <stdio.h>
#include <stdlib.h>

#include "types.h"

/* Returns a LinkedList* with its head as a NULL value. */
LinkedList* construct_linkedlist() {
    LinkedList* l = malloc(sizeof(LinkedList));
    l->head = NULL;
    return l;
}

/* Receives a LinkedList*. Prints it according to the specification. */
void print_linkedlist (LinkedList* l) {
    node* aux;
    aux = l->head;
    while (aux != NULL) {
        printf("\n");
        printf("O ciclista %d quebrou na volta %u\n", aux->id, aux->lap);
        aux = aux->next;
    }
}

bool in_linkedlist (LinkedList* l, int id) {

    if (l->head != NULL) {
        node* aux = l->head;
        while (aux != NULL) {
            if (aux->id == id && aux->check == false){
                aux->check = true;
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

    if (l->head == NULL) {
        l->head = n;
        l->head->next = NULL;
    }
    else {
        node* aux = l->head;
        while (aux->next != NULL) aux = aux->next;
        aux->next = n;
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
        aux = NULL;
    }
    free(l);
}
