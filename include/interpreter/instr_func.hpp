#ifndef INSTR_FUNC_HPP
#define INSTR_FUNC_HPP

#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

#include "memory/mem_mapping.hpp"

void func_instr_allocate(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_release(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

void func_instr_acquire(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_liberate(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

void func_instr_push_update(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
// void func_instr_suspend(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
// void func_instr_halt(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

void func_instr_jump_forward(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_jump_backward(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

void func_instr_move(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_move_to_array(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_move_from_array(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

void func_instr_set(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_set_slice(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

//considers the second operand as an explicit value
void func_instr_add(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_sub(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);

//considers the second operand as a memory address
void func_instr_madd(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
void func_instr_msub(std::vector<std::string> args, memory_map *m_map, size_t *p_instr, size_t num_instrs);
#endif