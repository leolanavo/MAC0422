#include "string_split.h"

using namespace std;

/* Receives a string and a integer, which is the starting point
 * of a substring.
 *
 * Retruns the index of the begging of the next word in the
 * substring. Returns -1 if no such integer is found.
 */
int find_next_word(string str, int start) {
    for (uint i = start; i < str.length(); i++)
        if (!isspace(str[i]))
            return i;
    return -1;
}

/* Receives a string.
 *
 * Returns a string array where every position contains a word
 * from the original string separated by blank space.
 */
vector<string> split_spaces(string str) {
    vector<string> parsed_str;
    int j = 0;

    for (uint i = 0; i < str.length(); i++)
        if (isspace(str[i])) {
            parsed_str.push_back(str.substr(j, i));
            j = find_next_word(str, i);
            if (j == -1) break;
            i = j;
        }

    parsed_str.push_back(str.substr(j, str.length()));
    return parsed_str;
}
