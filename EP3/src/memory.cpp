#include "memory.h"

Memory::Memory (int phys, int virt, int unity, int spage) :
    phys(phys), virt(virt),
    unity(unity), spage(spage)
{
}

Memory::~Memory () {
    phys = virt = unity = spage = 0;
}
