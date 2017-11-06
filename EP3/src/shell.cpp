#include "shell.h"

#define NCMD 5
typedef unsigned int uint;

/* Receives a string and a integer, which is the starting point
 * of a substring.
 *
 * Retruns the index of the begging of the next word in the
 * substring. Returns -1 if no such integer is found.
 */
int find_next_word(string str, int start) {
    for (uint i = start; i < str.length(); i++)
        if (!isspace(str[i]))
            return i;
    return -1;
}

/* Receives a string.
 *
 * Returns a string array where every position contains a word
 * from the original string separated by blank space.
 */
string* split_spaces(string str) {
    int nspc = 1;

    for (uint i = 0; i < str.length(); i++)
        if (isspace(str[i])) nspc++;

    string* parsed_str = new string[nspc];

    int j = 0;
    nspc = 0;

    for (uint i = 0; i < str.length(); i++)
        if (isspace(str[i])) {
            parsed_str[nspc] = str.substr(j, i);
            j = find_next_word(str, i);
            if (j == -1) break;
            i = j;
            nspc++;
        }

    parsed_str[nspc] = str.substr(j, str.length());
    return parsed_str;
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
