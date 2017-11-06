#ifndef SHELL_H
#define SHELL_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/* Receives a string and a integer, which is the starting point
 * of a substring.
 *
 * Retruns the index of the begging of the next word in the
 * substring. Returns -1 if no such integer is found.
 */
int find_next_word(string str, int start);

/* Receives a string.
 *
 * Returns a string array where every position contains a word
 * from the original string separated by blank space.
 */
string* split_spaces(string str);

/* Receives nothing.
 *
 * Execute the prompt for executing the functions of the
 * assingment.
 *
 * Returns nothing.
 */
void prompt();

#endif
