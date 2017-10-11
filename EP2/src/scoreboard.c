#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types.h"

int compareScore(const void* a, const void* b) {
    if ((**(cyclist**)a).score > (**(cyclist**)b).score) return -1;
    if ((**(cyclist**)a).score == (**(cyclist**)b).score) return 0;
    return 1;
}

void print_scoreboard(race* r, bool verbose) {
    cyclist** caux = malloc(r->ncomp * sizeof(cyclist*));
    for (int i = 0; i < r->ncomp; i++)
        caux[i] = r->comp[i];
    qsort(caux, r->ncomp, sizeof(cyclist*), compareScore);

    for (int i = 0; i < r->ncomp; i++)
        if (verbose)
            printf("%u - %d - %u\n", i, caux[i]->id, caux[i]->score);
        else
            printf("%u - %d\n", i, caux[i]->id);
}

