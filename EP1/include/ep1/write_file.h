#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ep1/types.h"

void write_file (FILE *f, process *p, double tf, double tr);

void write_file_context (FILE *f, int c);

void trace_line (char *p, int l, double t);

void result_line(char *p, int l);

void context_change (int c);

#endif
