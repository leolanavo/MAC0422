#ifndef LRUSECOND_H
#define LRUSECOND_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#include "memory.h"
#include "process.h"

typedef vector<vector<int>> matrix;

matrix init(int size);

void replace_page(int addr, Memory mem, matrix m, Process p);

void lrusecond_access(int addr, Memory mem, matrix m, Process p);

#endif
