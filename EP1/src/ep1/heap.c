#include <stdio.h>
#include <stdlib.h>
#include "../../include/ep1/types.h"

int greater (heap h, int index_1, int index_2) {
	return h.min_pq[index_1].times[3] > h.min_pq[index_2].times[3];
}

void exchange (heap h, int index_1, int index_2) {
	process tmp = h.min_pq[index_1];
	h.min_pq[index_1] = h.min_pq[index_2];
	h.min_pq[index_2] = tmp;
}

void swim (int k, heap h) {
	while (k > 1 && greater(h, k/2, k)) {
		exchange(h, k/2, k);
		k = k/2;
	}
}

void insert (heap h, process entry) {
	h.min_pq[++h.pr_total] = entry;
	swim(h.pr_total, h);
}

void sink (int k, heap h) {
	int j;
	while (2*k <= h.pr_total) {
		j = 2*k;
		if (j < h.pr_total && greater(h, j, j + 1)) j++;
		if (!greater(h, k, j)) break;
		exchange(h, k, j);
		k = j;
	}
}

heap minPQ (int size) {
	heap h;

	h.min_pq = malloc(size + 1);
	h.size = size + 1;
	h.pr_total = 0;

	return h;
}

process delMin (heap h) {
	process min;
	
	if (h.pr_total == 0) {
		min.name = NULL;
		min.times[0] = min.times[1] = min.times[2] = min.times[3] = 0; 
	}
	else {		
		min = h.min_pq[1];
		exchange (h, 1, h.pr_total--);
		sink(1, h);
	}

	return min;	
}
