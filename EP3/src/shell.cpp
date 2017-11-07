#include "shell.h"

using namespace std;

#define NCMD 5
typedef unsigned int uint;

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
    int free_sp, page_sub, time;

    string cmds[NCMD] = { "carrega", "espaco", "substitui", "executa", "sai" };

    while (true) {
        cout << "[ep3]: ";
        getline(cin, cmd_line);
        string* cmd = split_spaces(cmd_line);

        if (cmd[0] == cmds[0])
            in_file.open(cmd[1]);

        else if (cmd[0] == cmds[1])
            free_sp = stoi(cmd[1]);

        else if (cmd[0] == cmds[2])
            page_sub = stoi(cmd[1]);

        else if (cmd[0] == cmds[3])
            time = stoi(cmd[1]);

        else if (cmd[0] == cmds[4])
            exit(0);

        else
            cout << "Comando não encontrado" << endl;
    }
}
