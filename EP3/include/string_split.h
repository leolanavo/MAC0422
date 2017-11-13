#ifndef STRING_SPLIT_H
#define STRING_SPLIT_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;


/* Receives a string.
 *
 * Returns a string array where every position contains a word
 * from the original string separated by blank space.
 */
vector<string> split_spaces(string str);

#endif
