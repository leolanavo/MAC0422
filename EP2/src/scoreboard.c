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
            printf("%d - %d - %d - %d\n", i, caux[i]->id, caux[i]->score, caux[i]->lap);
        else
            printf("%d - %d\n", i, caux[i]->id);
}

int compareDist(const void* a, const void* b) {
    if ((**(cyclist**)a).dist > (**(cyclist**)b).dist) return -1;
    if ((**(cyclist**)a).dist == (**(cyclist**)b).dist) return 0;
    return 1;
}

void specialPoints(race* r) {
    cyclist** caux = malloc(r->ncomp * sizeof(cyclist*));
    for (int i = 0; i < r->ncomp; i++)
        caux[i] = r->comp[i];
    qsort(caux, r->ncomp, sizeof(cyclist*), compareDist);

    if (caux[0]->lap >= caux[1]->lap + 2) {
        printf("LAP: %d %d, ID: %d\n", caux[0]->lap, caux[1]->lap, caux[0]->id);
        r->comp[caux[0]->id]->score += 20;
    }
}