#include "string_split.h"

using namespace std;

/* Receives a string.
 *
 * Returns a string array where every position contains a word
 * from the original string separated by blank space.
 */
vector<string> split_spaces(string str) {
    istringstream iss(str);

    return {
        istream_iterator<string>{iss},
        istream_iterator<string>{}
    };
}
