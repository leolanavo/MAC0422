#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <list>
#include <cmath>

#include "process.h"
#include "alloc.h"

using namespace std;

/* Struct: page
 * ------------
 *   Fields:
 *     address : address in the physic memory
 *     r       : the access bit
 *     m       : the write bit
 *     p       : the presence bit
 */
struct page {
    int addr;
    bool r;
    bool m;
    bool p;
};

/* Class: Memory
 * -------------
 *  Fields:
 *      phys     : total physical memory space
 *      virt     : total virtual memory space
 *      unity    : memory unity for allocation
 *      spage    : size of a single page
 */
class Memory {
 public:
    int phys, virt, unity, spage;
    list<Alloc> free_mem, used_mem;
    vector<int> virtual_mem, phys_mem;
    vector<page> page_list;
    vector<int> frame_list;

    // Constructors
    Memory ();
    Memory(int phys, int virt, int unity, int spage);

    // Getters
    int get_page(int addr, Process p);

    // Other Methods
    bool is_loaded(int addr, Process p);
    void free_process(Process p);
    void best_fit(Process& p);
    void worst_fit(Process p);
    void quick_fit(Process p);
    ~Memory();
};

struct assemb {
	Memory mem;
	vector<Process> plist;
    vector<list<Access>> access_list;
};

#endif
