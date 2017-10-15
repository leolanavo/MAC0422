#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types.h"
#include "cyclist.h"

int compareScore(const void* a, const void* b) {
    if ((**(cyclist**)a).score > (**(cyclist**)b).score) return -1;
    if ((**(cyclist**)a).score == (**(cyclist**)b).score) return 0;
    return 1;
}

void print_scoreboard(race* r, int verbose, int break_id) {

    cyclist** caux = copy_array(r);
    qsort(caux, r->fixed_ncomp, sizeof(cyclist*), compareScore);

    if (break_id >= 0) {
        int c;
        for (c = 0; c < r->ncomp && caux[c]->id != break_id; c++);

        //printf(RED "BROKEN CYCLIST: %d LAP: %d POSITION: %d" RESET "\n", 
               //break_id, r->comp[break_id]->lap, c + 1);
        return;
    }
    
     /*
    if (verbose == 1)
        printf(BLUE "POSITION     ID     SCORE" RESET "\n");
    else if (verbose == 0)
        printf(YELLOW "POSITION     ID" RESET "\n");
    else
        printf(CYAN "ID     POSITION     TIME(min)     SCORE" RESET "\n");
    */

    int offset = 0;
    for (int i = 0; i < r->fixed_ncomp; i++) {
        
        if (caux[i]->speed != 0) {
            if (verbose == 1) {
                int debug = 0;
                debug++;
                //printf(BLUE "   %d     -   %d  -    %d" RESET "\n", 
                      //(i + 1 - offset), caux[i]->id, caux[i]->score);
            }
            else if (verbose == 0) {
                int debug = 0;
                debug++;
                //printf(YELLOW "   %d     -     %d" RESET "\n", 
                      //(i + 1 - offset), caux[i]->id);
            }
            else {
                int debug = 0;
                debug++;
                //printf(CYAN " %d  -    %d     -     %.2f     -     %d" RESET "\n",
                    //caux[i]->id, (i + 1 - offset), caux[i]->ftime, caux[i]->score);
            }
        }
        else
            offset++;
    }

    destroy_array(caux, r->fixed_ncomp);
}

int compareDist(const void* a, const void* b) {
    if ((**(cyclist**)a).dist > (**(cyclist**)b).dist) return -1;
    if ((**(cyclist**)a).dist == (**(cyclist**)b).dist) return 0;
    return 1;
}

void specialPoints(race* r) {
    cyclist** caux = copy_array(r);
    int size = r->fixed_ncomp - r->broken_comp->size;
    qsort(caux, size, sizeof(cyclist*), compareDist);

    if (caux[0]->lap >= caux[1]->lap + 2)
        r->comp[caux[0]->id]->score += 20;

    destroy_array(caux, r->fixed_ncomp);
}