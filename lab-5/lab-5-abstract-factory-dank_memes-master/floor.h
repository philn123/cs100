#include "base.h"
#include <cmath>

using namespace std;

class Floor : public Base{

    private:
        Base *value;

    public:
        Floor():value(NULL){};
        Floor(Base *tree):value(tree){};

        double evaluate(){
            return floor(value->evaluate());
        }


};
