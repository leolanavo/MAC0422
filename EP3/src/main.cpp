#include <fstream>
#include <iostream>
#include <string>

#include "shell.h"
#include "tests.h"

using namespace std;

int main (int argc, char** argv) {
    if (argc == 2 && argv[1][0] == 't') {
        tests();
    }
    prompt();
    return 0;
}
