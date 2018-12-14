#pragma once
#include "BaseFactory.h"
#include "binary_print.h"
using namespace std;

class BinaryFactory : public BaseFactory{

    private:
        double value;

    public:
        BinaryFactory():value(0.0){};
        BinaryFactory(double val):value(val){};

        BasePrint* generatePrint(double value){
            BinaryPrint *b = new BinaryPrint(value);
            return b;
        }

};
