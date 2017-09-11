#include <stdio.h>
#include <stdlib.h>
#include "../../include/ep1/types.h"

void write_file (FILE *f, process *p, double tf, double tr) {
    fprintf(f, "%s %.1lf %.1lf\n", p->name, tf, tr);
}

void write_file_context (FILE *f, int c) {
	fprintf(f, "%d", c);
}

void trace_line (char *p, int l, double t) {
	fprintf(stderr, "Arrival of: %s, input file line: %d, at instant: %.1lf\n", p, l, t);
    printf("\n");
}

void result_line(char *p, int l) {
	fprintf(stderr, "Exit of: %s, output file line: %d\n", p, l);
	printf("\n");
}

void context_change (int c) {
	fprintf(stderr, "Number of context changes so far: %d\n", c);
	printf("\n");
}
