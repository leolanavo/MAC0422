#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
  private:
    int t0, tf, b, base, next;
    string name;
    vector <int> access, time;
  public:
    Process(int t0, int tf, int b, string name, vector<int> access, vector<int> time);
    void set_base(int base);
    int get_base();
    void access_process(int current_time);
};

#endif
