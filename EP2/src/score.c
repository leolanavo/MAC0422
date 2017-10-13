#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "types.h"

/***********************************************
 * Function: swap                              *
 * --------------                              *
 *  @arg a: the first cyclist                  *
 *  @arg b: the second cyclist                 *
 *                                             *
 *  @process: Swaps to cyclist in the memory   *
 *                                             *
 *  @retrun: void function.                    *
 ***********************************************/
void swap(cyclist *a, cyclist *b) {
    cyclist temp = *a;
    *a = *b;
    *b = temp;
}

/********************************************************
 * Function: partition                                  *
 * -------------------                                  *
 *  @arg comp: an array of cyclists                     *
 *  @arg l:    the begging of the subarray              *
 *  @arg r:    the end of the subarray                  *
 *                                                      *
 *  @process:  divides the subarray into two parts,     *
 *             the first one contains all the cyclists  *
 *             which have a smaller dist value, and the *
 *             seconde one, all the bigger.             *
 *                                                      *
 *  @retrun:   the position where the last cyclist      *
 *             in the subarray should be if the array   *
 *             was sorted using the dist field          *
 ********************************************************/
int partition(cyclist** comp, int l, int r) {
    cyclist c = *(comp[r]);
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (comp[j]->dist <= c.dist) {
            swap(comp[i], comp[j]);
            i++;
        }
    }
    swap(comp[i], comp[r]);
    return i;
}

/***********************************************************
 * Function: kthselec                                      *
 * ------------------                                      *
 *  @arg comp: the array of cyclists                       *
 *  @arg l:    begging of the subarray                     *
 *  @arg r:    end of the subarray                         *
 *  @arg k:    the index of the desired cyclist if the     *
 *             array was sorted using the dist field       *
 *                                                         *
 *  @return:   the kth element in the comp array if it was *
 *             sorted using the dist field                 *
 ***********************************************************/
cyclist* kthselect(cyclist** comp, int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int pos = partition(comp, l, r);

        if (pos-l == k-1)
            return comp[pos];
        if (pos-l > k-1)
            return kthselect(comp, l, pos-1, k);

        return kthselect(comp, pos+1, r, k-pos+l-1);
    }

    return NULL;
}

/**********************************************************
 * Function: addScore                                     *
 * ------------------                                     *
 *  @arg comp:  the array of cyclists                     *
 *  @arg ncomp: the number of elements in the comp array  *
 *  @arg k:     the index of the desired cyclist if the   *
 *              array was sorted using the dist field     *
 *                                                        *
 *  @process:   select the kth element in the comp array, *
 *              if the array was sorted using the dist    *
 *              field, and adds the number of points      *
 *              that the cyclist deserve.                 *
 *              Returns doing nothing if the k is equal   *
 *              or greater than 5                         *
 *                                                        *
 *  @return:    void function                             *
 **********************************************************/
void addScore (cyclist** comp, int ncomp, int k) {
    int scores[] = {5, 3, 2, 1};
    cyclist** caux = malloc(ncomp * sizeof(cyclist*));
    for (int i = 0; i < ncomp; i++){
        caux[i] = malloc(sizeof(cyclist));
        *caux[i] = *comp[i];
    }
    cyclist* c = kthselect(caux, 0, ncomp, (ncomp - k - 1));
    printf("passou\n");
        
    c->score += scores[k];
}

void addScoreSpecial (cyclist** comp, int ncomp) {
    cyclist** caux = malloc(ncomp * sizeof(cyclist*));
    for (int i = 0; i < ncomp; i++)
        caux[i] = comp[i];
    cyclist* a = kthselect(caux, 0, ncomp, 0);
    cyclist* b = kthselect(caux, 0, ncomp, 1);
    if (b->lap + 1 >= a->lap)
        a->score += 20;
}
