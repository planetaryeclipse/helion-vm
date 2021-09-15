#ifndef VALUE_UTIL_HPP
#define VALUE_UTIL_HPP

#include <cstdlib>
#include <string>

enum e_val_type {
    VAL_HEXADECIMAL,
    VAL_OCTAL,
    VAL_DECIMAL
};

bool is_hex_val(std::string val);
bool is_oct_val(std::string val);
bool is_dec_val(std::string val);

bool is_valid_val(std::string val);
bool is_valid_val(std::string val, e_val_type* type);

size_t get_val(std::string val);

#endif