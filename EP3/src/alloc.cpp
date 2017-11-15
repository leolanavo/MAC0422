#include "alloc.h"

bool Alloc::operator==(const Alloc& b) {
    return base == b.base && size == b.size && pid == b.pid;
}

void Alloc::operator<<(ostream& os) {
    os << base << " " << size << " " << pid;
}

bool Alloc::operator<(const Alloc& b) {
    return base < b.base;
}
