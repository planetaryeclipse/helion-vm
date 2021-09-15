#ifndef SCRIPT_PARSER_HPP
#define SCRIPT_PARSER_HPP

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "interpreter/script/linker.hpp"
#include "interpreter/script/script.hpp"

std::map<std::string, std::pair<std::string, std::string>> parse_script_directory(std::string dir_path);
std::shared_ptr<script_block> parse_script_block(std::string file_path, std::map<std::string, std::pair<std::string, std::string>> script_files);
std::shared_ptr<script> parse_script(std::string file_path);

#endif