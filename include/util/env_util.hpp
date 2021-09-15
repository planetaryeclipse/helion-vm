#ifndef ENV_UTIL_HPP
#define ENV_UTIL_HPP

#include<string>

const std::string debug_instr_warnings = "DEBUG_HELION_INSTR_WARN";
const std::string debug_instr = "DEBUG_HELION_INSTR";
const std::string debug_instr_program = "DEBUG_HELION_INSTR_PROG";
const std::string use_big_endian = "HELION_USE_BIG_ENDIAN";

bool is_env_enabled(std::string env_var);

#endif