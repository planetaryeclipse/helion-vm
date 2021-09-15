#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <list>
#include <map>
#include <utility>
#include <vector>

#include "interpreter/instr_runner.hpp"
#include "interpreter/script/linker.hpp"
#include "memory/mem_mapping.hpp"
#include "memory/mem_types.hpp"

#include"interpreter/script/invokable.hpp"

class script : public invokable {
    linker* lnk;
    instr_runner instr_rn;

   public:
    script(invoke_def def, linker* lnk, std::vector<text_instr> instrs);
    script(invoke_def def, linker* lnk, std::string file_path);

    memory_map* get_output_mem() override;

    void invoke() override;
    void finalize() override;
};

class script_block : public invokable {
    linker* lnk;
    std::list<std::shared_ptr<invokable>> invks;

   public:
    script_block(invoke_def def, linker* lnk, std::list<std::shared_ptr<invokable>> invks);

    memory_map* get_output_mem() override;

    void invoke() override;
    void finalize() override;
};

#endif