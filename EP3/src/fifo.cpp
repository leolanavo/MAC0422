#include "fifo.h"

using namespace std;

void fifo_access(int addr, Memory& mem, list<page> l, Process p) {

    int page_index = mem.get_page(addr, p);
    auto it = --l.cend();

    if (mem.page_list[page_index].p == 1) return;

	for (int i = 0; mem.frame_list.size(); i++) {
        if (mem.frame_list[i] == -1) {
            mem.page_list[page_index] = {i, 1, 0, 1};
            mem.frame_list[i] = page_index;

            l.push_front(mem.page_list[page_index]);
            mem.load_phys(page_index);
            return;
        }
    }

    mem.page_list[mem.frame_list[it->addr]] = {-1, 0, 0, 0};
    mem.frame_list[it->addr] = page_index;
    l.push_front({it->addr, 1, 0, 1});
    l.erase(it); 
}