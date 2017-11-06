#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>

using namespace std;

/*
 * t0     : arrival time of a process
 * tf     : finish time of a process
 * b      : quantity of memory used by process
 * name   : name of the process
 * access : positions where the process will be acessed
 * time   : when which position will be acessed
 * base   : where is the initial position of the process
 *          in the physical memory
 * next   : the index of the next position to be accesed of
 *          the process
 */
class Process {
    int t0, tf, b, base, next;
    string name;
    int *access, *time;
  public:
    Process(int t0, int tf, int b, string name, int* access, int* time);
    void set_base(int base);
    int get_base();
    void access_process(int current_time);
    ~Process();
};

#endif
