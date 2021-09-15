#ifndef SCRIPT_PARSER_HPP
#define SCRIPT_PARSER_HPP

#include <string>
#include <vector>

#include "interpreter/instr_runner.hpp"

text_instr parse_instr_line(std::string line);

std::vector<text_instr> parse_instr_file(std::string file_path);
std::vector<text_instr> parse_instr_file(std::vector<std::string> lines);

#endif