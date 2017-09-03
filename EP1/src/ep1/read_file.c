#include <stdio.h>
#include <stdlib.h>
#include "../../include/ep1/types.h"

/* Frees alloced memorie for the process structured */
void destroy_process(process* p) {
    free(p->name);
    free(p);
}

/* Receives a file pointer, and return the number of lines
 * of the files. */
int count_lines(FILE* filename) {
    int i = 0;
    char c;
    do {
        c = fgetc(filename);
        if (c == '\n') i++;
    } while (c != EOF);
    rewind(filename);
    return i;
}

/* Receives a file pointer, and return the number of lines
 * of the files. */
void read_time (FILE* filename, process* p) {
    int spaces = 0;
    char c;
    p->times = malloc(4 * sizeof(double));
    while (spaces < 3) {
        c = fgetc(filename);
        if (c != ' ') {
            p->times[spaces] *= 10;
            p->times[spaces] += (c - 48);
        }
        else {
            spaces++;
        }
    }
}

/* Receives a file pointer and a process pointer, and inserts
 * the times in the times vector of the process pointer.*/
char* realloc_str(int size, char* str) {
    char* tmp = malloc(2*size*sizeof(char));
    for (int i = 0; i < size; i++)
        tmp[i] = str[i];
    free(str);
    return(str);
}

/* Receives an string and its size, and return the same string
 * with the same content, but with double the size alloced. */
process* parse_line (FILE* filename) {
    process* p = malloc(sizeof(process*)); 
    
    // Read times
    read_time(filename, p);

    // Read process name
    int i = 0;
    int size = 16;
    p->name = malloc(size * sizeof(char));

    for (char c = fgetc(filename); c != '\n' && c != EOF; c = fgetc(filename)) {
        if (i >= size) {
            p->name = realloc_str(size, p->name);
            size *= 2;
        }
        p->name[i] = c;
        i++;
    }
    
    return p;
}

/* Receives a file pointer and an integer pointer, which is the 
 * number of lines in the file. Return an array of process's pointers
 * with the file's data. */
process** get_process (FILE* filename, int* size) {
    int fsize = count_lines(filename);
    process** plist = malloc(fsize * sizeof(process));

    for (int i = 0; i < fsize; i++) {
        plist[i] = parse_line(filename);
    }
    *size = fsize;
    return plist;
}
