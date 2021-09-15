#include "interpreter/instr_type.hpp"

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "interpreter/instr_except.hpp"
#include "interpreter/instr_func.hpp"

using namespace std;

instr::instr(e_instr_type instr_type, e_oper_type oper_type, function<void(vector<string>, memory_map*, size_t*, size_t)> func) {
    this->instr_type = instr_type;
    this->oper_type = oper_type;
    this->func = func;
}

std::function<void(vector<string>, memory_map*, size_t*, size_t)> instr::get_func() {
    return this->func;
}

map<string, instr> instrs{
    {"ALLOC", instr(INSTR_ALLOCATE, ARGS_2_OPERAND, func_instr_allocate)},
    {"RELEA", instr(INSTR_RELEASE, ARGS_1_OPERAND, func_instr_release)},

    {"ACQUI", instr(INSTR_ACQUIRE, ARGS_1_OPERAND, func_instr_acquire)},
    {"LIBER", instr(INSTR_LIBERATE, ARGS_1_OPERAND, func_instr_liberate)},

    {"PSHUP", instr(INSTR_PUSH_UPDATE, ARGS_1_OPERAND, func_instr_push_update)},

    {"JPFOR", instr(INSTR_JUMP_FORWARD, ARGS_1_OPERAND, func_instr_jump_forward)},
    {"JPBCK", instr(INSTR_JUMP_FORWARD, ARGS_1_OPERAND, func_instr_jump_forward)},

    {"MOV", instr(INSTR_MOVE, ARGS_3_OPERAND, func_instr_move)},
    {"MOVTA", instr(INSTR_MOVE_TO_ARRAY, ARGS_4_OPERAND, func_instr_move_to_array)},
    {"MOVFA", instr(INSTR_MOVE_FROM_ARRAY, ARGS_4_OPERAND, func_instr_move_from_array)},

    {"SET", instr(INSTR_SET, ARGS_3_OPERAND, func_instr_set)},
    {"SETSL", instr(INSTR_SET_SLICE, ARGS_4_OPERAND, func_instr_set_slice)},

    {"ADD", instr(INSTR_ADD, ARGS_2_OPERAND, func_instr_add)},
    {"SUB", instr(INSTR_SUBTRACT, ARGS_2_OPERAND, func_instr_sub)},

    {"MADD", instr(INSTR_MEMORY_ADD, ARGS_2_OPERAND, func_instr_madd)},
    {"MSUB", instr(INSTR_MEMORY_SUBTRACT, ARGS_2_OPERAND, func_instr_msub)}};

instr get_instr_from_id(string id) {
    if (instrs.find(id) == instrs.end())
        throw unrecognized_instr_exception(id);

    return instrs.at(id);
}