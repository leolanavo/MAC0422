#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"
#include "cyclist.h"

/* Construct a velodrome*, with a matrix length X 10 as the velodrome
 * matrix */
velodrome* construct_velodrome (uint length) {
    velodrome* v = malloc(sizeof(velodrome));
    v->length = length;

    v->tracks = malloc(length * sizeof(uint*));
    for (uint i = 0; i < length; i++)
        v->tracks[i] = malloc(10 * sizeof(uint));
    return v;
}

/* Construct a cyclist** with ncomp cyclist*, each cyclist is created
 * according to the standard initial values */
cyclist** construct_competitors (uint ncomp) {
    cyclist** competitors = malloc(ncomp*sizeof(cyclist*));
    for (uint i = 0; i < ncomp; i++) {
        competitors[i] = init_cyclist(i);
    }
    return competitors;
}

/* Frees the matrix that represents the velodrome */
void destroy_velodrome(velodrome* v) {
    for (uint i = 0; i < v->length; i++)
        free(v->tracks[i]);
    free(v->tracks);
    free(v);
}

/* Frees the array that represents the competitors of the race */
void destroy_competitors (cyclist** c, uint size) {
    for (uint i = 0; i < size; i++)
        free(c[i]);
    free(c);
}

int main (int argc, char** argv) {
    if (argc != 4) {
        printf("Insufficient number of arguments\n");
        exit(-1);
    }

    race* r = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    destroy_race(r);
    return 0;
}
