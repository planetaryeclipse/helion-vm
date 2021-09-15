#include "memory/mem_types.hpp"

#include <cstring>
#include <iostream>
#include <memory>
#include <syncstream>
#include <vector>

#include "memory/mem_except.hpp"

using namespace std;

mem_def::mem_def(e_mem_type type, size_t byte_length) {
    this->type = type;
    this->byte_length = byte_length;
}

named_mem_def::named_mem_def(string name, e_mem_type type, size_t byte_length) : def(type, byte_length) {
    this->name = name;
}

mem_projectile::mem_projectile(size_t block_length) {
    // osyncstream osync(cout);
    // cout << "Allocating projectile memory" << endl;

    if (block_length == 0)
        throw invalid_mem_size_exception();

    this->block_addr = malloc(block_length);
    this->block_length = block_length;
}

mem_projectile::~mem_projectile() {
    // osyncstream osync(cout);
    // cout << "Freeing projectile memory" << endl;

    free(this->block_addr);
}

size_t mem_projectile::get_block_length() {
    return this->block_length;
}

void* mem_projectile::get_sub_block_addr(size_t index, size_t sub_length) {
    // osyncstream osync(cout);
    // cout << "Returning sub block of projectile memory:";
    // cout << "\n\tIndex: " << to_string(index);
    // cout << "\n\tSub block length: " << to_string(sub_length) << endl;

    if (sub_length == 0)
        throw invalid_mem_size_exception();
    else if (index + sub_length > this->block_length)
        throw invalid_mem_size_for_indexing_exception(index, block_length);

    //explicitly considers a single byte as 8-bits
    return (void*)(((uint8_t*)this->block_addr) + index);
}

void mem_projectile::set_bytes(vector<uint8_t> bytes) {
    // osyncstream osync(cout);
    // cout << "Setting block of projectile memory:";
    // cout << "\n\tStarting at beginning of block";
    // cout << "\n\tByte length: " << to_string(bytes.size()) << endl;

    void* mem_addr = this->get_sub_block_addr(0, bytes.size());
    memcpy(mem_addr, bytes.data(), bytes.size());
}

void mem_projectile::set_bytes(size_t index, vector<uint8_t> bytes) {
    // osyncstream osync(cout);
    // cout << "Setting block of projectile memory:";
    // cout << "\n\tStarting at index: " << to_string(index);
    // cout << "\n\tByte length: " << to_string(bytes.size()) << endl;

    void* mem_addr = this->get_sub_block_addr(index, bytes.size());
    memcpy(mem_addr, bytes.data(), bytes.size());
}

void mem_projectile::acquire_control() {
    // osyncstream osync(cout);
    // cout << "Warning: attempting to obtain control over non-protectable memory!";
    // cout << "\n\tNon-fatal -> review bytecode script validity" << endl;
}

void mem_projectile::release_control() {
    // osyncstream osync(cout);
    // cout << "Warning: attempting to release control over non-protectable memory!";
    // cout << "\n\tNon-fatal -> review bytecode script validity" << endl;
}

void mem_projectile::set_has_update(bool has_update) {
    // osyncstream osync(cout);
    // cout << "Warning: attempting to change update status of non-update flagging memory!";
    // cout << "\n\tNon-fatal -> review bytecode script validity" << endl;
}

bool mem_projectile::get_has_update() {
    // osyncstream osync(cout);
    // cout << "Warning: attempting to get update status of non-update flagging memory!";
    // cout << "\n\tNon-fatal -> review bytecode script validity" << endl;

    return false;
}

mem_satellite::mem_satellite(size_t block_length) : mem_projectile(block_length) {
    // osyncstream osync(cout);
    // cout << "Allocating satellite memory" << endl;
}

mem_satellite::~mem_satellite() {
    // osyncstream osync(cout);
    // cout << "Freeing satellite memory" << endl;
}

void mem_satellite::acquire_control() {
    // osyncstream osync(cout);
    // cout << "Obtaining control of satellite memory state protection" << endl;

    this->protect_state.lock();
}

void mem_satellite::release_control() {
    // osyncstream osync(cout);
    // cout << "Releasing control of satellite memory state protection" << endl;

    this->protect_state.lock();
}

mem_interstellar::mem_interstellar(size_t block_length) : mem_satellite(block_length) {
    // osyncstream osync(cout);
    // cout << "Allocating interstellar memory" << endl;
}

mem_interstellar::~mem_interstellar() {
    // osyncstream osync(cout);
    // cout << "Freeing interstellar memory" << endl;
}

void mem_interstellar::set_has_update(bool has_update) {
    // osyncstream osync(cout);
    // cout << "Setting update status of interstellar memory";
    // cout << "\n\tUpdate status: " << (has_update ? "true" : "false") << endl;

    this->has_update = has_update;
}

bool mem_interstellar::get_has_update() {
    // osyncstream osync(cout);
    // cout << "Getting update status of interstellar memory" << endl;

    return this->has_update;
}

//these methods provide an encapsulated and wasy way of creating the
//various memory types and packaging it into a shared pointer of the
//base class for simplicity of memory management

shared_ptr<mem_projectile> alloc_proj(size_t block_length) {
    return shared_ptr<mem_projectile>(new mem_projectile(block_length));
}

shared_ptr<mem_projectile> alloc_sat(size_t block_length) {
    return shared_ptr<mem_projectile>(new mem_satellite(block_length));
}

shared_ptr<mem_projectile> alloc_interst(size_t block_length) {
    return shared_ptr<mem_projectile>(new mem_interstellar(block_length));
}