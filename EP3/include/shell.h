#ifndef SHELL_H
#define SHELL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "string_split.h"
#include "read.h"
#include "lrusecond.h"

struct assemb;

using namespace std;

void simulate(assemb proc_info, int id_fit, int id_page, int interval);

/* Receives nothing.
 *
 * Execute the prompt for executing the functions of the
 * assingment.
 *
 * Returns nothing.
 */
void prompt();

#endif
