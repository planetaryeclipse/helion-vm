#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <list>
#include <string>
#include <vector>

bool is_char_in_list(char c, std::list<char> valid_chars);
std::vector<std::string> parse_delim_vals(std::string delim_str, char delim_c);

#endif