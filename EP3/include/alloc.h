#ifndef ALLOC_H
#define ALLOC_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* Class: alloc
 * ------------
 *   Fields:
 *     pid   : the process pid
 *     base  : the virtual memory base
 *     size  : the the virtual memory size
 */
class Alloc {
  public:
	int pid;
	int base, size;

    //Methods
    bool operator==(const Alloc& b);
    void operator<<(ostream& os);
    bool operator<(const Alloc& b);
};

#endif
