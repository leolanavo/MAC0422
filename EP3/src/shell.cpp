#include "shell.h"

using namespace std;

void simulate (assemb proc_info, int id_fit, int id_page, int interval) {
    int time = 0;

    auto m = init(proc_info.mem.page_list.size());

    for (int i = 0; i < proc_info.plist.size(); ) {
        
        //Acessos
        auto ac_list = proc_info.access_list[time];
        for (auto it = ac_list.begin(); it != ac_list.end(); it++) {
            Process p = proc_info.mem.get_process(it->pid, proc_info.plist);
            switch (id_page) {
                case 1:
                    lrusecond_access(it->pos, proc_info.mem, m, p);
                    break;
                /*case 2:
                    break;
                case 3:
                    break;*/
            }
        }

        if (time == proc_info.plist[i].t0) {
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

            i++;
        }

        time++;        
    }
    /*
    for (int i = 0; i < (proc_info.mem.virt/proc_info.mem.spage); i++)
        cout << proc_info.mem.page_list[i].addr << endl;
    cout << endl;
    for (int i = 0; i < (proc_info.mem.phys/proc_info.mem.spage); i++)
        cout << proc_info.mem.frame_list[i] << endl;
    cout << endl;
    for (int i = 0; i < proc_info.mem.virt; i++)
            cout << proc_info.mem.virtual_mem[i] << endl;
    */
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
            exit(0);

        else
            cout << "Comando não encontrado" << endl;
    }
}
