#include <iostream>
#include <random>
#include <vector>
#pragma once

class NumericalAttributes{
   
    public:
   
    NumericalAttributes(int passedCount, int passedFrom);
    ~NumericalAttributes();
    
    void calculateNumericalAttributes();

    private:
    int count;
    int from;
};
