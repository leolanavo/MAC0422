#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

typedef unsigned int uint;
typedef short unsigned int suint;

// Define the boolean type
typedef suint bool;
#define true 1
#define false 0

/****************************************************************
 * Struct: cyclist                                              *
 * ------------                                                 *
 *   @param th:     the thread that represents the cyclist      *
 *   @param speed:  the current speed of a cyclist              *
 *   @param dist:   the current traveled distance of a cyclist  *
 *   @param track:  the current track of a cyclist              *
 *   @param meter:  the current meter of a cyclist              *
 *   @param score: the current score of a cyclist               *
 ****************************************************************/
typedef struct {
    pthread_t* th;
    uint speed;
    int dist;
    uint score;
} cyclist;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param length: length of the velodrome                  *
 *   @param tracks: matrix of integers to identify where     *
 *                  the cyclists are                         *
 *************************************************************/
typedef struct {
    uint length;
    uint** tracks;
} velodrome;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param competitors: array of cyclists in the race       *
 *   @param v:           represents a velodrome              *
 *   @param laps:        number of laps in the race          *
 *   @param ncomp:       number of competitors in the race   *
 *************************************************************/
typedef struct {
    cyclist** competitors;
    velodrome* v;
    uint laps;
    uint ncomp;
} race;

#endif
