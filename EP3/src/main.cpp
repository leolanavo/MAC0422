#include <fstream>
#include <iostream>
#include <string>

#include "colors.h"
#include "shell.h"
#include "process.h"
#include "string_split.h"
#include "memory.h"
#include "read.h"
#include "tests.h"

using namespace std;

int main (int argc, char** argv) {
    if (argc == 2 && argv[1][0] == 't') {
        tests();
    }
    prompt();
    return 0;
}
