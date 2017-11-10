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

void test_linkedlist () {
    LinkedList<int> l;
    bool val;
    bool emp = l.isEmpty();

    l.add(1); l.add(2); l.add(3);

    bool ful = l.isEmpty();

    check(l.head->get_data() == 1 &&
          l.head->next->get_data() == 2 &&
          l.head->next->next->get_data() == 3, "LinkedList Add");

    l.remove(0);

    check(l.head->get_data() == 2 &&
        l.head->next->get_data() == 3, "LinkedList Remove");

    check(!ful && emp, "LinkedList isEmpty");
    l.print_list();
}

void tests() {
    test_split();
    test_linkedlist();
    exit(0);
}
