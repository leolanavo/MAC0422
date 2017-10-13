#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types.h"

int compareScore(const void* a, const void* b) {
    if ((**(cyclist**)a).score > (**(cyclist**)b).score) return -1;
    if ((**(cyclist**)a).score == (**(cyclist**)b).score) return 0;
    return 1;
}

void print_scoreboard(race* r, bool verbose, int break_id) {

    cyclist** caux = copy_array(r->comp, r->ncomp);
    qsort(caux, r->ncomp, sizeof(cyclist*), compareScore);

    if (break_id >= 0) {
        int c;
        for (c = 0; c < r->ncomp && caux[c]->id != break_id; c++);

        printf("Broken cyclist: %d Lap: %d Position: %d\n", break_id, r->comp[break_id]->lap, c + 1);
    }


    printf("POSITION     ID     SCORE\n");
    int ncomp = r->ncomp;

    for (int i = 0; i < ncomp; i++) {
        if (caux[i]->speed == 0) ncomp++;
        
        else {
            if (verbose)
                printf("   %d     -   %d  -    %d\n", i + 1, caux[i]->id, caux[i]->score);
            else
                printf("%d - %d\n", i + 1, caux[i]->id);
        }
    }
}

int compareDist(const void* a, const void* b) {
    if ((**(cyclist**)a).dist > (**(cyclist**)b).dist) return -1;
    if ((**(cyclist**)a).dist == (**(cyclist**)b).dist) return 0;
    return 1;
}

void specialPoints(race* r) {
    cyclist** caux = copy_array(r->comp, r->ncomp);
    qsort(caux, r->ncomp, sizeof(cyclist*), compareDist);

    if (caux[0]->lap >= caux[1]->lap + 2)
        r->comp[caux[0]->id]->score += 20;
}