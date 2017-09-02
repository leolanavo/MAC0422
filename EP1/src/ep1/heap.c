#include <stdio.h>
#include <stdlib.h>
#include "../include/ep1/types.h"

int greater (process *p, int index_1, int index_2) {
	return p[index_1].times[3] > p[index_2].times[3];
}

void exchange (process *p, int index_1, int index_2) {
	process tmp = p[index_1];
	p[index_1] = p[index_2];
	p[index_2] = tmp;
}

void sink (int k, process *p, int total) {
	int j;
	while (2*k <= total) {
		j = 2*k;
		if (j < total && greater(p, j, j + 1)) j++;
		if (!greater(p, k, j)) break;
		exchange(p, k, j);
		k = j;
	}
}

process* minPQ (process **p, int pr_total) {
	process *pr_heap = malloc(pr_total + 1);
	
	for (int i = 0; i < pr_total; i++)
		pr_heap[i + 1] = *p[i];
	
	for (int k = pr_total/2; k >= 1; k--)
		sink(k, pr_heap, pr_total);

	return pr_heap;
}

process delMin (process *p, int total) {
	if (total > 0) {
		process min = p[1];
		exchange (p, 1, total--);
		sink(1, p, total);
		return min;
	}
}
