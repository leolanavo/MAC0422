#include "fifo.h"

using namespace std;

bool fifo_access(int addr, Memory& mem, list<page>& l, const Process& p) {

    int page_index = mem.get_page(addr, p);
    auto it = --l.cend();

    if (mem.page_list[page_index].p == 1) return false;

	for (unsigned int i = 0; mem.frame_list.size(); i++) {
        if (mem.frame_list[i] == -1) {
            mem.page_list[page_index] = {(int)i, 1, 0, 1, 0};
            mem.frame_list[i] = page_index;

            l.push_front(mem.page_list[page_index]);
    		mem.load_phys(page_index, i);
            
            return true;
        }
    }

    mem.page_list[mem.frame_list[it->addr]] = {-1, 0, 0, 0, 0};
    mem.load_phys(page_index, it->addr);
    mem.frame_list[it->addr] = page_index;
    l.push_front({it->addr, 1, 0, 1, 0});
    l.erase(it);
    return true;
}