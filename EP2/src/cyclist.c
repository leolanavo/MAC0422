/*************************************************
 * Leonardo Lana Violin Oliveira - NUSP: 9793735 *
 * Beatriz Figuereido Marouelli  - NUSP: 9793652 *
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#include "types.h"
#include "linkedlist.h"
#include "race.h"

#define prob_to_60 70
#define prob_to_30 50
#define prob_to_90 10
#define prob_break 1

pthread_mutex_t rand_lock;

void init_lock_cyclist() {
    pthread_mutex_init(&rand_lock, NULL);
}

void destroy_lock_cyclist() {
    pthread_mutex_destroy(&rand_lock);
}

int get_random() {
    pthread_mutex_lock(&rand_lock);
    int i = (int)rand();
    pthread_mutex_unlock(&rand_lock);
    return i;
}


cyclist** copy_array (race* r) {

    cyclist** caux = malloc(r->fixed_ncomp * sizeof(cyclist*));

    for (int i = 0; i < r->fixed_ncomp; i++) {
        caux[i] = malloc(sizeof(cyclist));
        *caux[i] = *r->comp[i];
    }
    return caux;
}

void destroy_array (cyclist** comp, int size) {
    for (int i = 0; i < size; i++)
        free(comp[i]);
    free(comp);
}

void adequate_speed(int id, race* r) {
    int row = r->comp[id]->row;
    int col = r->comp[id]->col;
    bool need_break = false;

    do {
        if (r->v->tracks[row][col] == -1)
            break;
        else if (r->comp[r->v->tracks[row][col]]->speed == 30)
            need_break = true;
        row = (row + 1) % r->v->length;
    } while (row != r->comp[id]->speed && !need_break);

    if (need_break)
        r->comp[id]->speed = 30;
}

/* Change the speed of a cyclist according to the rules defined in
 * the assignment. */
void change_speed (int id, race* r) {
    int prob = get_random()%100;
    if (r->comp[id]->speed == 30 && prob < prob_to_60)
        r->comp[id]->speed = 60;
    else if (r->comp[id]->speed == 60 && prob < prob_to_30)
        r->comp[id]->speed = 30;
}

/* Change the speed of a cyclist to 90Km/h if the drawn number is
 * smaller than 10, this number follow an uniform distribution
 * between 0 and 1 */
void change_speed_90 (race* r) {
    if (r->sprinter == -1) {
        int id = get_random() % r->fixed_ncomp;
        int prob = get_random() % 100;

        while (in_linkedlist(r->broken_comp, id))
            id = rand() % r->fixed_ncomp;

        if (prob < prob_to_90)
            r->sprinter = id;

        else
            r->sprinter = -2;
    }
}

/* Initialize a cyclist pointer with the standard value of which
 * parameter */
cyclist* init_cyclist (int id) {
    cyclist* c = malloc(sizeof(cyclist));
    c->speed = 30;
    c->score = 0;
    c->lap = 1;
    c->id = id;
    c->overtook = false;
    c->ftime = 0;
    return c;
}

bool break_cyclist (cyclist* c, race* r) {
    int prob = (int)get_random()%100;
    if (prob > prob_break || r->ncomp <= 5 || r->sprinter == c->id)
        return false;
    r->v->tracks[c->row][c->col] = -1;
    insert_linkedlist(c->id, c->lap, r->broken_comp);
    c->speed = 0;
    return true;
}

int has_cyclist (LinkedList* l) {

    int count = 0;

    if (l->head != NULL) {
        node* aux = l->head;
        while (aux != NULL) {
            if (!aux->check){
                count++;
                aux->check = true;
            }

            aux = aux->next;
        }
    }

    return count;
}

void change_pos(cyclist* c, race* r, int move_id) {

    r->v->tracks[c->row][c->col] = -1;
    c->row = (c->row + 1) % r->v->length;

    if (move_id == 1) c->col++;
    else if (move_id == 2) c->col--;

    r->v->tracks[c->row][c->col] = c->id;

}

void counter_cyclist(cyclist* c, race* r, int move_id) {

    int id = r->sprinter;

    if ((id < 0 || r->comp[id]->speed != 90) && (
                (c->speed == 60 && c->move >= 1) ||
                (c->speed == 30 && c->move >= 2))) {

        c->dist++;
        c->move = 0;
        change_pos(c, r, move_id);
    }
    else if (id >= 0 && r->comp[id]->speed == 90 && (
                (c->speed == 90 && c->move >= 1) ||
                (c->speed == 60 && c->move >= 3) ||
                (c->speed == 30 && c->move >= 6))) {

        c->dist++;
        c->move = 0;
        change_pos(c, r, move_id);
    }
}

/* Change the position of the cyclist in the velodrome matrix */
void move_cyclist (cyclist* c, race* r) {
    velodrome* v = r->v;
    cyclist** comp = r->comp;
    int length = v->length;

    bool empty_front = v->tracks[(c->row + 1) % length][c->col] == -1? true : false;

    bool empty_right = c->col + 1 < TRACKS?
        v->tracks[c->row][c->col + 1] == -1? true : false :
        false;

    bool empty_diagr = c->col + 1 < TRACKS?
        v->tracks[(c->row + 1) % length][c->col + 1] == -1? true : false :
        false;

    bool empty_diagl = c->col - 1 >= 0?
        v->tracks[(c->row+1) % length][c->col-1] == -1? true : false :
        false;

    int s_front = empty_front == false?
        comp[v->tracks[(c->row + 1) % length][c->col]]->speed :
        INT_MAX;

    c->overtook = false;
    int move_id = 0;

    if (s_front < c->speed && empty_right && empty_diagr) {
        c->overtook = true;
        move_id = 1;
    }
    else if (c->overtook && empty_diagl)
        move_id = 2;
    else if (!empty_front && (!empty_right || !empty_diagr))
        adequate_speed(c->id, r);

    c->move++;
    counter_cyclist(c, r, move_id);
}
