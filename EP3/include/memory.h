#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
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
    int *free_mem, *used_mem;
    vector<page*> pglist;
  public:

    // Constructor
    Memory(int phys, int virt, int unity, int spage);
    int get_page(int access);
    bool isLoaded(int access);
    ~Memory();
};

#endif
