#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/ep1/heap.h"
#include "../include/ep1/types.h"
#include "../include/ep1/read_file.h"

#ifndef SIMULATOR_H
#define SIMULATOR_H

void SJF (char* trace_file, char* result);

void Round_Robin (char* trace_file, char* result);

void Priority (char* trace_file, char* result);

void* processing (process p);

#endif
