#ifndef VELODROME_H
#define VELODROME_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"
#include "cyclist.h"

/* Construct a velodrome*, with a matrix length X 10 as the velodrome
 * matrix */
velodrome* construct_velodrome (uint length, uint ncomp, cyclist** comp);

/* Construct a cyclist** with ncomp cyclist*, each cyclist is created
 * according to the standard initial values */
cyclist** construct_competitors (uint ncomp);

/* Frees the matrix that represents the velodrome */
void destroy_velodrome(velodrome* v);

/* Frees the array that represents the competitors of the race */
void destroy_competitors (cyclist** c, uint size);

#endif