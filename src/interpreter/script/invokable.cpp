#include "interpreter/script/invokable.hpp"

#include <list>

using namespace std;

//allows for general details surrounding the definition of the invokable object

invoke_def::invoke_def(list<named_mem_def> inputs, list<named_mem_def> ext_mem, map<string, list<named_mem_def>> out_paths) {
    this->inputs = inputs;
    this->ext_mem = ext_mem;
    this->out_paths = out_paths;
}

invokable::invokable(invoke_def def) {
    //this constructor only populates the invoke_def member
    this->def = def;
}

bool invokable::check_is_ready() {
    for (named_mem_def mem_def : this->def.inputs) {
        //ensures the current memory is present in the initial memory map in
        //accordance with the definition for the invokable object
        if (this->init_m_map.contains_mem(mem_def.name) &&
            this->init_m_map.find_mem(mem_def.name)->get_block_length() != mem_def.def.byte_length)
            return false;
    }

    return true;
}

invoke_def invokable::get_def() {
    return this->def;
}

memory_map* invokable::get_initial_mem() {
    return &this->init_m_map;
}