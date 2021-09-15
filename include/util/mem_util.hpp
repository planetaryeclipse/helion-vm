#ifndef MEM_UTIL_HPP
#define MEM_UTIL_HPP

#include <cstdlib>
#include <string>

#include "util/mem_util.hpp"

uint8_t get_inverted_bit_order(uint8_t val);

uint16_t get_inverted_byte_order(uint16_t val);
uint32_t get_inverted_byte_order(uint32_t val);
uint64_t get_inverted_byte_order(uint64_t val);

bool is_valid_mem_identifier(std::string identifier);

#endif  // MEM_UTIL_HPP