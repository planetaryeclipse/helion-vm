#include "util/value_util.hpp"

#include <cstdlib>
#include <list>
#include <stdexcept>
#include <string>

#include "util/string_util.hpp"

using namespace std;

bool is_hex_val(string val) {
    if (val.length() < 3 || val.substr(0, 2) != "0x")
        return false;

    const list<char> valid_hex_chars = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'};

    //ensures the rest of the characters are valid hex chars
    for (char c : val.substr(2, val.length() - 2))
        if (!is_char_in_list(c, valid_hex_chars))
            return false;

    return true;
}

bool is_oct_val(string val) {
    if (val.length() < 3 || val.substr(0, 2) != "0o")
        return false;

    const list<char> valid_oct_chars = {
        '0', '1', '2', '3',
        '4', '5', '6', '7'};

    //ensures the rest of the characters are valid oct chars
    for (char c : val.substr(2, val.length() - 2))
        if (!is_char_in_list(c, valid_oct_chars))
            return false;

    return true;
}

bool is_dec_val(string val) {
    if (val.length() < 3 || val.substr(0, 2) != "0d")
        return false;

    const list<char> valid_dec_chars = {
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9'};

    //ensures the rest of the characters are valid dec chars
    for (char c : val.substr(2, val.length() - 2))
        if (!is_char_in_list(c, valid_dec_chars))
            return false;

    return true;
}

bool is_valid_val(string val) {
    return is_hex_val(val) || is_oct_val(val) || is_dec_val(val);
}

bool is_valid_val(string val, e_val_type* type) {
    if (is_hex_val(val)) {
        *type = VAL_HEXADECIMAL;
        return true;
    } else if (is_oct_val(val)) {
        *type = VAL_OCTAL;
        return true;
    } else if (is_dec_val(val)) {
        *type = VAL_DECIMAL;
        return true;
    }

    return false;
}

size_t get_val(string val) {
    e_val_type type;
    if (!is_valid_val(val, &type))
        throw invalid_argument("Argument provided is not a valid value: " + val);

    if (type == VAL_HEXADECIMAL)
        return stoul(val.substr(2, val.length() - 2), 0, 16);
    else if (type == VAL_OCTAL)
        return stoul(val.substr(2, val.length() - 2), 0, 8);
    else  //type == VAL_DECIMAL
        return stoul(val.substr(2, val.length() - 2), 0, 10);
}