#ifndef MEM_MAPPING_HPP
#define MEM_MAPPING_HPP

#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "memory/mem_types.hpp"

class memory_map {
    std::map<std::string, std::shared_ptr<mem_projectile>> id_map;

   public:
    //always creates projectile memory objects
    std::shared_ptr<mem_projectile> create_mem(std::string id, size_t block_length);
    std::shared_ptr<mem_projectile> create_mem(std::string id, size_t block_length, std::vector<uint8_t> bytes);

    std::shared_ptr<mem_projectile> find_mem(std::string id);
    bool contains_mem(std::string id);

    void remove_mem(std::string id);

    //can import projectile, satellite, or interstellar memory objects
    void import_external_mem(std::string id, std::shared_ptr<mem_projectile> mem);

    std::string as_string();
};

#endif