#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <list>
#include <cmath>
#include <fstream>

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
    int counter;
};

struct best_size {
	int freq;
	int size;
};

struct best_alloc {
	int size;
	list<Alloc> free_mem;
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
    list<best_alloc> opt_mem;

    // Constructors
    Memory ();
    Memory(int phys, int virt, int unity, int spage);

    // Getters
    int get_page(int addr, Process p);
    Process get_process(int pid,  vector<Process> plist);

    // Other Methods
    void load_phys(int page, int phys);
    bool is_loaded(int addr, Process p);
    void print_memory ();
    void print_bitmap();
    void print_phys_memory();
    void print_virtual_memory();
    void compact(vector<Process>& plist);
    void free_process(Process p);
    void best_fit(Process& p);
    void worst_fit(Process p);
    void update_lists();
    void generate_lists(list<best_size> l);
    void quick_free_process(Process p);
    void quick_fit(Process p);
};

struct assemb {
	Memory mem;
	vector<Process> plist;
    vector<list<Access>> access_list;
};

#endif
