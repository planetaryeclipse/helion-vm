#ifndef INSTR_TYPE_HPP
#define INSTR_TYPE_HPP

#include <functional>
#include <string>
#include <vector>

#include "memory/mem_mapping.hpp"

enum e_instr_type {
    INSTR_ALLOCATE,
    INSTR_RELEASE,

    INSTR_ACQUIRE,
    INSTR_LIBERATE,

    INSTR_PUSH_UPDATE,
    // INSTR_SUSPEND,
    // INSTR_HALT,

    INSTR_JUMP_FORWARD,
    INSTR_JUMP_BACKWARD,

    INSTR_MOVE,
    INSTR_MOVE_TO_ARRAY,
    INSTR_MOVE_FROM_ARRAY,

    INSTR_SET,
    INSTR_SET_SLICE,

    INSTR_ADD,
    INSTR_SUBTRACT,

    INSTR_MEMORY_ADD,
    INSTR_MEMORY_SUBTRACT,
};

enum e_oper_type {
    ARGS_1_OPERAND,
    ARGS_2_OPERAND,
    ARGS_3_OPERAND,
    ARGS_4_OPERAND
};

class instr {
    e_instr_type instr_type;
    e_oper_type oper_type;
    std::function<void(std::vector<std::string>, memory_map*, size_t*, size_t)> func;

   public:
    instr(e_instr_type instr_type, e_oper_type oper_type, std::function<void(std::vector<std::string>, memory_map*, size_t*, size_t)> mem_func);
    std::function<void(std::vector<std::string>, memory_map*, size_t*, size_t)> get_func();
};

instr get_instr_from_id(std::string id);

#endif