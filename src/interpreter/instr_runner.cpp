#include "interpreter/instr_runner.hpp"

#include <cstdlib>
#include <string>
#include <vector>

#include "interpreter/instr_type.hpp"
#include "memory/mem_mapping.hpp"

using namespace std;

text_instr::text_instr(string id, vector<string> args) {
    this->id = id;
    this->args = args;
}

void text_instr::run_instr(memory_map* m_map, size_t* p_instr, size_t num_instrs) {
    get_instr_from_id(this->id).get_func()(this->args, m_map, p_instr, num_instrs);
}

string text_instr::get_id() {
    return this->id;
}

vector<string> text_instr::get_args() {
    return this->args;
}

instr_runner::instr_runner(vector<text_instr> instrs) {
    this->instrs = instrs;
}

void instr_runner::invoke() {
    while (this->p_instr != this->instrs.size())
        this->instrs.at(this->p_instr).run_instr(&this->m_map, &this->p_instr, this->instrs.size());
}

memory_map* instr_runner::get_mem() {
    return &this->m_map;
}

memory_map instr_runner::get_mem_clone() {
    return this->m_map;
}