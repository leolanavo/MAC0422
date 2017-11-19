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

    simulate(a, 1, 2, 3);    
}

void test_best_fifo() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 1, 2, 5);
}

void test_best_second() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 1, 3, 5);
}

void test_best_fourth() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 1, 4, 5);
}

void test_best_optimal() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 1, 1, 5);
}

void test_worst_fifo() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 2, 2, 5);
}

void test_worst_second() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 2, 3, 5);
}

void test_worst_fourth() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 2, 4, 5);
}

void test_worst_optimal() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 2, 1, 5);
}

void test_quick_fifo() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 3, 2, 5);
}

void test_quick_second() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 3, 3, 5);
}

void test_quick_fourth() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 3, 4, 5);
}

void test_quick_optimal() {
    string file = "test.txt";    
    assemb a = read_file(file);
    simulate(a, 3, 1, 5);
}

void tests(int id) {
    switch (id) {
        case 0:
            test_best_fifo();
            break;
        case 1:
            test_best_second();
            break;
        case 2:
            test_best_fourth();
            break;
        case 3:
            test_best_optimal();
            break;
        case 4:
            test_worst_fifo();
            break;
        case 5:
            test_worst_second();
            break;
        case 6:
            test_worst_fourth();
            break;
        case 7:
            test_worst_optimal();
            break;
        case 8:
            test_quick_fifo();
            break;
        case 9:
            test_quick_second();
            break;
        case 10:
            test_quick_fourth();
            break;
        case 11:
            test_quick_optimal();
            break;
    }
    exit(0);
}
