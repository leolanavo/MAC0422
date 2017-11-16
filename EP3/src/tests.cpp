#include "tests.h"

using namespace std;

void print_check (string str) {
    cout << GREEN_BOLD << "[ OK ]  " << RESET << str << endl;
}

void print_failed (string str) {
    cout << RED_BOLD << "[ FAILED ]  " << RESET << str << endl;
    exit(1);
}

void test_split() {
    string cmd = "carrega arquivo";
    vector<string> cmd_parsed = split_spaces(cmd);

    if (cmd_parsed[0] == "carrega" && cmd_parsed[1] == "arquivo")
        print_check("split_spaces");
    else
        print_failed("split_spaces");
}

void check(bool val, string name) {
    if (val)
        print_check(name);
    else
        print_failed(name);
}


void test_read () {
    string file = "test.txt";
    read_file(file);
}

void test_best () {
    string file = "test.txt";
    assemb a = read_file(file);
    simulate(a, 1, 1, 3);    
}

void tests() {
    test_best();
    //test_split();
    exit(0);
}
