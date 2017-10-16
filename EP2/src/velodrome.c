/*************************************************
 * Leonardo Lana Violin Oliveira - NUSP: 9793735 *
 * Beatriz Figuereido Marouelli  - NUSP: 9793652 *
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"
#include "cyclist.h"


void print_tracks (velodrome* v) {
    printf(RED_BOLD"DEBUG"RESET"\n");
    for (int i = 0; i < v->length; i++){
        for (int j = 0; j < TRACKS; j++)
            printf("  |%d|", v->tracks[i][j]);
        printf("\n");
    }
    printf("\n\n");
}

/* Construct a velodrome*, with a matrix length X 10 as the velodrome
 * matrix */
velodrome* construct_velodrome (int length, int ncomp, cyclist** comp) {
    velodrome* v = malloc(sizeof(velodrome));
    v->length = length;

    v->tracks = malloc(length * sizeof(int*));
    for (int i = 0; i < length; i++)
        v->tracks[i] = malloc(TRACKS * sizeof(int));

    for (int i = 0; i < length; i++)
        for (int j = 0; j < TRACKS; j++)
            v->tracks[i][j] = -1;

    int tmp = 0;
    int i = length - 1;
    while (tmp < ncomp) {
        for (int j = 0; j < TRACKS && tmp < ncomp; j++) {
            v->tracks[i][j] = tmp;
            comp[tmp]->dist = i - length;
            comp[tmp]->row = i;
            comp[tmp]->col = j;
            tmp++;
        }
        i--;
    }
    return v;
}

/* Construct a cyclist** with ncomp cyclist*, each cyclist is created
 * according to the standard initial values */
cyclist** construct_competitors (int ncomp) {
    cyclist** comp = malloc(ncomp*sizeof(cyclist*));
    for (int i = 0; i < ncomp; i++)
        comp[i] = init_cyclist(i);

    return comp;
}

/* Frees the matrix that represents the velodrome */
void destroy_velodrome(velodrome* v) {
    for (int i = 0; i < v->length; i++) {
        free(v->tracks[i]);
        v->tracks[i] = NULL;
    }
    free(v->tracks);
    v->tracks = NULL;
    free(v);
    v = NULL;
}
