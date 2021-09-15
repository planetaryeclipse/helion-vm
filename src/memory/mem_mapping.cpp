#include "memory/mem_mapping.hpp"

#include <cstdlib>
#include <iomanip>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "memory/mem_except.hpp"
#include "util/mem_util.hpp"

using namespace std;

inline void ensure_valid_identifier(string id) {
    if (!is_valid_mem_identifier(id))
        throw invalid_mem_identifier_exception(id);
}

inline void ensure_identifier_not_exists(string id, map<string, shared_ptr<mem_projectile>> id_map) {
    if (id_map.find(id) != id_map.end())
        throw duplicate_mem_identifier_exception(id);
}

inline void ensure_identifier_exists(string id, map<string, shared_ptr<mem_projectile>> id_map) {
    if (id_map.find(id) == id_map.end())
        throw unallocated_mem_identifier_exception(id);
}

shared_ptr<mem_projectile> memory_map::create_mem(string id, size_t block_length) {
    ensure_valid_identifier(id);
    ensure_identifier_not_exists(id, this->id_map);

    shared_ptr<mem_projectile> mem(new mem_projectile(block_length));
    this->id_map.insert(pair<string, shared_ptr<mem_projectile>>(id, mem));

    return mem;
}

shared_ptr<mem_projectile> memory_map::create_mem(string id, size_t block_length, vector<uint8_t> bytes) {
    ensure_valid_identifier(id);
    ensure_identifier_not_exists(id, this->id_map);

    shared_ptr<mem_projectile> mem(new mem_projectile(block_length));
    this->id_map.insert(pair<string, shared_ptr<mem_projectile>>(id, mem));

    mem->set_bytes(bytes);
    return mem;
}

shared_ptr<mem_projectile> memory_map::find_mem(string id) {
    ensure_valid_identifier(id);
    ensure_identifier_exists(id, this->id_map);

    return this->id_map.at(id);
}

bool memory_map::contains_mem(string id) {
    ensure_valid_identifier(id);

    return this->id_map.find(id) != this->id_map.end();
}

void memory_map::remove_mem(string id) {
    ensure_valid_identifier(id);
    ensure_identifier_exists(id, this->id_map);

    this->id_map.erase(id);
}

void memory_map::import_external_mem(string id, shared_ptr<mem_projectile> mem) {
    ensure_valid_identifier(id);
    ensure_identifier_not_exists(id, this->id_map);

    this->id_map.insert(pair<string, shared_ptr<mem_projectile>>(id, mem));
}

string memory_map::as_string() {
    stringstream rep_sstream;
    for (map<string, shared_ptr<mem_projectile>>::iterator iter = this->id_map.begin(); iter != this->id_map.end(); iter++) {
        size_t mem_length = iter->second->get_block_length();
        uint8_t* p_mem = (uint8_t*)iter->second->get_sub_block_addr(0, mem_length);

        rep_sstream << "ID: " << left << setw(20) << iter->first;
        rep_sstream << "Length: " << setw(10) << mem_length;

        rep_sstream << hex;
        for (int i = 0; i < mem_length; i++) {
            uint8_t val = *(p_mem + i);
            rep_sstream << "0x" << (uint16_t)val;  //ensures that the char value will not be interpreted as a character
            if (i != mem_length - 1)
                rep_sstream << ',';
        }
        rep_sstream << endl;
    }

    return rep_sstream.str();
}