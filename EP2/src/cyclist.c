#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#include "types.h"

#define prob_to_60 70
#define prob_to_30 50
#define prob_to_90 10

/* Change the speed of a cyclist according to the rules defined in
 * the assignment. */
void change_speed (cyclist* c) {
    uint prob = (uint)rand()%100;
    if (c->speed == 30 && prob < prob_to_60)
        c->speed = 60;
    else if (c->speed == 60 && prob < prob_to_30)
        c->speed = 30;
}

/* Change the speed of a cyclist to 90Km/h if the drawn number is
 * smaller than 0.1, this number follow an uniform distribution
 * between 0 and 1 */
void change_speed_90 (cyclist* c) {
    uint prob = (uint)rand()%100;
    if (prob < prob_to_90)
        c->speed = 90;
}

/* Initialize a cyclist pointer with the standar value of which
 * parameter */
cyclist* init_cyclist () {
    cyclist* c = malloc(sizeof(cyclist));
    c->speed = 30;
    c->score = 0;
    c->down = false;
    return c;
}

void break_down (uint lap) {
    if (lap % 15 == 0) {

    }
}

/* Change the position of the cyclist in the velodrome matrix */
void move_cyclist (cyclist* c, velodrome* v, uint row, uint col, cyclist** comp, uint length) {
    bool empty_front = v->tracks[(row+1)%length][col] == -1? true : false;
    bool empty_right = v->tracks[row][col+1] == -1? true : false;
    bool empty_diagr = v->tracks[(row+1)%length][col+1] == -1? true : false;
    bool empty_diagl = v->tracks[(row+1)%length][col-1] == -1? true : false;

    uint v_front = empty_front? comp[v->tracks[row+1][col]]->speed : INT_MAX;

    if (v_front < c->speed && empty_right && empty_diagr) {
        v->tracks[(row+1)%length][col+1] = v->tracks[row][col];
        v->tracks[row][col] = -1;
        c->dist++;
        c->overtook = true;
    }
    else if (c->overtook && empty_diagl) {
        v->tracks[(row+1)%length][col-1] = v->tracks[row][col];
        v->tracks[row][col] = -1;
        c->dist++;
        c->overtook = false;
    }
    else if (empty_front) {
        v->tracks[(row+1)%length][col] = v->tracks[row][col];
        v->tracks[row][col] = -1;
        c->dist++;
        c->overtook = false;
    }
    else if (v_front < c->speed && (!empty_right || !empty_diagr)){
        c->speed = v_front;
    }
}
