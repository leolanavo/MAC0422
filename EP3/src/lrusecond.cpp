#include "lrusecond.h"

using namespace std;

matrix lrusecond_init(int size) {
    matrix m (size, vector<int>(size));
    return m;
}

// Only finds which page has to be replaced
void replace_page(int addr, Memory& mem, matrix& m, Process p) {
    int min = numeric_limits<int>::max();
    int sub_index = 0, val;
    int page_index = mem.get_page(addr, p);

    if (check_empty(addr, mem, p))
        return;

    for (int i = 0; m.size(); i++) {
        val = 0;
        for (int j = 0; j < m[i].size(); j++)
            val += m[i][j] * ((int) pow(2.0, (double) m[i].size() - j - 1));

        if (val < min) {
            min = val;
            sub_index = i;
        }
    }

    mem.frame_list[mem.page_list[sub_index].addr] = page_index;
    mem.page_list[page_index] = {mem.page_list[sub_index].addr, 1, 0, 1};
    mem.page_list[sub_index] = {-1, 0, 0, 0};
}

bool lrusecond_access(int addr, Memory& mem, matrix& m, Process p) {

    bool page_fault = !(mem.is_loaded(addr, p));

    if (page_fault)
        replace_page(addr, mem, m, p);

    int page_index = mem.get_page(addr, p);

    mem.page_list[page_index].r = 1;

    for (int i = 0; i < m.size(); i++) {
        m[page_index][i] = 1;
        m[i][page_index] = 0;
    }

    return page_fault;
}

