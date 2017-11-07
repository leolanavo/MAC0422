#include "read.h"

#define SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace std;

void read_file(string name) {
    string line;
    ifstream file(name);
    double len;
    int i;
    vector<int> access, time;

    if (!file.is_open())
        print_failed("Open input file");

    getline(file, line);
    string* fline = split_spaces(line);
    Memory mem(stoi(fline[0]), stoi(fline[1]),
               stoi(fline[2]), stoi(fline[3]));
    delete fline;

    while (!file.eof()) {
        getline(file, line);
        fline = split_spaces(line);

        len = ceil(((double)(SIZE(fline) - 4))/2); // Get the size of the process arrays
        access.resize(len);
        time.resize(len);
        i = 0;

        for (int j = 0; j < len; j++) {
            i = j*2 + 4;
            access[j] = stoi(fline[i]);
            time[j] = stoi(fline[i+1]);
        }

        Process p(stoi(fline[0]), stoi(fline[1]), stoi(fline[2]), fline[3],
                  access, time);
    }
}
