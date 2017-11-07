#include "tests.h"

using namespace std;

void print_check (string str) {
    cout << GREEN_BOLD << "[ OK ]  " << RESET << str << endl;
}

void print_failed (string str) {
    cout << RED_BOLD << "[ FAILED ]  " << RESET << str << endl;
    exit(1);
}

void tests() {
    string cmd = "carrega arquivo";
    vector<string> cmd_parsed = split_spaces(cmd);

    if (cmd_parsed[0] == "carrega" && cmd_parsed[1] == "arquivo")
        print_check("split_spaces");
    else
        print_failed("split_spaces");
}
