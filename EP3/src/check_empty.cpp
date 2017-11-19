#include "check_empty.h"

bool check_empty (int addr, Memory& mem, Process p) {
	
    int page_index = mem.get_page(addr, p);

	for (int i = 0; mem.frame_list.size(); i++) {
        if (mem.frame_list[i] == -1) {
            mem.page_list[page_index] = {i, 1, 0, 1};
            mem.frame_list[i] = page_index;
            mem.page_list[page_index].p = 1;
            return true;
        }
    }

    return false;
}