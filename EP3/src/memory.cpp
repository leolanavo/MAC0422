#include "memory.h"


/* Receives the amount of space for the physical memory,
 * for the virtual memory, the allocation unity and
 * the size of a page.
 *
 * Constructs a memory from the given values.
 */
Memory::Memory (int phys, int virt, int unity, int spage) :
    phys(phys), virt(virt),
    unity(unity), spage(spage),
    pglist(virt/spage)
{
}

/* Receives a position in the virtual memory.
 *
 * Returns the page that corresponds to the given
 * address.
 */
int Memory::get_page(int access) {
    return access/spage;
}

/* Receives a position in the virtual memory.
 *
 * Returns true if the page is loaded in the physical
 * memory. False otherwise.
 */
bool Memory::isLoaded(int access) {
    int index = get_page(access);
    return pglist[index]->p;
}

/* Receives nothing.
 *
 * Destructs a memory object.
 */
Memory::~Memory () {
    phys = virt = unity = spage = 0;
}
