#ifndef INVOKABLE_HPP
#define INVOKABLE_HPP

#include <list>
#include <map>
#include <string>

#include "memory/mem_mapping.hpp"

struct invoke_def {
    std::list<named_mem_def> inputs;   //the defined inputs
    std::list<named_mem_def> ext_mem;  //external memory (connected by linker)

    std::map<std::string, std::list<named_mem_def>> out_paths;  //the output paths and associated memory

    invoke_def() = default;  //default constructor (no values are provided)
    invoke_def(std::list<named_mem_def> inputs, std::list<named_mem_def> ext_mem, std::map<std::string, std::list<named_mem_def>> out_paths);
};

//allows an abstract executable interface
class invokable {
   protected:
    //allows the ready check without having all the subsequent scripts (in the case of
    //a script block intialized)
    memory_map init_m_map;

    invoke_def def;

   public:
    invokable(invoke_def def);

    invoke_def get_def();

    memory_map* get_initial_mem();
    bool check_is_ready();

    virtual memory_map* get_output_mem() = 0;

    virtual void invoke() = 0;
    virtual void finalize() = 0;
};

#endif