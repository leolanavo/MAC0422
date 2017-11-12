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
	alloc mem;
    mem.pid = "empty";
    mem.base = 0;
    mem.size = virt;
    free_mem->add(mem);
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
    alloc *aux, *best;
	int index, best_index, min_space;
	alloc node_aux, node_best, node_remove, node_insert;
    list<alloc>::iterator it_list = free_mem->begin();

	aux = ;
	best = free_mem->head;
	best_index = 0;
	index = 1;
	min_space = ((p.get_size()/unity) * unity) + ((p.get_size() % unity) * unity);

	while (aux != NULL) {

		node_aux = aux->get_data();
		node_best = best->get_data();

		if (node_aux.size < node_best.size && node_aux.size >= min_space) {
			best = aux;
			best_index = index;
		}

		index++;
		aux = aux->next;
	}

	node_remove = free_mem->remove(best_index);
	node_insert.pid = p.get_name();
	node_insert.base = node_remove.base;
	node_insert.size = min_space;

	if (node_remove.size != min_space) {
		node_remove.base = node_insert.base + min_space;
		node_remove.size = node_remove.size - node_insert.size;
		free_mem->push_front(node_remove);
	}

	used_mem->push_front(node_insert);
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
