#pragma once
#include "basePrint.h"
#include <iostream>
#include <bitset>

using namespace std;
class BinaryPrint : public BasePrint{
    private:
        double value;
    
    public:
        BinaryPrint():value(0.0){}
        BinaryPrint(double val): value(val){}

        void print(){
            //using sizeof to keep amount of digits printed smaller
            bitset<sizeof(value)> bset1(value);
            cout << bset1;
        
        }

};
