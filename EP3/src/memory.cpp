#include "memory.h"

using namespace std;

Memory::Memory () :
    phys(0), virt(0),
    unity(0), spage(0),
    page_list(0)
{
}


/* Receives the amount of space for the physical memory,
 * for the virtual memory, the allocation unity and
 * the size of a page.
 *
 * Constructs a memory from the given values.
 */
Memory::Memory (int phys, int virt, int unity, int spage) :
    phys(phys), virt(virt),
    unity(unity), spage(spage),
    virtual_mem(virt), phys_mem(phys),
    page_list(virt/spage),
    frame_list(phys/spage)
{
    Alloc mem = {-1, 0, virt};
    list<Alloc> tmp(1, mem);
    free_mem = tmp;
    opt_mem = list<best_alloc>(0); 

    for (int i = 0; i < virt; i++) virtual_mem[i] = -1;
    for (int i = 0; i < phys; i++) phys_mem[i] = -1;
    for (int i = 0; i < virt/spage; i++) page_list[i].addr = -1;
    for (int i = 0; i < phys/spage; i++) frame_list[i] = -1;
}

/* Receives a position in the virtual memory and
 * a process.
 *
 * Returns the page frame according to the given
 * arguments.
 */
int Memory::get_page(int addr, Process& p) {
    return ((addr + p.v_base)/spage);
}

Process Memory::get_process(int pid, vector<Process>& plist) {
    for (int i = 0; i < plist.size(); i++) {
        if (pid == plist[i].pid)
            return plist[i];
    }
}

void Memory::load_phys(int page, int phys) {
    int v_start, p_start;
    v_start = page*spage;
    p_start = phys*spage;

    for (int i = v_start, j = p_start; i < v_start + spage; i++, j++)
        phys_mem[j] = virtual_mem[i];
}

/* Receives a position in the virtual memory.
 *
 * Returns true if the page is loaded in the physical
 * memory. False otherwise.
 */
bool Memory::is_loaded(int addr, Process& p) {
    int index = ((addr + p.get_base())/spage);
    if (page_list[index].p == 0) return false;
    return true;
}

void Memory::print_memory () {
    cout << "indíce : Virtual | Física" << endl;
    for (int i = virtual_mem.size() - 1; i >= 0; i--) {

        if (i > phys_mem.size())
            cout << i << " : " << virtual_mem[i] << endl;
        else    
            cout << i << " : " << virtual_mem[i] << " | " << phys_mem[i] << endl;
    }
}

void Memory::print_phys_memory() {
    ofstream file ("/tmp/ep3.mem");
    for (int i = phys_mem.size() - 1; i >= 0; i--) {
        file << i << " : " << phys_mem[i] << endl;
    }
    file.close();
}

void Memory::print_virtual_memory() {
    ofstream file ("/tmp/ep3.virt");
    for (int i = virtual_mem.size() - 1; i >= 0; i--) {
        file << i << " : " << virtual_mem[i] << endl;
    }
    file.close();
}

void Memory::print_bitmap () {
    for (int i = 0; i < virtual_mem.size(); i += unity) {
        int bit = virtual_mem[i] != -1 ? 1 : 0;
        cout << bit;
    }
    cout << endl;
}

void Memory::print_free_memory() {
    for (auto it = free_mem.begin(); it != free_mem.end(); it++)
        cout << it->base << " || " << it->size << endl;
    cout << endl;
}

void Memory::print_used_memory() {
    for (auto it = used_mem.begin(); it != used_mem.end(); it++)
        cout << it->pid << " || " << it->base << " || " << it->size << endl;
    cout << endl;
}

void Memory::print_page_list() {
    for (int i = 0; i < page_list.size(); i++)
        cout << page_list[i].addr << " | " << page_list[i].p << endl;
    cout << endl;
}

void Memory::print_frame_list() {
    for (int i = 0; i < frame_list.size(); i++)
        cout << frame_list[i] << endl;
    cout << endl;
}

void print_plist(vector<Process> plist) {
    cout << "==========" << endl;
    for(int i = 0; i < plist.size(); i++)
        cout << plist[i].pid << " | " << plist[i].v_base << endl;
    cout << endl;
}

void Memory::update_lists() {
    for (auto it = opt_mem.begin(); it != opt_mem.end(); it++) {
        it->free_mem.clear();

        for (auto jt = free_mem.begin(); jt != free_mem.end(); jt++) {
            int n = jt->size/it->size;
            for (int i = 0, base = jt->base; i < n; i++, base += it->size) {
                it->free_mem.push_back({-1, base, it->size});
            }
        }
    }

}

void Memory::compact(vector<Process>& plist) {
    list<Alloc> used_aux, free_aux;
    int base, total_used; 
    base = 0;

   for (auto it = used_mem.begin(); it != used_mem.end(); it++) {
        used_aux.push_back({it->pid, base, it->size});
        
        for (int i = 0; i < plist.size(); i++)
            if (it->pid == plist[i].pid)
                plist[i].v_base = base;

        base += it->size;
    }

    for (int i = 0; i < phys; i++) phys_mem[i] = -1;
    for (int i = 0; i < virt/spage; i++) page_list[i].addr = -1;
    for (int i = 0; i < phys/spage; i++) frame_list[i] = -1;
    
    free_mem.clear();
    free_aux.push_back({-1, base, virt - base});
    free_mem = free_aux;
    used_mem = used_aux;
}

void Memory::free_process(Process& p) {
    bool append = false;
    int pg_frame;

    int min_space = (int)ceil((double) p.b/unity) * unity;

    for (int i = p.v_base; i < p.v_base + min_space; i++) {
        virtual_mem[i] = -1;
        pg_frame = page_list[i/spage].addr;    
        
        for(int j = pg_frame*spage; j < pg_frame*spage + spage; j++)
            phys_mem[j] = -1;
            
        page_list[i/spage].addr = -1;
        page_list[i/spage].p = 0;

        frame_list[pg_frame] = -1;
    }

    Alloc node = {p.pid, p.v_base, min_space};
    used_mem.remove(node);

    node.pid = -1;
    auto it = free_mem.begin();
    for (; it != free_mem.end() && !append; it++) {
        
        if (it->base + it->size == node.base) {
            node.base = it->base;
            node.size = node.size + it->size;
            it = free_mem.erase(it);
            append = true;
        }

        if (node.base + node.size == it->base) {
            node.size = node.size + it->size;
            it = free_mem.erase(it);
            append = true;
        }
    }

    it = free_mem.begin();
    for (; it != free_mem.end() && it->base < node.base; it++);
    it = free_mem.insert(it, node);

}

/* Receives a process to allocate in the virtual memory,
 * using the "best fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::best_fit(Process& p) {
    int index, min_space;
    Alloc best, insert, reinsert, tmp;
    auto it_list = free_mem.begin();
    auto best_node = free_mem.begin();

    min_space = (int)ceil((double) p.b/unity) * unity;
    best = *(it_list++);

    while (it_list != free_mem.end()) {

        if ((it_list->size < best.size && it_list->size >= min_space) || best.size < min_space) {
            best = *(it_list);
            best_node = it_list;
        }

        index++;
        it_list++;
    }

    p.v_base = best_node->base;
    insert = {p.pid, best_node->base, min_space};
	tmp = {best_node->pid, best_node->base, best_node->size};

	for (int i = best_node->base; i < best_node->base + min_space; i++)
		virtual_mem[i] = p.pid;

    if (best_node->size > min_space) {
        reinsert.base = insert.base + min_space;
        reinsert.size = best_node->size - insert.size;
        reinsert.pid = -1;
        free_mem.insert(best_node, reinsert);
    }

    free_mem.remove(tmp);
    used_mem.push_back(insert);
}

/* Receives a process to allocate in the virtual memory,
 * using the "worst fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::worst_fit(Process& p) {
    int index, min_space;
    Alloc best, insert, reinsert, tmp;
    auto it_list = free_mem.begin();
    auto best_node = free_mem.begin();

    min_space = (int)ceil((double) p.b/unity) * unity;
    best = *(it_list++);

    while (it_list != free_mem.end()) {

        if ((it_list->size > best.size && it_list->size >= min_space) || best.size < min_space) {
            best = *(it_list);
            best_node = it_list;
        }

        index++;
        it_list++;
    }

    p.v_base = best_node->base;
    insert = {p.pid, best_node->base, min_space};
    tmp = {best_node->pid, best_node->base, best_node->size};

    for (int i = best_node->base; i < best_node->base + min_space; i++)
        virtual_mem[i] = p.pid;

    if (best_node->size > min_space) {
        reinsert.base = insert.base + min_space;
        reinsert.size = best_node->size - insert.size;
        reinsert.pid = -1;
        free_mem.insert(best_node, reinsert);
    }

    free_mem.remove(tmp);
    used_mem.push_back(insert);
}

bool compare_freq (const best_size& b1, const best_size& b2) {
    return (b1.freq < b2.freq);
}

bool compare_size (const best_alloc& a1, const best_alloc& a2) {
    return (a1.size < a2.size); 
}

void Memory::generate_lists(list<best_size>& l) {
    int n, ac_freq, min_size, offset;
    n = l.size()/3;
    ac_freq = 0;
    l.sort(compare_freq);
    
    auto it = --l.end();
    for (int i = 0; i < n; i++, it--) 
        ac_freq += it->freq;

    it = --l.end();
    for (int i = 0; i < n; i++, it--) {   
        min_size = (int)ceil((double) it->size/unity) * unity;
        offset = virt/min_size;
        list<Alloc> l;
        
        for (int j = 0; j < virt; j += offset)
            l.push_back({-1, j, min_size});    

        opt_mem.push_back({min_size, l});
    }

    opt_mem.sort(compare_size);
}


void Memory::quick_free_process (Process& p) {
    free_process(p);
    update_lists();
}


/* Receives a process to allocate in the virtual memory,
 * using the "quick fit" algorithm.
 *
 * Returns nothing.
 */
void Memory::quick_fit(Process& p) {
    auto it = opt_mem.begin();    
    int min_size = (int)ceil((double) p.b/unity) * unity;   

    for (; it != opt_mem.end() 
         && it->size >= min_size; it++);   
    Alloc& a = it->free_mem.front();

    for (auto it1 = free_mem.begin(); it1 != free_mem.end(); it1++) {
        if (a.base == it1->base) {
            it1 = free_mem.insert(it1, {-1, a.base + a.size, it1->size - a.size});
            it1 = free_mem.erase(it1);
        }

        else if (a.base > it1->base && a.base <= it1->base + it1->size - 1) {
            it1 = free_mem.insert(it1, {-1, it1->base, a.base - it1->base});
            it1 = free_mem.insert(it1, {-1, a.base + a.size, it1->size - a.size - a.base + it1->base});
            it1 = free_mem.erase(it1);
        }
    }

    used_mem.push_back({p.pid, a.base, a.size});
}