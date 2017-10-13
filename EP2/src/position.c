#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "types.h"
#include "cyclist.h"

void swap(cyclist** comp, int a, int b) {
    cyclist* tmp = comp[a];
    comp[a] = comp[b];
    comp[b] = tmp;
}

int partition(cyclist** comp, int l, int r) {
    cyclist *c = comp[r];
    int i = l;
    for (int j = l; j < r; j++) {
        if (comp[j]->score <= c->score) {
            swap(comp, i, j);
            i++;
        }
    }
    swap(comp, i, r);
    return i;
}

void getPos (cyclist** comp, int ncomp, int k, int id) {
    cyclist** caux = copy_array(comp, ncomp);
    swap(comp, id, ncomp - 1);
    return partition(comp, 0, ncomp);
}