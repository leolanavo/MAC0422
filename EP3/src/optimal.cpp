#include "optimal.h"

using namespace std;

void replace_page(int addr, int current_time, Memory& mem,
            vector<list<Access>> access_list, Process p,
            vector<Process> plist) {

    int sub_index = -1;
    unsigned int time = (unsigned int)current_time;

    if (check_empty(addr, mem, p))
        return;

    for(unsigned int i = 0; i < mem.frame_list.size(); i++) {
        int index = mem.frame_list[i];
        bool skip = false;

        for (unsigned int j = current_time; j < access_list.size() && !skip; j++) {
            for (auto it = access_list[j].begin();
                 it != access_list[j].end() && !skip; it++) {

                Process paux = mem.get_process(it->pid, plist);
                if (paux.v_base != -1 && index == mem.get_page(it->pos, paux)) {
                    if (time < j) {
                        time = j;
                        sub_index = index;
                    }
                    skip = true;
                }
            }
        }
    }

    int page_index = mem.get_page(addr, p);
    mem.frame_list[mem.page_list[sub_index].addr] = page_index;
    mem.page_list[page_index] = {mem.page_list[sub_index].addr, 1, 0, 1, 0};
    mem.page_list[sub_index] = {-1, 0, 0, 0, 0};

}

bool optimal_access(int addr, int current_time, Memory& mem,
            const vector<list<Access>>& access_list, Process& p,
            const vector<Process>& plist) {
    bool page_fault = !(mem.is_loaded(addr, p));

    if (page_fault)
        replace_page (addr, current_time, mem, access_list, p, plist);
    
    int page_index = mem.get_page(addr, p);    
    mem.page_list[page_index].r = 1;

    return page_fault;
}   
