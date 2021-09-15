#ifndef INSTR_EXCEPT_HPP
#define INSTR_EXCEPT_HPP

#include <cstdlib>
#include <string>

#include "instr_type.hpp"

class unrecognized_instr_exception {
    std::string instr_name;

   public:
    unrecognized_instr_exception(std::string instr_name) {
        this->instr_name = instr_name;
    }

    const std::string what() const {
        return "Instruction is not recognized";
    }

    const std::string get_instr_name() const {
        return this->instr_name;
    }
};

class invalid_number_of_instr_args_exception {
    e_instr_type instr_type;
    e_oper_type oper_type;

    size_t num_args_provided;

   public:
    invalid_number_of_instr_args_exception(e_instr_type instr_type, e_oper_type oper_type, size_t num_args_provided) {
        this->instr_type = instr_type;
        this->oper_type = oper_type;

        this->num_args_provided = num_args_provided;
    }

    const std::string what() const {
        return "Invalid number of arguments for instruction type";
    }

    const e_instr_type get_instr_type() const {
        return this->instr_type;
    }

    const e_oper_type get_oper_type() const {
        return this->oper_type;
    }

    const size_t get_num_args_provided() const {
        return this->num_args_provided;
    }
};

class invalid_instruction_file_line_exception {
    std::string line;

   public:
    invalid_instruction_file_line_exception(std::string line) {
        this->line = line;
    }

    const std::string what() const {
        return "Line is file is invalid instruction";
    }

    const std::string get_line() const {
        return this->line;
    }
};

class instr_pointer_out_of_bounds_exception {
    size_t p_instr_jump;

   public:
    instr_pointer_out_of_bounds_exception(size_t p_instr_jump) {
        this->p_instr_jump = p_instr_jump;
    }

    const std::string what() const {
        return "Intended instruction pointer value is out of allowable range of instructions";
    }

    const size_t get_p_instr_jump() const {
        return this->p_instr_jump;
    }
};

#endif