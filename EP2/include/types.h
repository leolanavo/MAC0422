#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

typedef unsigned int uint;
typedef short unsigned int suint;

// Define the boolean type
typedef suint bool;
#define true 1
#define false 0

/*************************************************************
 * Struct: cyclist                                           *
 * ------------                                              *
 *   @param th:  the thread that represents the cyclist      *
 *   @param pos: the current position in meters of the       *
 *               cyclist in distance                         *
 *************************************************************/

typedef struct {
    pthread_t* th;
    double pos;
} cyclist;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param competitors: array of cyclists in the race       *
 *   @param length:      length of the velodrome             *
 *   @param laps:        number of laps in the race          *
 *   @param ncomp:       number of competitors in the race   *
 *************************************************************/

typedef struct {
    cyclist* competitors;
    double length;
    int laps;
    int ncomp;
} race;

#endif
