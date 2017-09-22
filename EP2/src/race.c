#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"

int main (int argc, char** argv) {
    if (argc != 4) {
        printf("Insufficient number of arguments\n");
        exit(-1);
    }

    race* r = malloc(sizeof(race));
    r->length = atof(argv[1]);
    r->competitors = malloc(atoi(argv[2])*sizeof(cyclist));
    r->laps = atoi(argv[3]);
    return 0;
}
