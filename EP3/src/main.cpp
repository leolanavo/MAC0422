#include <fstream>
#include <iostream>
#include <string>

#include "shell.h"
#include "tests.h"

using namespace std;

int main (int argc, char** argv) {
    if (argc == 3 && argv[1][0] == 't') {
        tests(stoi(argv[2]));
    }
    prompt();
    return 0;
}
