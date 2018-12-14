#pragma once
#include "BaseFactory.h"
#include "double_print.h"

class DoubleFactory : public BaseFactory{
    private:
        double value;
    public:
        DoubleFactory():value(0.0){};
        DoubleFactory(double val):value(val){};

        BasePrint* generatePrint(double value){
            DoublePrint *d = new DoublePrint(value);
            return d;
        }
};
