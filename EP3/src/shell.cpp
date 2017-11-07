#include "shell.h"

using namespace std;

#define NCMD 5
typedef unsigned int uint;

void simulate(vector<Process> plist, int id_fit, int id_page, int interval) {
    cout << "SIMULATE" << endl;
}

/* Receives nothing.
 *
 * Execute the prompt for executing the functions of the
 * assingment.
 *
 * Returns nothing.
 */
void prompt() {
    string cmd_line;
    ofstream in_file, out_file;
    vector<string> cmd;
    vector<Process> plist;
    int id_fit, id_page, interval;

    string cmds[NCMD] = { "carrega", "espaco", "substitui", "executa", "sai" };

    while (true) {
        cout << "[ep3]: ";
        getline(cin, cmd_line);
        cmd = split_spaces(cmd_line);

        if (cmd[0] == cmds[0])
            plist = read_file(cmd[1]);

        else if (cmd[0] == cmds[1])
            id_fit = stoi(cmd[1]);

        else if (cmd[0] == cmds[2])
            id_page = stoi(cmd[1]);

        else if (cmd[0] == cmds[3]) {
            interval = stoi(cmd[1]);
            simulate(plist, id_fit, id_page, interval);
        }

        else if (cmd[0] == cmds[4])
            exit(0);

        else
            cout << "Comando não encontrado" << endl;

        cmd.clear();
    }
}
