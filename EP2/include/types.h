#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

typedef unsigned int uint;
typedef short unsigned int suint;

// Define the boolean type
typedef suint bool;
#define true 1
#define false 0

/*****************************************************************
 * Struct: cyclist                                               *
 * ------------                                                  *
 *   @param th:       the thread that represents the cyclist     *
 *   @param speed:    the current speed of a cyclist             *
 *   @param dist:     the current traveled distance of a cyclist *
 *   @param lap:      the current lap of the cyclist             *
 *   @param score:    the current score of a cyclist             *
 *   @param overtook: mark if the cyclist tried to overtake in   *
 *                    the previous iteration                     *
 *****************************************************************/
typedef struct {
    uint speed;
    int dist;
    uint lap;
    uint score;
    bool overtook;

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
    cyclist** comp;
    velodrome* v;
    uint total_laps;
    uint ncomp;
} race;

#endif
