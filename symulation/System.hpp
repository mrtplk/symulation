#pragma once
#include <stdio.h>
#include "M_M_1.hpp"

class System {
public:
    M_M_1 m;
    double
    capacity_in,
    capacity_out;
    int
    buffer_size;
    char type;
};
