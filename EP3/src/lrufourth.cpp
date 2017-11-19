#include "lrufourth.h"

void lrufourth_access(Memory& mem) {
    for (int i = 0; i < mem.page_list.size(); i++)
        mem.page_list[i].counter = 0;
}

void replace_page(int addr, Memory& mem, Process p) {
    int min = numeric_limits<int>::max();
    int sub_index = 0, val;
    int page_index = mem.get_page(addr, p);

    if (check_empty(addr, mem, p))
        return;

    for (int i = 0; mem.page_list.size(); i++) {
        val = mem.page_list[i].counter;
        if (val < min) {
            min = val;
            sub_index = i;
        }
    }

    mem.frame_list[mem.page_list[sub_index].addr] = page_index;
    mem.page_list[page_index] = {mem.page_list[sub_index].addr, 1, 0, 1, 0};
    mem.page_list[sub_index] = {-1, 0, 0, 0, 0};
}

bool lrufourth_access(int addr, Memory& mem, const Process& p) {
    bool page_fault = !(mem.is_loaded(addr, p));

    if (page_fault)
        replace_page(addr, mem, p);
    int page_index = mem.get_page(addr, p);

    mem.page_list[page_index].r = 1;

    for (int i = 0; i < mem.page_list.size(); i++) {
        mem.page_list[i].counter >>= 1;
        mem.page_list[i].counter += mem.page_list[i].r *
            pow(2.0, mem.page_list.size() - 1);
    }

    mem.page_list[page_index].r = 1;
    return page_fault;
}
