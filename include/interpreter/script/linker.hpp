#ifndef LINKER_HPP
#define LINKER_HPP

#include "interpreter/script/invokable.hpp"

class invokable;  //forward definition as some subclasses of invokable require the linker

class linker {
    invokable* out_invk;

    void invoke();
};

#endif