#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "process.h"
#include "linkedlist.h"
#include "node.h"

using namespace std;

/* Struct: page
 * ------------
 *   Fields:
 *     address : address in the virtual memory
 *     r       : the access bit
 *     m       : the write bit
 *     p       : the presence bit
 */
typedef struct {
    int address;
    bool r;
    bool m;
    bool p;
} page;

/* Struct: alloc
 * ------------
 *   Fields:
 *     pid   : the process pid
 *     base  : the virtual memory base
 *     size  : the the virtual memory size
 */
typedef struct {
	string pid;
	int base, size;
} alloc;


/* Class: Memory
 * -------------
 *  Fields:
 *      phys     : total physical memory space
 *      virt     : total virtual memory space
 *      unity    : memory unity for allocation
 *      spage    : size of a single page
 */
class Memory {
    int phys, virt, unity, spage;
    LinkedList<alloc> *free_mem, *used_mem;
    vector<page*> pglist;
  public:

    // Constructor
    Memory(int phys, int virt, int unity, int spage);
    int get_page(int access, Process p);
    int get_page_frame(int addr, Process p);
    bool isLoaded(int addr, Process p);
    void best_fit(Process p);
    void worst_fit(Process p);
    void quick_fit(Process p);
    ~Memory();
};

#endif
