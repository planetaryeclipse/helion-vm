#ifndef INSTR_RUNNER_HPP
#define INSTR_RUNNER_HPP

#include <string>
#include <vector>

#include "memory/mem_mapping.hpp"

class text_instr {
    std::string id;
    std::vector<std::string> args;

   public:
    text_instr(std::string id, std::vector<std::string> args);
    void run_instr(memory_map* m_map, size_t* p_instr, size_t num_instrs);

    std::string get_id();
    std::vector<std::string> get_args();
};

class instr_runner {
    memory_map m_map;
    std::vector<text_instr> instrs;

    size_t p_instr = 0;

   public:
    instr_runner(std::vector<text_instr> instrs);
    void invoke();
    memory_map* get_mem();
    memory_map get_mem_clone();
};

#endif