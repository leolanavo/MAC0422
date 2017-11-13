#include "memory.h"

Memory::Memory () :
    phys(0), virt(0),
    unity(0), spage(0),
    pglist(0)
{
}


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
    alloc mem;
    mem.pid = "empty";
    mem.base = 0;
    mem.size = virt;
    list<alloc> tmp(1, mem);
    free_mem = tmp;
}

/* Receives a position in the virtual memory.
 *
 * Returns the page that corresponds to the given
 * address.
 */
page Memory::get_page(int index) {
    return *(pglist[index]);
}

/* Receives a position in the virtual memory and
 * a process.
 *
 * Returns the page frame according to the given
 * arguments.
 */
int Memory::get_page_frame(int addr, Process p) {
    int index = ((addr + p.get_base())/spage);
    return (pglist[index]->addr*spage);
}

int Memory::get_page_size() {
    return spage;
}

int Memory::get_pglist_size() {
    return pglist.size();
}

vector<page*> Memory::get_page_list() {
    return pglist;
}

/* Receives a position in the virtual memory.
 *
 * Returns true if the page is loaded in the physical
 * memory. False otherwise.
 */
bool Memory::isLoaded(int addr, Process p) {
    int index = ((addr + p.get_base())/spage);
    return pglist[index]->p;
}

/* Receives a process to allocate in the virtual memory,
 * using the "best fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::best_fit(Process p) {
    int index, min_space;
    alloc best, insert, reinsert, tmp;
    list<alloc>::iterator it_list = free_mem.begin();
    list<alloc>::iterator best_node = free_mem.begin();

    min_space = (int)ceil((double) p.get_size()/unity) * unity;
    best = *(it_list++);

    while (it_list != free_mem.end()) {

        if (it_list->size < best.size && it_list->size >= min_space) {
            best = *(it_list);
            best_node = it_list;
        }

        index++;
        it_list++;
    }

    insert.pid = p.get_name();
    insert.base = best_node->base;
    insert.size = min_space;

    tmp.pid = best_node->pid;
    tmp.base = best_node->base;
    tmp.size = best_node->size;

    free_mem.remove(tmp);

    if (best_node->size != min_space) {
        reinsert.base = insert.base + min_space;
        reinsert.size = best_node->size - insert.size;
        free_mem.push_front(reinsert);
    }

    used_mem.push_front(insert);
}

/* Receives a process to allocate in the virtual memory,
 * using the "worst fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::worst_fit(Process p) {

}

/* Receives a process to allocate in the virtual memory,
 * using the "quick fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::quick_fit(Process p) {

}

/* Receives nothing.
 *
 * Destructs a memory object.
 */
Memory::~Memory () {
    phys = virt = unity = spage = 0;
}
