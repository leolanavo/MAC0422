#include "memory.h"

using namespace std;

Memory::Memory () :
    phys(0), virt(0),
    unity(0), spage(0),
    page_list(0)
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
    virtual_mem(virt), phys_mem(phys),
    page_list(virt/spage),
    frame_list(phys/spage)
{
    Alloc mem = {-1, 0, virt};
    list<Alloc> tmp(1, mem);
    free_mem = tmp;

    for (int i = 0; i < virt/spage; i++) page_list[i].addr = -1;
    for (int i = 0; i < phys/spage; i++) frame_list[i] = -1;
}

/* Receives a position in the virtual memory and
 * a process.
 *
 * Returns the page frame according to the given
 * arguments.
 */
int Memory::get_page(int addr, Process p) {
    return ((addr + p.get_base())/spage);
}

Process Memory::get_process(int pid, vector<Process> plist) {
    for (int i = 0; i < plist.size(); i++) {
        if (pid == plist[i].pid)
            return plist[i];
    }
}

/* Receives a position in the virtual memory.
 *
 * Returns true if the page is loaded in the physical
 * memory. False otherwise.
 */
bool Memory::is_loaded(int addr, Process p) {
    int index = ((addr + p.get_base())/spage);
    return page_list[index].p;
}

void Memory::free_process(Process p) {

    auto find_p = used_mem.begin();

    while (find_p->pid != p.pid && find_p != used_mem.end()) find_p++;

    if (find_p != used_mem.end()) {
        Alloc node = {find_p->pid, find_p->base, find_p->size};
        used_mem.remove(node);

        node.pid = -1;
        for (auto it = used_mem.begin(); it != free_mem.end(); it++) {
            if (it->base + it->size == node.base ||
                node.base + node.size == it->base) {
                free_mem.remove(*it);
                node.base = node.base > it->base? it->base : node.base;
                node.size += it->size;
            }
        }

        auto it = used_mem.begin();
        while (it != free_mem.end() && *it < node)
            it++;
        free_mem.insert(it, node);
    }
}

/* Receives a process to allocate in the virtual memory,
 * using the "best fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::best_fit(Process& p) {
    int index, min_space;
    Alloc best, insert, reinsert, tmp;
    list<Alloc>::iterator it_list = free_mem.begin();
    list<Alloc>::iterator best_node = free_mem.begin();

    min_space = (int)ceil((double) p.b/unity) * unity;
    best = *(it_list++);

    while (it_list != free_mem.end()) {

        if (it_list->size < best.size && it_list->size >= min_space) {
            best = *(it_list);
            best_node = it_list;
        }

        index++;
        it_list++;
    }

    p.v_base = best_node->base;
    insert = {p.pid, best_node->base, min_space};
	tmp = {best_node->pid, best_node->base, best_node->size};

	for (int i = best_node->base; i < best_node->base + min_space; i++)
		virtual_mem[i] = p.pid;


    free_mem.remove(tmp);

    if (best_node->size != min_space) {
        reinsert.base = insert.base + min_space;
        reinsert.size = best_node->size - insert.size;
        reinsert.pid = -1;
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
