#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "types.h"

#define prob_to_60 0.7
#define prob_to_30 0.5
#define prob_to_90 0.1

/* Change the speed of a cyclist according to the rules defined in
 * the assignment. */
void change_speed (cyclist* c) {
    double prob = (double)rand()/(double)RAND_MAX;
    if (c->speed == 30 && prob < prob_to_60)
        c->speed = 60;
    else if (c->speed == 60 && prob < prob_to_30)
        c->speed = 30;
}

/* Change the speed of a cyclist to 90Km/h if the drawn number is
 * smaller than 0.1, this number follow an uniform distribution
 * between 0 and 1 */
void change_speed_90 (cyclist* c) {
    double prob = (double)rand()/(double)RAND_MAX;
    if (prob < prob_to_90)
        c->speed = 90;
}

/* Initialize a cyclist pointer with the standar value of which
 * parameter */
cyclist* init_cyclist (uint id) {
    cyclist* c = malloc(sizeof(cyclist));
    c->id = id;
    c->speed = 30;
    c->points = 0;
    return c;
}

/* Change the position of the cyclist in the velodrome matrix */
void position_cyclist (cyclist* c, uint lin, uint row, uint length) {
    c->dist = -(length*lin);
    c->track = row;
    c->meter = lin;
}

/* int main (int argc, char** argv) {
 *     if (argc != 2) {
 *         printf("Wrong number of arguments");
 *         exit(-1);
 *     }
 *
 *     srand(time(NULL));
 *
 *     cyclist* c = malloc(sizeof(cyclist));
 *     c->speed = atoi(argv[1]);
 *     change_speed(c);
 *     free(c);
 * } */
