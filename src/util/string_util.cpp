#include "util/string_util.hpp"

#include <cstdlib>
#include <list>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using namespace std;

bool is_char_in_list(char c, list<char> valid_chars) {
    for (char valid_c : valid_chars)
        if (c == valid_c)
            return true;

    return false;
}

vector<string> parse_delim_vals(string delim_str, char delim_c) {
    if (delim_str.length() == 0)
        throw invalid_argument("Delimited string cannot have length 0");

    vector<string> vals;

    size_t val_begin = 0;
    while (true) {
        size_t val_end = delim_str.find(delim_c, val_begin);
        string val = delim_str.substr(val_begin, val_end - val_begin);

        if (val.length() == 0)
            throw invalid_argument("Value cannot be of length 0");

        vals.push_back(val);

        if (val_end == string::npos)
            break;

        val_begin = val_end + 1;
    }

    return vals;
}