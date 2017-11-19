#ifndef LRUSECOND_H
#define LRUSECOND_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include "memory.h"
#include "process.h"
#include "check_empty.h"

typedef vector<vector<int>> matrix;

matrix lrusecond_init(int size);

bool lrusecond_access(int addr, Memory& mem, matrix& m, Process& p);

#endif
