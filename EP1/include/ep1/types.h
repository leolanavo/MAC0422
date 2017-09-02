#ifndef TYPES_H
#define TYPE_H

/* This structure has the process name, and a array with
 * initial time, duration time, deadline time and remaining
 * time to complete the task. */
typedef struct {
    char* name;
    int times[4];
} process;

#endif