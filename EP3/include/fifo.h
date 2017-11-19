#ifndef FIFO_H
#define FIFO_H

#include <list>
#include "memory.h"
#include "process.h"

bool fifo_access(int addr, Memory& mem, list<page> l, Process p);

#endif