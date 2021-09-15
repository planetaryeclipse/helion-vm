#include "interpreter/script/script.hpp"

#include <list>
#include <map>
#include <string>
#include <vector>

#include "interpreter/instr_parser.hpp"
#include "interpreter/instr_runner.hpp"
#include "interpreter/script/invokable.hpp"

using namespace std;

//describes the implementation of a single script

script::script(invoke_def def, linker* lnk, vector<text_instr> instrs) : invokable(def), instr_rn(instrs) {
    this->lnk = lnk;
}

script::script(invoke_def def, linker* lnk, string file_path) : invokable(def), instr_rn(parse_instr_file(file_path)) {
    this->lnk = lnk;
}

memory_map* script::get_output_mem() {
    return this->instr_rn.get_mem();
}

void script::invoke() {
    //copies the initial memory to be acted upon by the script
    *this->instr_rn.get_mem() = this->init_m_map;
    this->instr_rn.invoke();
}

void script::finalize() {
    this->invoke();
}

//describes the implementation of the script block (allows for running of multiple scripts/script blocks)

script_block::script_block(invoke_def def, linker* lnk, list<shared_ptr<invokable>> invks) : invokable(def) {
    this->lnk = lnk;
    this->invks = invks;
}

memory_map* script_block::get_output_mem() {
    return this->invks.back()->get_output_mem();
}

void script_block::invoke() {
    //copies the initial memory to the first script
    *this->invks.front()->get_initial_mem() = this->init_m_map;
    for (shared_ptr<invokable> scrpt : this->invks)
        if (scrpt->check_is_ready())  //ensures that the invokable has the needed memory
            scrpt->invoke();
}

void script_block::finalize() {
    this->invoke();
}