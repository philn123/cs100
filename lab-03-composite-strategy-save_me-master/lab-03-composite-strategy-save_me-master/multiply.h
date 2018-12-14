#pragma once
#include "base.h"

class Mult : public Base{

    private:
	    Base *operand1;
	    Base *operand2;
    public:
	    Mult(){};
	    Mult(Base *value1, Base *value2){
	        operand1 = value1;
		operand2 = value2;
	    }

	    double evaluate(){
	        return (operand1->evaluate()) * (operand2->evaluate());
	    }



};
