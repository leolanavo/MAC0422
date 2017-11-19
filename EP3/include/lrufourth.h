#ifndef LRUFOURTH_H
#define LRUFOURTH_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include "memory.h"
#include "check_empty.h"

void lrufourth_init(Memory mem);

bool lrufourth_access(int addr, Memory mem, Process p);

#endif
