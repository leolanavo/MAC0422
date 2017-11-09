#ifndef MEMORY_H
#define MEMORY_H

using namespace std;

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
  public:

    // Constructor
    Memory(int phys, int virt, int unity, int spage);
    ~Memory();
};

#endif
