#include "read.h"


using namespace std;

/* Receives a filename.
 *
 * Reads and process the file according to the
 * specification of the assignment.
 *
 * Returns nothing.
 */
assemb read_file(string name) {
    string line;
    ifstream file(name);
    double len;
    int i, pid_count;
    vector<int> access, time;
    vector<Process> plist;

    pid_count = 1;

    if (!file.is_open())
        print_failed("Open input file");

    getline(file, line);
    vector<string> fline = split_spaces(line);
    Memory mem(stoi(fline[0]), stoi(fline[1]),
               stoi(fline[2]), stoi(fline[3]));

    fline.clear();

    while (!file.eof()) {
        getline(file, line);

        fline = split_spaces(line);

        if (fline.size() == 2) {
           plist.push_back(Process (stoi(fline[0]), -1, -1, "COMPACTAR", access, time));
        }
        else {
            len = (fline.size() - 4)/2; // Get the size of the process arrays

            for (int j = 0; j < len; j++) {
                i = j*2 + 4;
                access.push_back(stoi(fline[i]));
                time.push_back(stoi(fline[i + 1]));
            }

            Process p (stoi(fline[0]), stoi(fline[1]), stoi(fline[2]), fline[3], access, time);
            p.pid = pid_count;
            pid_count++;

            plist.push_back(p);
        }

        access.clear();
        time.clear();
        fline.clear();
    }

    assemb rt;
    rt.mem = mem;
    rt.plist = plist;
    
    return rt;
}
