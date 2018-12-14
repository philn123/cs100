#pragma once
#include "BaseFactory.h"
#include <iostream>
#include "scientific_print.h"
using namespace std;

class ScientificFactory : public BaseFactory{
    private:
        double value;
        
    public:
        ScientificFactory() : value(0.0){};
        ScientificFactory(double val) : value(val){};

        BasePrint* generatePrint(double value){
            ScientificPrint *s = new ScientificPrint(value);
            return s;
        }
};
