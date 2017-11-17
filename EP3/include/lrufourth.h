#ifndef LRUFOURTH_H
#define LRUFOURTH_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include "memory.h"

void lrufourth_init(Memory mem);

void lrufourth_access(int addr, Memory mem, Process p);

#endif
