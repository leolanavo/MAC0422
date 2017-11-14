#include "shell.h"

using namespace std;

void simulate (assemb proc_info, int id_fit, int id_page, int interval) {
    int time = 0;
    
    for (int i = 0; i < proc_info.plist.size; i++) {
        if (time >= proc_info.plist[i].t0) {
            
            vector<char> v;
            
            for (int k = 0; k <= i; k++) {
            }
        }

        switch (id_fit) {
            case 1:
                return proc_info.mem.best_fit(proc_info.plist[i]);
            case 2:
                return proc_info.mem.worst_fit(proc_info.plist[i]);
            case 3:
                return proc_info.mem.quick_fit(proc_info.plist[i]);
        }        
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
            exit(0);

        else
            cout << "Comando não encontrado" << endl;
    }
}
