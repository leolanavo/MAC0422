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
Process::Process (int t0, int tf, int b, string name, int naccess) :
    t0(t0), tf(tf), b(b), name(name), v_base(-1), next(0), naccess(naccess)
{
}

/* Receives and integer.
 *
 * Sets a new base for the process
 *
 * Returns nothing;
 */
void Process::set_base(int base) {
    this->v_base = base;
}

/* Receives nothing;
 *
 * Returns the current base of the process
 */
int Process::get_base() {
    return this->v_base;
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