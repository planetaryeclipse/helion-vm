#ifndef MEM_EXCEPT_HPP
#define MEM_EXCEPT_HPP

#include <cstdlib>
#include <string>

// TODO - these exceptions should likely be refactored at some stage

class invalid_mem_size_exception {
   public:
    const std::string what() const {
        return "Memory byte length of 0 is invalid";
    }
};

class invalid_mem_size_for_indexing_exception {
    size_t index, block_length;

   public:
    invalid_mem_size_for_indexing_exception(size_t index, size_t block_length) {
        this->index = index;
        this->block_length = block_length;
    }

    const std::string what() const {
        return "Desired memory block exceeds allocated memory block";
    }

    const size_t get_index() const {
        return this->index;
    }

    const size_t get_block_length() const {
        return this->block_length;
    }
};

class unallocated_mem_identifier_exception {
    std::string identifier;

   public:
    unallocated_mem_identifier_exception(std::string identifier) {
        this->identifier = identifier;
    }

    const std::string what() const {
        return "Memory with identifier is unallocated";
    }
};

class invalid_mem_identifier_exception {
    std::string identifier;

   public:
    invalid_mem_identifier_exception(std::string identifier) {
        this->identifier = identifier;
    }

    const std::string what() const {
        return "Memory identifier is invalid";
    }
};

class duplicate_mem_identifier_exception {
    std::string identifier;

   public:
    duplicate_mem_identifier_exception(std::string identifier) {
        this->identifier = identifier;
    }

    const std::string what() const {
        return "Memory with identifier is already allocated";
    }
};

#endif  // MEM_EXCEPT_HPP