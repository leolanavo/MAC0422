#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/ep1/types.h"

int greater (heap *h, int index_1, int index_2) {
	return h->min_pq[index_1]->times[3] > h->min_pq[index_2]->times[3];
}

void exchange (heap *h, int index_1, int index_2) {
	process *tmp = malloc(sizeof(process));
	*tmp = *(h->min_pq[index_1]);
	*(h->min_pq[index_1]) = *(h->min_pq[index_2]);
	*(h->min_pq[index_2]) = *tmp;
}

void swim (int k, heap *h) {
	while (k > 1 && greater(h, k/2, k)) {
		exchange(h, k/2, k);
		k = k/2;
	}
}

void insert_heap (heap *h, process *entry) {
	h->pr_total = h->pr_total + 1;
    h->min_pq[h->pr_total] = malloc(sizeof(process));
    h->min_pq[h->pr_total]->name = malloc(strlen(entry->name));
    strcpy(h->min_pq[h->pr_total]->name, entry->name);
    
    h->min_pq[h->pr_total]->times = malloc(4 * sizeof(double));
    for (int i = 0; i < 4; i++)
        h->min_pq[h->pr_total]->times[i] = entry->times[i];
	
    swim(h->pr_total, h);
}

void sink (int k, heap *h) {
	int j;
	while (2*k <= h->pr_total) {
		j = 2*k;
		if (j < h->pr_total && greater(h, j, j + 1)) j++;
		if (!greater(h, k, j)) break;
		exchange(h, k, j);
		k = j;
	}
}

heap* init_heap (int size) {
	heap *h = malloc(sizeof(heap));

	h->min_pq = malloc((size + 1) * sizeof(process*));
	h->size = size + 1;
	h->pr_total = 0;

	return h;
}

process* remove_heap (heap *h) {
	process *min;
	if (h->pr_total == 0) {
	    min = NULL; 
    }
	
    else {
    	min = malloc(sizeof(process));
        *min = *(h->min_pq[1]);
        exchange (h, 1, h->pr_total--);
        sink(1, h);
	}

	return min;	
}
