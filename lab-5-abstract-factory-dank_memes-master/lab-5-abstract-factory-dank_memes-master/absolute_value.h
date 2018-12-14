#include "base.h"
#include <cmath>

using namespace std;

class Absolute : public Base{

    private:
        Base *value;
    
    public: 
        Absolute():value(NULL){};
        Absolute(Base *tree):value(tree){};

        double evaluate(){
            return abs(value->evaluate());
        }
    


};
