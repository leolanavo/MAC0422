#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "memory.h"
#include "tests.h"
#include "string_split.h"
#include "process.h"

typedef struct {
	Memory mem;
	vector<Process> plist;
} assemb;

/* Receives a filename.
 *
 * Reads and process the file according to the
 * specification of the assignment.
 *
 * Returns nothing.
 */
assemb read_file(string name);

#endif
