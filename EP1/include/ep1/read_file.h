#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ep1/types.h"

/* Frees alloced memorie for the process structured */
void destroy_process(process* p);

/* Receives a file pointer, and return the number of lines
 * of the files. */
int count_lines(FILE* filename);

/* Receives a file pointer and a process pointer, and inserts
 * the times in the times vector of the process pointer.*/
void read_time (FILE* filename, process* p);

/* Receives an string and its size, and return the same string
 * with the same content, but with double the size alloced. */
char* realloc_str(int size, char* str);

/* Receives a file pointer, reads a line of the file and parse
 * it to fit the struct of the process pointer. Return the
 * process pointer with data. */
process* parse_line (FILE* filename);

/* Receives a file pointer and an integer pointer, which is the 
 * number of lines in the file. Return an array of process's pointers
 * with the file's data. */
process** get_process (FILE* filename, int* size);

#endif
