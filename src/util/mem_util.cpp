#include "util/mem_util.hpp"

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

#include "memory/mem_types.hpp"
#include "util/string_util.hpp"

using namespace std;

uint8_t get_inverted_bit_order(uint8_t val) {
    //gets the bits and shifts them to desired position
    uint8_t bits[] = {
        (uint8_t)((val & 0x01) << 7),  // 0b00000001 -> 0b10000000
        (uint8_t)((val & 0x02) << 5),  // 0b00000010 -> 0b01000000
        (uint8_t)((val & 0x04) << 3),  // 0b00000100 -> 0b00100000
        (uint8_t)((val & 0x08) << 1),  // 0b00001000 -> 0b00010000
        (uint8_t)((val & 0x10) >> 1),  // 0b00010000 -> 0b00001000
        (uint8_t)((val & 0x20) >> 3),  // 0b00100000 -> 0b00000100
        (uint8_t)((val & 0x40) >> 5),  // 0b01000000 -> 0b00000010
        (uint8_t)((val & 0x80) >> 7),  // 0b10000000 -> 0b00000001
    };

    //combines all their bits
    return bits[0] | bits[1] | bits[2] | bits[3] |
           bits[4] | bits[5] | bits[6] | bits[7];
}

uint16_t get_inverted_byte_order(uint16_t val) {
    //shifts the bytes around
    uint16_t bytes[] = {
        (uint16_t)((val & 0x00FF) << 8),  // 0x00FF -> 0xFF00
        (uint16_t)((val & 0xFF00) >> 8),  // 0xFF00 -> 0x00FF
    };

    //converts the shifted bytes
    return bytes[0] | bytes[1];
}

uint32_t get_inverted_byte_order(uint32_t val) {
    uint32_t bytes[] = {
        (val & 0xFF000000) >> 24,  //0xFF000000 -> 0x000000FF
        (val & 0x00FF0000) >> 8,   //0x00FF0000 -> 0x0000FF00
        (val & 0x0000FF00) << 8,   //0x0000FF00 -> 0x00FF0000
        (val & 0x000000FF) << 24,  //0x000000FF -> 0xFF000000
    };

    return bytes[0] | bytes[1] | bytes[2] | bytes[3];
}

uint64_t get_inverted_byte_order(uint64_t val) {
    uint64_t bytes[] = {
        (val & 0xFF00000000000000) >> 56,  // 0xFF00000000000000 -> 0x00000000000000FF
        (val & 0x00FF000000000000) >> 40,  // 0x00FF000000000000 -> 0x000000000000FF00
        (val & 0x0000FF0000000000) >> 24,  // 0x0000FF0000000000 -> 0x0000000000FF0000
        (val & 0x000000FF00000000) >> 8,   // 0x000000FF00000000 -> 0x00000000FF000000

        (val & 0x00000000FF000000) << 8,   // 0x00000000FF000000 -> 0x000000FF00000000
        (val & 0x0000000000FF0000) << 24,  // 0x0000000000FF0000 -> 0x0000FF0000000000
        (val & 0x000000000000FF00) << 40,  // 0x000000000000FF00 -> 0x00FF000000000000
        (val & 0x00000000000000FF) << 56,  // 0x00000000000000FF -> 0xFF00000000000000
    };

    return bytes[0] | bytes[1] | bytes[2] | bytes[3] |
           bytes[4] | bytes[5] | bytes[6] | bytes[7];
}

bool is_valid_mem_identifier(string identifier) {
    const list<char> valid_nums = {
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9'};

    const list<char> valid_chs_symbs = {
        'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'Y',
        'Z', '_'};

    if (identifier.length() == 0)
        return false;

    if (is_char_in_list(identifier.at(0), valid_nums))
        return false;  //first char of identifier must be capital letters or allowed symbols

    //ensures the rest of the characters are either numerical, capital letters, or allowed symbols
    for (char identifier_c : identifier.substr(1, identifier.length() - 1)) {
        if (!is_char_in_list(identifier_c, valid_nums) && !is_char_in_list(identifier_c, valid_chs_symbs))
            return false;
    }

    return true;
}