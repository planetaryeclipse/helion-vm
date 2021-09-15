#include "interpreter/instr_func.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "interpreter/instr_except.hpp"
#include "memory/mem_types.hpp"
#include "util/env_util.hpp"
#include "util/mem_util.hpp"
#include "util/term_colors.hpp"
#include "util/value_util.hpp"

#define CHAR_BYTES 1
#define SHORT_BYTES 2
#define INT_BYTES 4
#define LONG_BYTES 8

using namespace std;

//NOTE: the use of these environment variables allows the user to configure program output

void func_instr_allocate(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 2);
    //ALLOC <mem-id>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr allocate" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(1) << endl;
    }

    m_map->create_mem(args.at(0), get_val(args.at(1)));
    ++(*p_instr);
}
void func_instr_release(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //RELEA <mem-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr release" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
    }

    m_map->remove_mem(args.at(0));
    ++(*p_instr);
}

void func_instr_acquire(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //ACQUI <mem-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr acquire" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
    }

    m_map->find_mem(args.at(0))->acquire_control();
    ++(*p_instr);
}
void func_instr_liberate(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //LIBER <mem-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr liberate" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
    }

    m_map->find_mem(args.at(0))->release_control();
    ++(*p_instr);
}

void func_instr_push_update(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //PSHUP <mem-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr push update" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
    }

    m_map->find_mem(args.at(0))->set_has_update(true);
    ++(*p_instr);
}

// void func_instr_suspend(vector<string> args, memory_map *m_map, size_t p_instr) {
// }
// void func_instr_halt(vector<string> args, memory_map *m_map, size_t p_instr) {
// }

void func_instr_jump_forward(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //JPFOR <instr-num>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr jump forward" << endl;
        cout << "\tInstruction number: " << foreground_reset << args.at(0) << endl;
    }

    size_t fwd_jump = get_val(args.at(0));
    if (fwd_jump + (*p_instr) >= num_instrs)
        throw instr_pointer_out_of_bounds_exception(fwd_jump);

    (*p_instr) += get_val(args.at(0));
}

void func_instr_jump_backward(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 1);
    //JPBCK <instr-num>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr jump backward" << endl;
        cout << "\tInstruction number: " << foreground_reset << args.at(0) << endl;
    }

    size_t bck_jump = get_val(args.at(0));
    if (bck_jump > (*p_instr))
        throw instr_pointer_out_of_bounds_exception(-bck_jump);  //requires either (-) or (+)

    (*p_instr) -= get_val(args.at(0));
}

void func_instr_move(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 3);
    //MOV <mem-id-src>,<mem-id-dest>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr move" << endl;
        cout << "\tMemory source ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory destination ID: " << foreground_reset << args.at(1) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(2) << endl;
    }

    size_t mem_len = get_val(args.at(2));
    void *src_addr = m_map->find_mem(args.at(0))->get_sub_block_addr(0, mem_len);
    void *dest_addr = m_map->find_mem(args.at(1))->get_sub_block_addr(0, mem_len);

    memcpy(dest_addr, src_addr, mem_len);

    ++(*p_instr);
}

void func_instr_move_to_array(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 4);
    //MOVTA <mem-id-src>,<mem-id-dest>,<mem-index>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr move to array" << endl;
        cout << "\tMemory source ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory destination ID: " << foreground_reset << args.at(1) << endl;
        cout << foreground_blue << "\tMemory index: " << foreground_reset << args.at(2) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(3) << endl;
    }

    size_t mem_index = get_val(args.at(2));
    size_t mem_len = get_val(args.at(3));
    void *src_addr = m_map->find_mem(args.at(0))->get_sub_block_addr(0, mem_len);
    void *dest_addr = m_map->find_mem(args.at(1))->get_sub_block_addr(mem_index, mem_len);

    memcpy(dest_addr, src_addr, mem_len);

    ++(*p_instr);
}

void func_instr_move_from_array(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 4);
    //MOVFA <mem-id-src>,<mem-index>,<mem-id-dest>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr move from array" << endl;
        cout << "\tMemory source ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory index: " << foreground_reset << args.at(1) << endl;
        cout << foreground_blue << "\tMemory destination ID: " << foreground_reset << args.at(2) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(3) << endl;
    }

    size_t mem_index = get_val(args.at(1));
    size_t mem_len = get_val(args.at(3));
    void *src_addr = m_map->find_mem(args.at(0))->get_sub_block_addr(mem_index, mem_len);
    void *dest_addr = m_map->find_mem(args.at(2))->get_sub_block_addr(0, mem_len);

    memcpy(dest_addr, src_addr, mem_len);

    ++(*p_instr);
}

void func_instr_set(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 3);
    //SET <mem-id>,<mem-val>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr set" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory value: " << foreground_reset << args.at(1) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(2) << endl;
    }

    size_t mem_len = get_val(args.at(2));
    void *mem_addr = m_map->find_mem(args.at(0))->get_sub_block_addr(0, mem_len);

    memset(mem_addr, get_val(args.at(1)), mem_len);

    ++(*p_instr);
}

void func_instr_set_slice(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 4);
    //SETSL <mem-id>,<mem-index>,<mem-val>,<mem-len>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr set slice" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tMemory index: " << foreground_reset << args.at(1) << endl;
        cout << foreground_blue << "\tMemory value: " << foreground_reset << args.at(2) << endl;
        cout << foreground_blue << "\tMemory length: " << foreground_reset << args.at(3) << endl;
    }

    size_t mem_len = get_val(args.at(3));
    void *mem_addr = m_map->find_mem(args.at(0))->get_sub_block_addr(get_val(args.at(1)), mem_len);

    memset(mem_addr, get_val(args.at(2)), mem_len);

    ++(*p_instr);
}

void func_instr_add(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 2);
    //ADD <mem-id>,<val>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr add" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tValue: " << foreground_reset << args.at(1) << endl;
    }

    uint64_t *mem_val = (uint64_t *)m_map->find_mem(args.at(0))->get_sub_block_addr(0, LONG_BYTES);

    uint64_t val = get_val(args.at(1));
    if (is_env_enabled(use_big_endian))
        *mem_val += get_inverted_byte_order(val);
    else
        *mem_val += val;

    ++(*p_instr);
}

void func_instr_sub(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 2);
    //SUB <mem-id>,<val>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr subtract" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tValue: " << foreground_reset << args.at(1) << endl;
    }

    uint64_t *mem_val = ((uint64_t *)m_map->find_mem(args.at(0))->get_sub_block_addr(0, LONG_BYTES));

    uint64_t val = get_val(args.at(1));
    if (is_env_enabled(use_big_endian))
        *mem_val -= get_inverted_byte_order(val);
    else
        *mem_val -= val;

    ++(*p_instr);
}

void func_instr_madd(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 2);
    //MADD <mem-id>,<mem-val-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr memory add" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tValue memory ID: " << foreground_reset << args.at(1) << endl;
    }

    *((uint64_t *)m_map->find_mem(args.at(0))->get_sub_block_addr(0, LONG_BYTES)) += *((uint64_t *)m_map->find_mem(args.at(1))->get_sub_block_addr(0, LONG_BYTES));
    ++(*p_instr);
}

void func_instr_msub(vector<string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs) {
    assert(args.size() == 2);
    //MSUB <mem-id>,<mem-val-id>

    if (is_env_enabled(debug_instr)) {
        cout << foreground_blue << "Running instr memory subtract" << endl;
        cout << "\tMemory ID: " << foreground_reset << args.at(0) << endl;
        cout << foreground_blue << "\tValue memory ID: " << foreground_reset << args.at(1) << endl;
    }

    *((uint64_t *)m_map->find_mem(args.at(0))->get_sub_block_addr(0, LONG_BYTES)) -= *((uint64_t *)m_map->find_mem(args.at(1))->get_sub_block_addr(0, LONG_BYTES));
    ++(*p_instr);
}
