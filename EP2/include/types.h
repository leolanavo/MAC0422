#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

// Define the boolean type
typedef char bool;
#define true 1
#define false 0

#define TRACKS 10

/* colors*/
#define RED          "\033[31m"
#define GREEN        "\033[32m"
#define YELLOW       "\033[33m"
#define BLUE         "\033[34m"
#define MAGENTA      "\033[35m"
#define CYAN         "\033[36m"
#define RED_BOLD     "\033[31;1m"
#define GREEN_BOLD   "\033[32;1m"
#define YELLOW_BOLD  "\033[33;1m"
#define BLUE_BOLD    "\033[34;1m"
#define MAGENTA_BOLD "\033[35;1m"
#define CYAN_BOLD    "\033[36;1m"
#define RESET        "\033[0m"

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
 *   @param move:     marks if the cyclist can or cannot move    *
 *   @param overtook: marks if the cyclist tried to overtake in  *
 *                    the previous iteration                     *
 *****************************************************************/
typedef struct {
    pthread_t th;
    int speed;
    int dist;
    int lap;
    int id;
    int score;
    int row;
    int col;
    int move;
    bool overtook;
    double ftime;
} cyclist;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param length: length of the velodrome                  *
 *   @param tracks: matrix of integers to identify where     *
 *                  the cyclists are                         *
 *************************************************************/
typedef struct {
    int length;
    int** tracks;
} velodrome;

struct cell {
    int id;
    int lap;
    bool check;
    struct cell* next;
};

typedef struct cell node;

typedef struct {
    node* head;
    int size;
} LinkedList;

/*************************************************************
 * Struct: race                                              *
 * ------------                                              *
 *   @param competitors: array of cyclists in the race       *
 *   @param v:           represents a velodrome              *
 *   @param nlaps:       number of laps in the race          *
 *   @param ncomp:       number of competitors in the race   *
 *************************************************************/
typedef struct {
    cyclist** comp;
    velodrome* v;
    LinkedList* broken_comp;
    int sprinter;
    int exit;
    int nlaps;
    int ncomp;
    int fixed_ncomp;
} race;

typedef struct {
    int counter;
    int flag;
    pthread_mutex_t op_lock;
} barrier;
#endif
