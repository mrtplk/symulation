#pragma once
#include <cmath>
#include <iostream>

using namespace std;

class calculator {
    
public:
    //constructor
    calculator(double lambda, double mean);
    //destructor
    ~calculator();
    double
    ro,
    Lq,
    Wq;
};
