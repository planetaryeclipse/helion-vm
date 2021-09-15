#ifndef MEM_TYPES_HPP
#define MEM_TYPES_HPP

#include <cstdlib>
#include <memory>
#include <mutex>
#include <vector>

//currently supported memory types
enum e_mem_type {
    PRIM_CHAR,
    PRIM_UCHAR,
    PRIM_SHORT,
    PRIM_USHORT,
    PRIM_INT,
    PRIM_UINT,
    PRIM_LONG,
    PRIM_ULONG
};

struct mem_def {
    e_mem_type type;
    size_t byte_length;

    mem_def(e_mem_type type, size_t byte_length);
};

//essentially just encapsulates a memory definition
struct named_mem_def {
    std::string name;
    mem_def def;

    named_mem_def(std::string name, e_mem_type type, size_t byte_length);
};

//the base class provides all possible function implementations to simplify
//the work that the interpreter and the script linkers need to do

class mem_projectile {
    void* block_addr;
    size_t block_length;

   public:
    mem_projectile(size_t block_length);
    ~mem_projectile();

    size_t get_block_length();

    void* get_sub_block_addr(size_t index, size_t sub_length);

    void set_bytes(std::vector<uint8_t> bytes);
    void set_bytes(size_t index, std::vector<uint8_t> bytes);

    //these are to be overridden by the separate implementations to acquire
    //the necessary mutex controls and update information

    virtual void acquire_control();
    virtual void release_control();

    virtual void set_has_update(bool has_update);
    virtual bool get_has_update();
};

class mem_satellite : public mem_projectile {
    std::mutex protect_state;

   public:
    mem_satellite(size_t block_length);
    ~mem_satellite();

    //provides functionality for controlling the memory state
    //protection for this class and subclasses

    void acquire_control();
    void release_control();
};

class mem_interstellar : public mem_satellite {
    bool has_update = false;

   public:
    mem_interstellar(size_t block_length);
    ~mem_interstellar();

    //control methods are defined by superclass

    //provides functionality for controlling the update status
    //only found in the interstellar memory

    void set_has_update(bool has_update);
    bool get_has_update();
};

//recommended to use these methods to create the pointers at the time
//of allocating the memory for the objects as well as packaging it into
//the unified memory type of the base memory type

std::shared_ptr<mem_projectile> alloc_proj(size_t block_length);
std::shared_ptr<mem_projectile> alloc_sat(size_t block_length);
std::shared_ptr<mem_projectile> alloc_interst(size_t block_length);

#endif