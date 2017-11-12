#include "process.h"

using namespace std;

/* Receives a initial time, a final time, a size, a name,
 * the positions where the process will be accesed and when
 * it will be accessed.
 *
 * Returns a Process object with all the fields with the same values
 * as the arguments.
 *
 * NOTE: the base field will be set according to the chosen algorithm.
 */
Process::Process (int t0, int tf, int b, string name, vector<int> access, vector<int> time) :
    t0(t0), tf(tf), b(b), name(name), next(0), access(access), time(time)
{
}

/* Receives and integer.
 *
 * Sets a new base for the process
 *
 * Returns nothing;
 */
void Process::set_base(int base) {
    this->base = base;
}

/* Receives nothing;
 *
 * Returns the current base of the process
 */
int Process::get_base() {
    return this->base;
}

/* Receives nothing;
 *
 * Returns the size of the process
 */
int Process::get_size() {
	return this->b;
}

/* Receives nothing;
 *
 * Returns the name of the process
 */
string Process::get_name() {
	return this->name;
}

/* Receives the current time of execution.
 *
 * Moves the next index to the first postion that wasn't
 * accessed until the current time of execution.
 *
 * Returns nothing.
 */
void Process::access_process(int current_time) {
    for (int i = this->next; i < access.size(); i++) {
        if (this->time[i] <= current_time) {
            this->next++;
        }
    }
}
