#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Access {

    int pos;
    int pid;
};

/* Class: Process
 * --------------
 * Fields:
 *     t0     : arrival time of a process
 *     tf     : finish time of a process
 *     b      : quantity of memory used by process
 *     name   : name of the process
 *     access : positions where the process will be acessed
 *     time   : when which position will be acessed
 *     base   : where is the initial position of the process
 *              in the physical memory
 *     next   : the index of the next position to be accesed of
 *              the process
 */
class Process {
  public:
    int t0, tf, b, p_base, v_base, pid, next, naccess;
    string name;

    Process(int t0, int tf, int b, string name, int naccess);
    void set_base(int base);
    int get_base();
    int get_size();
    string get_name();
};

#endif
