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
    int pid_count;
    vector<list<Access>> access_list (2, list<Access>(0));
    vector<Process> plist;
    list<best_size> opt_size;

    pid_count = 1;

    getline(file, line);
    vector<string> fline = split_spaces(line);
    Memory mem(stoi(fline[0]), stoi(fline[1]),
               stoi(fline[2]), stoi(fline[3]));

    fline.clear();


    while (!file.eof()) {
        getline(file, line);
        fline = split_spaces(line);

        auto it = opt_size.begin();
        for (; it != opt_size.end() && fline.size() != 2; it++) {
            if (it->size == stoi(fline[2])) {
                it->freq++;
                break;
            }
        }

        if (it == opt_size.end()) {
            opt_size.push_back({1 , stoi(fline[2])});
        }

        if (fline.size() == 2) {
           plist.push_back(Process (stoi(fline[0]), -1, -1, "COMPACTAR", 0));
        }
        else {
            len = (fline.size() - 4)/2; // Get the size of the process arrays

            for (int j = 0; j < len; j++) {
                int i = j*2 + 4;
                int time = stoi(fline[i + 1]);
                if (time >= access_list.size())
                    access_list.resize(time + 1);

                access_list[time].push_back({stoi(fline[i]), pid_count});                
            }

            Process p (stoi(fline[0]), stoi(fline[1]), stoi(fline[2]), fline[3], len);
            p.pid = pid_count;
            pid_count++;

            plist.push_back(p);
        }

        fline.clear();
    }

    mem.generate_lists(opt_size);

    return {mem, plist, access_list};
}
