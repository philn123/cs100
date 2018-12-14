#include "basePrint.h"
#include <iostream>
#include <ios>
using namespace std;
class HexPrint : public BasePrint{
    private:
        double value;            


    public:
            HexPrint(){}
            HexPrint(double val): value(val){}

            void print(){
                cout << hexfloat << value << defaultfloat;
            }

};
