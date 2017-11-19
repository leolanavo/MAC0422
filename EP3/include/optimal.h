#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <vector>
#include <list>

#include "process.h"
#include "memory.h"
#include "check_empty.h"


bool access(int addr, int current_time, Memory mem,
            vector<list<Access>> access_list, Process p,
            vector<Process> plist);

#endif
