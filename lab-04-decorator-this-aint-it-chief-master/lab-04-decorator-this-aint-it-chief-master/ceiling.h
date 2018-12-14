#include "base.h"
#include <cmath>

using namespace std;

class Ceiling : public Base{
    private:
        Base *value;

    public:
        Ceiling(): value(NULL){};
        Ceiling(Base *value_to_evaluate): value(value_to_evaluate){};

        double evaluate(){
            return ceil(value->evaluate());
        }    
    


};                         
