#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

typedef unsigned int uint;
typedef short unsigned int suint;

// Define the boolean type
typedef char bool;
#define true 1
#define false 0

#define TRACKS 10

/*****************************************************************
 * Struct: cyclist                                               *
 * ------------                                                  *
 *   @param speed:    the current speed of a cyclist             *
 *   @param dist:     the current traveled distance of a cyclist *
 *   @param lap:      the current lap of the cyclist             *
 *   @param id:       the identifier of a cyclist                *
 *   @param score:    the current score of a cyclist             *
 *   @param row:      the current row of a cyclist               *
 *   @param col:      the current column of a cyclist            *
 *   @param overtook: mark if the cyclist tried to overtake in   *
 *                    the previous iteration                     *
 *****************************************************************/
typedef struct {
    uint speed;
    int dist;
    uint lap;
    int id;
    uint score;
    uint row;
    uint col;
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
    int** tracks;
} velodrome;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param competitors: array of cyclists in the race       *
 *   @param v:           represents a velodrome              *
 *   @param nlaps:        number of laps in the race         *
 *   @param ncomp:       number of competitors in the race   *
 *************************************************************/
typedef struct {
    cyclist** comp;
    velodrome* v;
    pthread_t* th_comp;
    uint nlaps;
    uint ncomp;
} race;

typedef struct {
    int counter;
    int flag;
    pthread_mutex_t lock;
} barrier;

#endif
