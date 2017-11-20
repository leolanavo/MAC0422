#ifndef SHELL_H
#define SHELL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#include "string_split.h"
#include "read.h"
#include "optimal.h"
#include "fifo.h"
#include "lrusecond.h"
#include "lrufourth.h"

struct assemb;

using namespace std;

void simulate(assemb& proc_info, int id_fit, int id_page, int interval);

/* Receives nothing.
 *
 * Execute the prompt for executing the functions of the
 * assingment.
 *
 * Returns nothing.
 */
void prompt();

#endif
