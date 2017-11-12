#include "lrusecond.h"

using namespace std;

matrix init(int size) {
    matrix m;
    m.resize(size);
    for (int i = 0; i < size; i++)
        m[i].resize(size);
}

// Only finds which page has to be replaced
void replace_page(int address, Memory mem, matrix m) {
    int min = std::numeric_limits<int>::max();
    int index = 0, val;

    for (int i = 0; m.size(); i++) {
        val = 0;
        for (int j = 0; m.size(); j++)
            val += m[i][j] * ((int) pow(2.0, (double) m.size() - j - 1));
        if (val < min) {
            min = val;
            index = i;
        }
    }

    // Substituir o page frame indicado por index
}

void access(int addr, Memory mem, matrix m, Process p) {
    bool page_fault = mem.isLoaded(addr, p);

    if (page_fault)
        replace_page(addr, mem, m);

    int k = mem.get_page_frame(addr);
    for (int i = 0; i < m.size(); i++) {
        m[k][i] = 1;
        m[i][k] = 0;
    }
}

