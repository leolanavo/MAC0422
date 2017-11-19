#include "shell.h"

using namespace std;

void simulate (assemb& proc_info, int id_fit=1, int id_page=1, int interval=1) {
    
    int i, time, counter_pf;
    bool page_fault = false;
    i = time = counter_pf = 0;
    list<Process> running;

    auto m = lrusecond_init(proc_info.mem.page_list.size());
    list<page> fifo_pages = list<page>(0);   

    while ((unsigned int)i < proc_info.plist.size() || !running.empty()) {

        list<Process>::iterator it;
        for (it = running.begin(); it != running.end(); it++) {
            if (time >= it->tf) {
                if (id_fit == 3) proc_info.mem.quick_free_process(*it);
                else proc_info.mem.free_process(*it);

                it = running.erase(it);
            }
        }

        while ((unsigned int)i < proc_info.plist.size() && time == proc_info.plist[i].t0) {
            if (proc_info.plist[i].name == "COMPACTAR")
                proc_info.mem.compact(proc_info.plist);
            else {
                switch (id_fit) {
                    case 1:
                        proc_info.mem.best_fit(proc_info.plist[i]);
                        break;
                    case 2:
                        proc_info.mem.worst_fit(proc_info.plist[i]);
                        break;
                    case 3:
                        proc_info.mem.quick_fit(proc_info.plist[i]);
                        break;
                }
                running.push_back(proc_info.plist[i]);
            }

            //proc_info.mem.print_virtual_memory();
            i++;
        }
        

        //Acessos
        if (time < proc_info.access_list.size()) {
            auto ac_list = proc_info.access_list[time];
            for (auto it = ac_list.begin(); it != ac_list.end(); it++) {
                Process p = proc_info.mem.get_process(it->pid, proc_info.plist);
                switch (id_page) {
                    case 1:
                        page_fault = optimal_access(it->pos, time, proc_info.mem, 
                                       proc_info.access_list, p, proc_info.plist);
                        break;
                    case 2:
                        page_fault = fifo_access(it->pos, proc_info.mem, fifo_pages, p);
                        break;
                    case 3:
                        page_fault = lrusecond_access(it->pos, proc_info.mem, m, p);
                        break;
                    case 4:
                        page_fault = lrufourth_access(it->pos, proc_info.mem, p);
                        break;
                }

                if (page_fault) {
                    //proc_info.mem.print_phys_memory();
                    counter_pf++;
                    page_fault = false;
                }  
            }
        }
        
        /*if (time % interval == 0) {
            proc_info.mem.print_memory();
            proc_info.mem.print_bitmap();
        }*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
        time++;        
    }
}

/* Receives nothing.
 *
 * Execute the prompt for executing the functions of the
 * assingment.
 *
 * Returns nothing.
 */
void prompt() {
    assemb proc_info;
    int id_fit, id_page, interval;

    while (true) {
        cout << "[ep3]: ";

        string cmd_line;
        getline(cin, cmd_line);
        auto cmd_vector = split_spaces(cmd_line);

        auto cmd = cmd_vector[0];
        auto arg = cmd_vector[1];

        if (cmd == "carrega")
            proc_info = read_file(arg);

        else if (cmd == "espaco")
            id_fit = stoi(arg);

        else if (cmd == "substitui")
            id_page = stoi(arg);

        else if (cmd == "executa") {
            interval = stoi(arg);
            simulate(proc_info, id_fit, id_page, interval);
        }

        else if (cmd == "sai")
            return;

        else
            cout << "Comando não encontrado" << endl;
    }
}
