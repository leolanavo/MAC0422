#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <vector>
#include <list>

#include "process.h"
#include "memory.h"
#include "check_empty.h"


bool optimal_access(int addr, int current_time, Memory& mem,
            const vector<list<Access>>& access_list, const Process& p,
            const vector<Process>& plist);

#endif
