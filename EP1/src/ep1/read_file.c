#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int times[4];
} process;

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

void read_time (FILE* filename, process* p) {
    int spaces = 0;
    int times[4];
    char c;
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

char* realloc_str(int size, char* str) {
    char* tmp = malloc(2*size*sizeof(char));
    for (int i = 0; i < size; i++)
        tmp[i] = str[i];
    free(str);
    return(str);
}

process* parse_line (FILE* filename) {
    process* p = malloc(sizeof(process*)); 
    char c = 0; 
    int space;
    
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

int main (int argc, char **argv) {
    FILE* filename = fopen(argv[1], "r");
    
    int fsize = count_lines(filename);
    process** plist = malloc(fsize * sizeof(process));

    for (int i = 0; i < fsize; i++) {
        plist[i] = parse_line(filename);
    }
}
